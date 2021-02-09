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

#define SYSTEM_TEST_IMU true
auto FormatEuclidVectorForPrintOut(std::string Sensor, types::EuclideanVector<std::int16_t> Vector) -> std::string;

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
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM16_Init();
  MX_TIM17_Init();

#ifdef SYSTEM_TEST_IMU

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
      } else {
        utilities::UartPrint("Update failed.");
      }
    }
    utilities::Sleep(500);
  }
#else
  while (1) {
  }
#endif

  return 0;
}

auto FormatEuclidVectorForPrintOut(std::string Sensor, types::EuclideanVector<std::int16_t> Vector) -> std::string {
  return Sensor + ":" +
         " X: " + std::to_string(Vector.x) +
         " Y: " + std::to_string(Vector.y) +
         " Z: " + std::to_string(Vector.z);
}