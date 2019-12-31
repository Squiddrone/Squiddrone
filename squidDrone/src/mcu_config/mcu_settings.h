#ifndef SRC_MCU_CONFIG_MCU_SETTINGS_H_
#define SRC_MCU_CONFIG_MCU_SETTINGS_H_

#ifdef __cplusplus
	extern "C" {
#endif



#define PWM_ESC_0_Pin GPIO_PIN_0
#define PWM_ESC_0_GPIO_Port GPIOA
#define PWM_ESC_1_Pin GPIO_PIN_1
#define PWM_ESC_1_GPIO_Port GPIOA
#define USART2_TX_Pin GPIO_PIN_2
#define USART2_TX_GPIO_Port GPIOA
#define USART2_RX_Pin GPIO_PIN_3
#define USART2_RX_GPIO_Port GPIOA
#define PWM_LED_GREEN_Pin GPIO_PIN_4
#define PWM_LED_GREEN_GPIO_Port GPIOA
#define PWM_ESC_2_Pin GPIO_PIN_6
#define PWM_ESC_2_GPIO_Port GPIOA
#define PWM_ESC_3_Pin GPIO_PIN_7
#define PWM_ESC_3_GPIO_Port GPIOA
#define PWM_LED_BLUE_Pin GPIO_PIN_0
#define PWM_LED_BLUE_GPIO_Port GPIOB
#define CSCOM_Pin GPIO_PIN_8
#define CSCOM_GPIO_Port GPIOA
#define GPS1_Pin GPIO_PIN_11
#define GPS1_GPIO_Port GPIOA
#define GPS2_Pin GPIO_PIN_12
#define GPS2_GPIO_Port GPIOA
#define T_SWDIO_Pin GPIO_PIN_13
#define T_SWDIO_GPIO_Port GPIOA
#define T_SWCLK_Pin GPIO_PIN_14
#define T_SWCLK_GPIO_Port GPIOA
#define PWM_LED_RED_Pin GPIO_PIN_7
#define PWM_LED_RED_GPIO_Port GPIOB
#define LD2_Pin GPIO_PIN_8
#define LD2_GPIO_Port GPIOB

void Error_Handler();


#ifdef __cplusplus
	}
#endif
#endif /* SRC_MCU_CONFIG_MCU_SETTINGS_H_ */
