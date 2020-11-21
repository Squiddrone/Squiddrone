#include "stm32g4xx_hal.h"

#include "spi_config.h"

SPI_HandleTypeDef hspi1;

void MX_I2C2_Init(void) {
  hspi1.mock_return_value = HAL_ERROR;
}