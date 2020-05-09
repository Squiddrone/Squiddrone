/*
 * main.cpp
 *
 *  Created on: Oct 4, 2019
 *      Author: aron
 */
#include "stm32g4xx_hal.h"
#include "cmsis_os.h"
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
#include "threads.hpp"

osThreadId_t blink_led_task_handle;

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

  osKernelInitialize();

  osThreadAttr_t blink_led_task_attributes;
  blink_led_task_attributes.name = "defaultTask";
  blink_led_task_attributes.cb_mem = NULL;
  blink_led_task_attributes.stack_mem = NULL;
  blink_led_task_attributes.priority = static_cast<osPriority_t>(osPriorityNormal);
  blink_led_task_attributes.stack_size = 128;

  
  blink_led_task_handle = osThreadNew(BlinkLedTask, NULL, &blink_led_task_attributes);

  osKernelStart();

  while(1){}
  return 0;
}


