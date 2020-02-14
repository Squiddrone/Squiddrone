#include <stdint.h>
#include "stm32g4xx_hal_tim.h"
#include "stm32g4xx_hal_def.h"


HalTimPwmStopMockValues hal_tim_pwm_stop_mock_values;

HAL_StatusTypeDef HAL_TIM_PWM_Stop(TIM_HandleTypeDef *htim, uint32_t Channel){
  hal_tim_pwm_stop_mock_values.htim = htim;
  hal_tim_pwm_stop_mock_values.channel = Channel;
  return hal_tim_pwm_stop_mock_values.return_value;
}

HalTimCalcPscMockValues hal_tim_calc_psc_mock_values;

uint32_t __HAL_TIM_CALC_PSC(int timer_clock, int target_timer_clock_rate){
  hal_tim_calc_psc_mock_values.timer_clock = timer_clock;
  hal_tim_calc_psc_mock_values.target_timer_clock_rate = target_timer_clock_rate;
  return hal_tim_calc_psc_mock_values.return_value;
}

HalTimPwmConfigChannelMockValues hal_tim_pwm_config_channel_mock_values;

HAL_StatusTypeDef HAL_TIM_PWM_ConfigChannel(TIM_HandleTypeDef *htim, TIM_OC_InitTypeDef *sConfig, uint32_t Channel){
  hal_tim_pwm_config_channel_mock_values.htim = htim;
  hal_tim_pwm_config_channel_mock_values.sconfig = sConfig;
  hal_tim_pwm_config_channel_mock_values.channel = Channel;
  return hal_tim_pwm_config_channel_mock_values.return_value;
}

HalTimPwmInitMockValues hal_tim_pwm_init_mock_values;

HAL_StatusTypeDef HAL_TIM_PWM_Init(TIM_HandleTypeDef *htim){
  hal_tim_pwm_init_mock_values.htim = htim;
  return hal_tim_pwm_init_mock_values.return_value;
}

HalTimPwmStartMockValues hal_tim_pwm_start_mock_values;

HAL_StatusTypeDef HAL_TIM_PWM_Start(TIM_HandleTypeDef *htim, uint32_t Channel){
  hal_tim_pwm_start_mock_values.htim = htim;
  hal_tim_pwm_start_mock_values.channel = Channel;
  return hal_tim_pwm_start_mock_values.return_value;
}
