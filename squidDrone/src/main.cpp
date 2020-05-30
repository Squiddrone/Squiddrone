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
#include "i2c.hpp"
#include <memory>
#include <string.h>
#include <stdio.h>

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

  static const uint8_t MPU9250_ADDR = 0x68;
  static const uint8_t WHO_AM_I = 0x75;
  std::unique_ptr<i2c::I2C> i2c_interface;
  i2c_interface = std::make_unique<i2c::I2C>();

  uint8_t buf[12];

  while (1)
    {
      std::vector<uint8_t> data = {WHO_AM_I};
      i2c::I2CStatus i2c_status;
      std::vector<uint8_t> result_data;

      i2c_status = i2c_interface->Write(MPU9250_ADDR, data);

      if (i2c_status != i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL) {
        strcpy((char*)buf, "Error Tx\r\n");
      }
      else {
        std::tie(i2c_status, result_data) = i2c_interface->Read(MPU9250_ADDR, 1);

        if (i2c_status != i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL) {
        strcpy((char*)buf, "Error Rx\r\n");
        }
        else {
          uint8_t mpu_address = result_data.at(0);
          sprintf((char*)buf, "%02X\r\n", mpu_address);
        }

      }

      HAL_UART_Transmit(&huart2, buf, (uint16_t)strlen((char*)buf), HAL_MAX_DELAY);

      HAL_Delay(500);
    }
  return 0;
}


