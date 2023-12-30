/**
 * main.cpp
 *
 *  Created on: Oct 4, 2019
 *      Author: aron
 */

#include "stm32g431xx.h"
#include "stm32g4xx_hal.h"
//
#include <memory>
#include "clock_config.h"
#include "com/com_message_buffer.hpp"
#include "com_interrupt_handler.hpp"
#include "com_nrf24l01.hpp"
#include "com_nrf24l01_types.hpp"
#include "cordic_config.h"
#include "crc_config.h"
// #include "filter.hpp"
#include "fmac_config.h"
#include "gpio_config.h"
#include "i2c.hpp"
#include "i2c_config.h"
#include "inertial_measurement.hpp"
#include "math.h"
#include "mcu_settings.h"
#include "motor_builder.hpp"
#include "motor_driver.hpp"
#include "serial_config.h"
#include "sleep.hpp"
#include "spi_config.h"
#include "timer_config.h"
#include "uart_print.hpp"

#define SYSTEM_TEST_IMU false
#define SYSTEM_TEST_PROPULSION false
#define SYSTEM_TEST_COM false

auto FormatEuclidVectorForPrintOut(const std::string &Sensor, types::EuclideanVector<std::int16_t> Vector) -> std::string;

struct RCDataPacket : public types::ComDataPacket {
  union {
    float f;
    uint8_t u[sizeof(float)];
  } throttle_cast;

  inline auto Decode() noexcept -> float {
    std::copy(data.begin(),
              data.begin() + sizeof(float),
              std::begin(throttle_cast.u));
    return throttle_cast.f;
  }

  RCDataPacket() : types::ComDataPacket(){};
  RCDataPacket(const types::ComDataPacket &p) : types::ComDataPacket() {
    data = p.data;
  }
  ~RCDataPacket() = default;
};

// MedianFilter<float, 9> median_filter;

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

  auto com_cs_pin = spi::CSPin(CSCOM_GPIO_Port, CSCOM_Pin, spi::CSActiveState::ACTIVE_LOW);
  auto com_spi = std::make_unique<spi::SPI>(com_cs_pin);
  auto com_spi_protocol = std::make_unique<com::NRF24L01SpiProtocol>(std::move(com_spi));
  auto com_buffer = std::make_unique<com::ComMessageBuffer>();
  auto com_nrf_core = std::make_unique<com::NRF24L01Core>(std::move(com_spi_protocol));
  auto com_nrf = std::make_shared<com::NRF24L01>(std::move(com_buffer), std::move(com_nrf_core));
  com::ComInterruptHandler::SetComDriver(com_nrf);

  if (com_nrf->NRFInit() != types::DriverStatus::OK) {
    utilities::UartPrint("Init error...");
    while (true) {
    };
  }

  auto i2c = std::make_unique<i2c::I2C>();
  auto imu = std::make_unique<imu::InertialMeasurement>(std::move(i2c));
  bool init_successful = false;

  utilities::UartPrint("Begin IMU calibration");
  if (imu->Init() == types::DriverStatus::OK) {
    imu->SetGyroscopeSensitivity(types::ImuSensitivity::FINEST);
    imu->SetAccelerometerSensitivity(types::ImuSensitivity::ROUGHEST);
    utilities::UartPrint("IMU Init successfull.");
    init_successful = true;
  } else {
    utilities::UartPrint("IMU Init failed.");
  }

  std::unique_ptr<propulsion::AbstractMotorBuilder> builder = std::make_unique<propulsion::MotorBuilder>();
  propulsion::MotorDriver driver(std::move(builder));
  driver.ArmEscs();
  utilities::Sleep(3000);

  utilities::UartPrint("Ready...");

  float throttle = 0.0f;
  float err_x_I = 0.0f;
  float throttle_x_control = 0.0f;

  while (1) {
    if (init_successful == true) {
      if (imu->Update() == types::DriverStatus::OK) {
        auto accel_vector = imu->GetAccelerometer();
        static constexpr float pi = 3.14159265f;
        static constexpr float G = 2048.0;
        float angle_x = atan((static_cast<float>(accel_vector.x) / G) / ((1.0f - static_cast<float>(accel_vector.z) / G))) * 180.0f / pi;
        utilities::UartPrint("Angle X: " + std::to_string(static_cast<int16_t>(angle_x)));
        // auto angle_y = atan((static_cast<float>(accel_vector.y) / G) / ((1.0 - static_cast<float>(accel_vector.z) / G))) * 180.0 / pi;

        auto err_x = 0.0f - angle_x;

        static constexpr float k_I = 0.01f;
        err_x_I += k_I * err_x;

        static constexpr float k_P = 0.1f;

        throttle_x_control = err_x * k_P + err_x_I;

        float threshold = 0.1f * throttle;

        if (abs(throttle_x_control) > threshold) {
          if (throttle_x_control > 0) {
            throttle_x_control = threshold;
          }
          if (throttle_x_control < 0) {
            throttle_x_control = -threshold;
          }
        }
      }
    }
    RCDataPacket rc_data(com_nrf->GetDataPacket());
    if (rc_data.data.size() > 0) {
      throttle = rc_data.Decode();
      utilities::UartPrint("Throttle: " + std::to_string(static_cast<int>(throttle * 100)));
      // auto throttle_filt = median_filter.Insert(throttle);
    }

    if (throttle < 0.0) {
      throttle = 0.0;
    }
    // utilities::UartPrint("Control: " + std::to_string(static_cast<int>(throttle_x_control*100)));
    driver.SetMotorSpeed(propulsion::MotorPosition::LEFT_FRONT, throttle + throttle_x_control);
    driver.SetMotorSpeed(propulsion::MotorPosition::RIGHT_FRONT, throttle + throttle_x_control);
    driver.SetMotorSpeed(propulsion::MotorPosition::LEFT_REAR, throttle - throttle_x_control);
    driver.SetMotorSpeed(propulsion::MotorPosition::RIGHT_REAR, throttle - throttle_x_control);
    utilities::Sleep(100);
  }
  return 0;
}

auto FormatEuclidVectorForPrintOut(const std::string &Sensor, types::EuclideanVector<std::int16_t> Vector) -> std::string {
  return Sensor + ":" +
         " X: " + std::to_string(Vector.x) +
         " Y: " + std::to_string(Vector.y) +
         " Z: " + std::to_string(Vector.z);
}
