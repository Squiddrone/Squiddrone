#ifndef TESTS_COM_MOCK_LIBRARIES_STM32G4XX_HAL_H_
#define TESTS_COM_MOCK_LIBRARIES_STM32G4XX_HAL_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __GPIO_TypeDef {
  uint8_t mock_test_value;
} GPIO_TypeDef;

typedef enum {
  GPIO_PIN_RESET = 0U,
  GPIO_PIN_SET
} GPIO_PinState;

void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);

void HAL_Delay(uint32_t delay);

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#ifdef __cplusplus
}
#endif

#endif