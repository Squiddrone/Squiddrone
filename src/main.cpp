/**
 * main.cpp
 *
 *  Created on: Oct 4, 2019
 *      Author: aron
 */

#include "stm32g4xx_hal.h"
//
#include <memory>
#include "clock_config.h"
#include "com/com_message_buffer.hpp"
#include "com_nrf24l01_types.hpp"
#include "cordic_config.h"
#include "crc_config.h"
#include "fmac_config.h"
#include "gpio_config.h"
#include "i2c.hpp"
#include "i2c_config.h"
#include "inertial_measurement.hpp"
#include "mcu_settings.h"
#include "serial_config.h"
#include "sleep.hpp"
#include "spi_config.h"
#include "timer_config.h"
#include "uart_print.hpp"

#define SYSTEM_TEST_IMU false
#define SYSTEM_TEST_COM true

auto FormatEuclidVectorForPrintOut(const std::string &Sensor, types::EuclideanVector<std::int16_t> Vector) -> std::string;

#include "com_interrupt_handler.hpp"
#include "com_nrf24l01.hpp"

int main() {
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_CORDIC_Init();
  MX_CRC_Init();
  MX_FMAC_Init();
  MX_I2C2_Init();
  MX_SPI1_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  MX_TIM16_Init();
  MX_TIM17_Init();

#if (SYSTEM_TEST_COM == true)

  auto com_cs_pin = spi::CSPin(CSCOM_GPIO_Port, CSCOM_Pin, spi::CSActiveState::ACTIVE_LOW);
  auto com_spi = std::make_unique<spi::SPI>(com_cs_pin);
  auto com_spi_protocol = std::make_unique<com::NRF24L01SpiProtocol>(std::move(com_spi));
  auto com_buffer = std::make_unique<com::ComMessageBuffer>();
  auto com_nrf_core = std::make_unique<com::NRF24L01Core>(std::move(com_spi_protocol));
  auto com_nrf = std::make_shared<com::NRF24L01>(std::move(com_buffer), std::move(com_nrf_core));
  com::ComInterruptHandler::SetComDriver(com_nrf);

  // Frame must always be 32 bytes long. Padd if necessary.
  types::com_msg_frame tx_data{'t', 'e', 's', 't', 't', 'e', 's', 't', 't', 'e', 's', 't', 't', 'e', 's', 't', 't', 'e', 's', 't', 't', 'e', 's', 't', 't', 'e', '_', 'e', 'n', 'd'};
  types::ComDataPacket tx_packet;

  tx_packet.data = tx_data;
  tx_packet.type = types::ComPacketType::TELEMETRY_PACKET;
  tx_packet.target = types::PutDataTarget::TARGET_FALLBACK;

  if (com_nrf->NRFInit() != types::DriverStatus::OK) {
    utilities::UartPrint("Init error...");
  }

  types::ota_config_data<types::PutDataTarget::TARGET_FRONT> addr;

  utilities::UartPrint("Ready...");

  while (1) {
    auto rv = com_nrf->PutDataPacket(types::PutDataTarget::TARGET_FALLBACK, tx_packet);

    if (rv != types::DriverStatus::OK) {
      utilities::UartPrint("Tx error...");
    }

    utilities::Sleep(2000);
    {
      auto rx_packet = com_nrf->GetDataPacket();

      if (rx_packet.data.size() > 0) {
        std::string type_string(std::to_string(static_cast<std::uint8_t>(rx_packet.type)));
        utilities::UartPrint("type: " + type_string);
        std::string target_string(std::to_string(static_cast<std::uint8_t>(rx_packet.target)));
        utilities::UartPrint("target: " + type_string);
        std::string data_string(rx_packet.data.begin(), rx_packet.data.end());
        utilities::UartPrint("data: " + data_string);
      }
    }
  }
#endif

#if (SYSTEM_TEST_IMU == true)

  auto i2c = std::make_unique<i2c::I2C>();
  auto imu = std::make_unique<imu::InertialMeasurement>(std::move(i2c));
  bool init_successful = false;

  if (imu->Init() == types::DriverStatus::OK) {
    utilities::UartPrint("Init successfull.");
    init_successful = true;
  } else {
    utilities::UartPrint("Init failed.");
  }

  utilities::Sleep(500);

  while (1) {
    if (init_successful == true) {
      if (imu->Update() == types::DriverStatus::OK) {
        utilities::UartPrint(FormatEuclidVectorForPrintOut("Gyroscope", imu->GetGyroscope()));
        utilities::UartPrint(FormatEuclidVectorForPrintOut("Accelerometer", imu->GetAccelerometer()));
        utilities::UartPrint(FormatEuclidVectorForPrintOut("Magnetometer", imu->GetMagnetometer()));
        utilities::UartPrint("Temperature: " + std::to_string(imu->GetTemperature()));
      } else {
        utilities::UartPrint("Update failed.");
      }
    }
    utilities::Sleep(500);
  }
#endif

#if (SYSTEM_TEST_COM == false && SYSTEM_TEST_IMU == false)
  while (1) {
  }
#endif

  return 0;
}

auto FormatEuclidVectorForPrintOut(const std::string &Sensor, types::EuclideanVector<std::int16_t> Vector) -> std::string {
  return Sensor + ":" +
         " X: " + std::to_string(Vector.x) +
         " Y: " + std::to_string(Vector.y) +
         " Z: " + std::to_string(Vector.z);
}
