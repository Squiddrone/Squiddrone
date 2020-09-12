/**
 * main.cpp
 *
 *  Created on: Oct 4, 2019
 *      Author: aron
 */

#include "stm32g4xx_hal.h"
//
#include "clock_config.h"
#include "com/com_message_buffer.hpp"
#include "com/nrf24l01.hpp"
#include "cordic_config.h"
#include "crc_config.h"
#include "fmac_config.h"
#include "gpio_config.h"
#include "i2c_config.h"
#include "mcu_settings.h"
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

  auto com_spi_handle = std::make_unique<spi::SPI>(CSCOM_Pin);
  auto com_msg_buffer = std::make_unique<com::ComMessageBuffer>();
  auto comsys = std::make_unique<com::NRF24L01>(std::move(com_spi_handle), std::move(com_msg_buffer));

  types::com_msg_frame test_payload = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};

  while (1) {
    comsys->PutDataPacket(0x15, test_payload);
    HAL_Delay(1000);
  }
  return 0;
}
