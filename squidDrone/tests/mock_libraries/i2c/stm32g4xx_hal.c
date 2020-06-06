#include "stm32g4xx_hal.h"

HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  DevAddress = DevAddress >> 1; //revert shift to the left for easier comparison

  if (DevAddress == 0x10) {
    pData[0] = 1;
    pData[1] = 2;
    pData[2] = 3;
    pData[3] = 4;
    return HAL_OK;
  }
  else if (DevAddress == 0x11) {
    return HAL_ERROR;
  }
  else if (DevAddress == 0x12) {
    return HAL_TIMEOUT;
  }
  else if (DevAddress == 0x13) {
    return HAL_BUSY;
  }

  return HAL_ERROR;
}

HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  DevAddress = DevAddress >> 1; //revert shift to the left for easier comparison

  if (DevAddress == 0x10) {
    return HAL_OK;
  }
  else if (DevAddress == 0x11) {
    return HAL_ERROR;
  }
  else if (DevAddress == 0x12) {
    return HAL_TIMEOUT;
  }
  else if (DevAddress == 0x13) {
    return HAL_BUSY;
  }

  return HAL_ERROR;
}