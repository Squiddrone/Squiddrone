/*
 * main.cpp
 *
 *  Created on: Oct 4, 2019
 *      Author: aron
 */
#include "stm32g4xx_hal.h"
#include "clock_config.h"
#include "gpio_config.h"
#include "serial_config.h"
#include "cordic_config.h"
#include "crc_config.h"
#include "fmac_config.h"
#include "i2c_config.h"
#include "spi_config.h"
#include "timer_config.h"
#include "mcu_settings.h"
#include "esc.hpp"
#include "letodar_2204.hpp"
#include "little_bee_20_a.hpp"
#include <memory>
#include <utility>

int main(){
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

  
  propulsion::LeTodar2204 letodar(std::make_unique<propulsion::LittleBee20A>(&htim16, TIM_CHANNEL_1));

  letodar.SetSpeedInPercent(100);
  auto a = letodar.GetCurrentSpeedInPercent();
  letodar.SetSpeedInPercent(50);
  letodar.SetSpeedInPercent(0);
  letodar.SetSpeedInPercent(13.3F);
  while(1){}
  return 0;
}


