/*
 * serial_config.h
 *
 *  Created on: Oct 20, 2019
 *      Author: aron
 */

#ifndef SRC_MCU_CONFIG_SERIAL_CONFIG_H_
#define SRC_MCU_CONFIG_SERIAL_CONFIG_H_


#ifdef __cplusplus
	extern "C" {
#endif

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);

#ifdef __cplusplus
	}
#endif


#endif /* SRC_MCU_CONFIG_SERIAL_CONFIG_H_ */
