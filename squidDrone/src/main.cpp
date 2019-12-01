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
#include "mcu_settings.h"

int main(){
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_USART2_UART_Init();
	float a = 0;
	while(1){
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		HAL_Delay(500);
	}
	return 0;
}


