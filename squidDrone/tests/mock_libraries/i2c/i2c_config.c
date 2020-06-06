#include "stm32g4xx_hal.h"
#include "i2c_config.h"

I2C_HandleTypeDef hi2c2;

void MX_I2C2_Init(void)
{
  hi2c2.dummy = 0;
}