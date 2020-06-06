/*
 * main.cpp
 *
 *  Created on: Oct 4, 2019
 *      Author: aron
 */
#include "stm32g4xx_hal.h"
#include "clock_config.h"
#include "cordic_config.h"
#include "crc_config.h"
#include "fmac_config.h"
#include "gpio_config.h"
#include "i2c_config.h"
#include "mcu_settings.h"
#include "motor_builder.hpp"
#include "propulsion_hardware_config.hpp"
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

  propulsion::PropulsionHardwareConfig config{types::MotorType::LETODAR_2204, types::EscType::LITTLE_BEE_20_A, &htim2, TIM_CHANNEL_2};
  auto correct_motor = propulsion::MotorBuilder::Create(config);

  while (1) {
    auto a = correct_motor->GetCurrentSpeedInPercent();
  }
  return 0;
}
