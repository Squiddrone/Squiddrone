#include "stm32g4xx_hal.h"

HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  if (DevAddress == 0x01)
  {
    pData[0] = 1;
    pData[1] = 2;
    pData[2] = 3;
    return HAL_OK;
  }
  else if (DevAddress == 0x02)
  {
    return HAL_ERROR;
  }
  else if (DevAddress == 0x03)
  {
    return HAL_TIMEOUT;
  }
  else if (DevAddress == 0x04)
  {
    return HAL_BUSY;
  }

  return HAL_ERROR;
}

HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  return HAL_ERROR;
}