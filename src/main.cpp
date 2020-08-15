/**
 * main.cpp
 *
 *  Created on: Oct 4, 2019
 *      Author: aron
 */
#include "stm32g4xx_hal.h"

#include <stdio.h>
#include <string.h>
#include <memory>
#include "clock_config.h"
#include "cordic_config.h"
#include "crc_config.h"
#include "fmac_config.h"
#include "gpio_config.h"
#include "gyroscope.hpp"
#include "i2c.hpp"
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

  uint8_t buf[25];

  auto i2c_interface = std::make_unique<i2c::I2C>();

  std::unique_ptr<imu::Gyroscope> gyroscope = std::make_unique<imu::Gyroscope>(std::move(i2c_interface));
  if (gyroscope->Init(0x68) == types::HalError::WORKING) {
    strcpy((char*)buf, "Init successfull\r\n");
  } else {
    strcpy((char*)buf, "Init failed\r\n");
  }
  HAL_UART_Transmit(&huart2, buf, (uint16_t)strlen((char*)buf), HAL_MAX_DELAY);

  HAL_Delay(500);

  while (1) {
    if (gyroscope->Update() == types::HalError::WORKING) {
      auto gyro_sensor_values = gyroscope->Get();
      sprintf((char*)buf, "%d %d %d\r\n", gyro_sensor_values.x, gyro_sensor_values.y, gyro_sensor_values.z);
    } else {
      strcpy((char*)buf, "Update failed\r\n");
    }
    HAL_UART_Transmit(&huart2, buf, (uint16_t)strlen((char*)buf), HAL_MAX_DELAY);
    HAL_Delay(500);
  }
  return 0;
}
