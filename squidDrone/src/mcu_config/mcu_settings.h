/*
 * settings.h
 *
 *  Created on: Oct 10, 2019
 *      Author: aron
 */


#ifndef SRC_MCU_CONFIG_MCU_SETTINGS_H_
#define SRC_MCU_CONFIG_MCU_SETTINGS_H_

#ifdef __cplusplus
	extern "C" {
#endif



#define USART2_TX_Pin GPIO_PIN_2
#define USART2_TX_GPIO_Port GPIOA
#define USART2_RX_Pin GPIO_PIN_3
#define USART2_RX_GPIO_Port GPIOA
#define T_SWDIO_Pin GPIO_PIN_13
#define T_SWDIO_GPIO_Port GPIOA
#define T_SWCLK_Pin GPIO_PIN_14
#define T_SWCLK_GPIO_Port GPIOA
#define T_SWO_Pin GPIO_PIN_3
#define T_SWO_GPIO_Port GPIOB
#define LD2_Pin GPIO_PIN_8
#define LD2_GPIO_Port GPIOB

void Error_Handler();


#ifdef __cplusplus
	}
#endif
#endif /* SRC_MCU_CONFIG_MCU_SETTINGS_H_ */
