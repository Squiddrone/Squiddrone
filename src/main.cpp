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
#include "i2c_config.h"
#include "mcu_settings.h"
#include "motor_builder.hpp"
#include "motor_driver.hpp"
#include "serial_config.h"
#include "spi_config.h"
#include "timer_config.h"

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

  std::unique_ptr<propulsion::AbstractMotorBuilder> builder = std::make_unique<propulsion::MotorBuilder>();
  propulsion::MotorDriver driver(std::move(builder));

  while (1) {
    driver.ArmEscs();
    HAL_Delay(1000);
  }
  //while (1) {
  //driver.ArmEscs();
  //HAL_Delay(1000);
  //driver.SetMotorSpeed(propulsion::MotorPosition::LEFT_FRONT, 99.0);
  //driver.SetMotorSpeed(propulsion::MotorPosition::RIGHT_FRONT, 75.1);
  //driver.SetMotorSpeed(propulsion::MotorPosition::LEFT_REAR, 50.0);
  //driver.SetMotorSpeed(propulsion::MotorPosition::RIGHT_REAR, 10.0);
  //}
  return 0;
}
