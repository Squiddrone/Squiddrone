#ifndef TESTS_MOCK_LIBRARIES_SPI_STM32G4XX_HAL_H_
#define TESTS_MOCK_LIBRARIES_SPI_STM32G4XX_HAL_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  HAL_OK = 0x00U,
  HAL_ERROR = 0x01U,
  HAL_BUSY = 0x02U,
  HAL_TIMEOUT = 0x03U
} HAL_StatusTypeDef;

typedef struct __SPI_HandleTypeDef {
  HAL_StatusTypeDef mock_return_value;
} SPI_HandleTypeDef;

HAL_StatusTypeDef HAL_SPI_TransmitReceive(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size,
                                          uint32_t Timeout);

HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint16_t Size,
                                   uint32_t Timeout);

typedef struct __GPIO_TypeDef {
  uint8_t mock_test_value;
} GPIO_TypeDef;

typedef enum {
  GPIO_PIN_RESET = 0U,
  GPIO_PIN_SET
} GPIO_PinState;

void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
#ifdef __cplusplus
}
#endif

#endif