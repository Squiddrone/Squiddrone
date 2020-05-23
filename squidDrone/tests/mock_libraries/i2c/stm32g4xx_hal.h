#ifndef MOCK_STM32G4xx_HAL_H_
#define MOCK_STM32G4xx_HAL_H_

#include <stdint.h>
#include "stm32g4xx_hal_def.h"

typedef struct __I2C_HandleTypeDef
{
  int dummy;
} I2C_HandleTypeDef;

HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);

#endif /* MOCK_STM32G4xx_HAL_H_ */

