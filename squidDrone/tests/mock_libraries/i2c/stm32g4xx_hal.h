#ifndef MOCK_STM32G4xx_HAL_H_
#define MOCK_STM32G4xx_HAL_H_

#include <stdint.h>

#ifdef __cplusplus
  extern "C" {
#endif

typedef enum
{
  HAL_OK       = 0x00U,
  HAL_ERROR    = 0x01U,
  HAL_BUSY     = 0x02U,
  HAL_TIMEOUT  = 0x03U
} HAL_StatusTypeDef;

#define HAL_MAX_DELAY      0xFFFFFFFFU

typedef struct __I2C_HandleTypeDef
{
  int dummy;
} I2C_HandleTypeDef;

HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);

#ifdef __cplusplus
  }
#endif

#endif /* MOCK_STM32G4xx_HAL_H_ */
