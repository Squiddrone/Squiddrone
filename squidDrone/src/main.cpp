/*
 * main.cpp
 *
 *  Created on: Oct 4, 2019
 *      Author: aron
 *     TODO static void MX_GPIO_Init(void);
 * 	   TODO static void MX_USART2_UART_Init(void);
 */
#include "stm32g4xx_hal.h"
#include "clock_config.h"

int main(){

	HAL_Init();
	SystemClock_Config();
	return 0;
}


