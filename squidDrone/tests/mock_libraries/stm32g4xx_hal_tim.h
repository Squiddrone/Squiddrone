#ifndef TESTS_MOCK_LIBRARIES_STM32G4XX_HAL_TIM_H_
#define TESTS_MOCK_LIBRARIES_STM32G4XX_HAL_TIM_H_


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "stm32g4xx_hal_def.h"

#define TIM_OCPOLARITY_HIGH 0x00000000U
#define TIM_OCFAST_DISABLE 0x00000000U
#define TIM_OCMODE_PWM1 0x00000000U

typedef struct
{
  uint32_t Prescaler;
  uint32_t Period;
  uint32_t RepetitionCounter;
} TIM_Base_InitTypeDef;

typedef enum
{
  HAL_TIM_ACTIVE_CHANNEL_1        = 0x01U,    
  HAL_TIM_ACTIVE_CHANNEL_2        = 0x02U,   
  HAL_TIM_ACTIVE_CHANNEL_3        = 0x04U,  
  HAL_TIM_ACTIVE_CHANNEL_4        = 0x08U,   
  HAL_TIM_ACTIVE_CHANNEL_5        = 0x10U,   
  HAL_TIM_ACTIVE_CHANNEL_6        = 0x20U,    
  HAL_TIM_ACTIVE_CHANNEL_CLEARED  = 0x00U    
} HAL_TIM_ActiveChannel;

typedef struct {
  int test_member;
  TIM_Base_InitTypeDef Init;
  HAL_TIM_ActiveChannel Channel;
} TIM_HandleTypeDef;


typedef struct {
  TIM_HandleTypeDef* htim;
  uint32_t channel;
  HAL_StatusTypeDef return_value;
} HalTimPwmStopMockValues;

HalTimPwmStopMockValues hal_tim_pwm_stop_mock_values;

HAL_StatusTypeDef HAL_TIM_PWM_Stop(TIM_HandleTypeDef *htim, uint32_t Channel){
  hal_tim_pwm_stop_mock_values.htim = htim;
  hal_tim_pwm_stop_mock_values.channel = Channel;
  return hal_tim_pwm_stop_mock_values.return_value;
}

typedef struct {
  int timer_clock;
  int target_timer_clock_rate;
  uint32_t return_value;
}HalTimCalcPscMockValues;

HalTimCalcPscMockValues hal_tim_calc_psc_mock_values;

uint32_t __HAL_TIM_CALC_PSC(int timer_clock, int target_timer_clock_rate){
  hal_tim_calc_psc_mock_values.timer_clock = timer_clock;
  hal_tim_calc_psc_mock_values.target_timer_clock_rate = target_timer_clock_rate;
  return hal_tim_calc_psc_mock_values.return_value;
}

typedef struct
{
  uint32_t OCMode;
  uint32_t Pulse;
  uint32_t OCPolarity;
  uint32_t OCFastMode; 
} TIM_OC_InitTypeDef;

typedef struct{
  TIM_HandleTypeDef *htim;
  TIM_OC_InitTypeDef *sconfig;
  uint32_t channel;
  HAL_StatusTypeDef return_value;
}HalTimPwmConfigChannelMockValues;

HalTimPwmConfigChannelMockValues hal_tim_pwm_config_channel_mock_values;

HAL_StatusTypeDef HAL_TIM_PWM_ConfigChannel(TIM_HandleTypeDef *htim, TIM_OC_InitTypeDef *sConfig, uint32_t Channel){
  hal_tim_pwm_config_channel_mock_values.htim = htim;
  hal_tim_pwm_config_channel_mock_values.sconfig = sConfig;
  hal_tim_pwm_config_channel_mock_values.channel = Channel;
  return hal_tim_pwm_config_channel_mock_values.return_value;
}

typedef struct{
  TIM_HandleTypeDef* htim;
  HAL_StatusTypeDef return_value;
} HalTimPwmInitMockValues;

HalTimPwmInitMockValues hal_tim_pwm_init_mock_values;

HAL_StatusTypeDef HAL_TIM_PWM_Init(TIM_HandleTypeDef *htim){
  hal_tim_pwm_init_mock_values.htim = htim;
  return hal_tim_pwm_init_mock_values.return_value;
}

typedef struct{
  TIM_HandleTypeDef *htim;
  uint32_t channel;
  HAL_StatusTypeDef return_value;
}HalTimPwmStartMockValues;

HalTimPwmStartMockValues hal_tim_pwm_start_mock_values;

HAL_StatusTypeDef HAL_TIM_PWM_Start(TIM_HandleTypeDef *htim, uint32_t Channel){
  hal_tim_pwm_start_mock_values.htim = htim;
  hal_tim_pwm_start_mock_values.channel = Channel;
  return hal_tim_pwm_start_mock_values.return_value;
}

#ifdef __cplusplus
}
#endif

#endif