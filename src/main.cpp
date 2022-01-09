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
#include "motor_builder.hpp"
#include "motor_driver.hpp"
#include "serial_config.h"
#include "sleep.hpp"
#include "spi_config.h"
#include "timer_config.h"
#include "uart_print.hpp"

#define SYSTEM_TEST_IMU false
#define SYSTEM_TEST_PROPULSION true

auto FormatEuclidVectorForPrintOut(const std::string &Sensor, types::EuclideanVector<std::int16_t> Vector) -> std::string;

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

#ifdef SYSTEM_TEST_PROPULSION
  std::unique_ptr<propulsion::AbstractMotorBuilder> builder = std::make_unique<propulsion::MotorBuilder>();
  propulsion::MotorDriver driver(std::move(builder));
  driver.ArmEscs();
  utilities::Sleep(3000);

  driver.SetMotorSpeed(propulsion::MotorPosition::LEFT_FRONT, 10);
  driver.SetMotorSpeed(propulsion::MotorPosition::RIGHT_FRONT, 10);
  driver.SetMotorSpeed(propulsion::MotorPosition::LEFT_REAR, 10);
  driver.SetMotorSpeed(propulsion::MotorPosition::RIGHT_REAR, 10);

  utilities::Sleep(3000);
  driver.SetMotorSpeed(propulsion::MotorPosition::LEFT_FRONT, 3.0);
  driver.SetMotorSpeed(propulsion::MotorPosition::RIGHT_FRONT, 3.0);
  driver.SetMotorSpeed(propulsion::MotorPosition::LEFT_REAR, 3.0);
  driver.SetMotorSpeed(propulsion::MotorPosition::RIGHT_REAR, 3.0);

  utilities::Sleep(5000);
  driver.SetMotorSpeed(propulsion::MotorPosition::LEFT_FRONT, 10.0);
  driver.SetMotorSpeed(propulsion::MotorPosition::RIGHT_FRONT, 10.0);
  driver.SetMotorSpeed(propulsion::MotorPosition::LEFT_REAR, 10.0);
  driver.SetMotorSpeed(propulsion::MotorPosition::RIGHT_REAR, 10.0);

  utilities::Sleep(5000);
  driver.SetMotorSpeed(propulsion::MotorPosition::LEFT_FRONT, 8.0);
  driver.SetMotorSpeed(propulsion::MotorPosition::RIGHT_FRONT, 8.0);
  driver.SetMotorSpeed(propulsion::MotorPosition::LEFT_REAR, 8.0);
  driver.SetMotorSpeed(propulsion::MotorPosition::RIGHT_REAR, 8.0);

  utilities::Sleep(5000);
  driver.SetMotorSpeed(propulsion::MotorPosition::LEFT_FRONT, 3.0);
  driver.SetMotorSpeed(propulsion::MotorPosition::RIGHT_FRONT, 3.0);
  driver.SetMotorSpeed(propulsion::MotorPosition::LEFT_REAR, 3.0);
  driver.SetMotorSpeed(propulsion::MotorPosition::RIGHT_REAR, 3.0);

  utilities::Sleep(5000);
  driver.SetMotorSpeed(propulsion::MotorPosition::LEFT_FRONT, 0.0);
  driver.SetMotorSpeed(propulsion::MotorPosition::RIGHT_FRONT, 0.0);
  driver.SetMotorSpeed(propulsion::MotorPosition::LEFT_REAR, 0.0);
  driver.SetMotorSpeed(propulsion::MotorPosition::RIGHT_REAR, 0.0);

#elif SYSTEM_TEST_IMU

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
#else
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