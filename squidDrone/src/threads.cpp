#include "stm32g4xx_hal.h"
#include "threads.hpp"
#include "mcu_settings.h"


/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used 
 * @retval None
 */
void BlinkLedTask(void *argument){
  for(;;)
  {
    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    osDelay(1200);
  }
}

/**
 * @brief  Period elapsed callback in non blocking mode
 * @note   This function is called  when TIM15 interrupt took place, inside
 * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
 * a global variable "uwTick" used as application time base.
 * @param  htim : TIM handle
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
  if (htim->Instance == TIM15) {
    HAL_IncTick();
  }
}