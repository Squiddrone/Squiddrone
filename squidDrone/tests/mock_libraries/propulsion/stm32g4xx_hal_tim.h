#ifndef TESTS_MOCK_LIBRARIES_STM32G4XX_HAL_TIM_H_
#define TESTS_MOCK_LIBRARIES_STM32G4XX_HAL_TIM_H_


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "stm32g4xx_hal_def.h"

#define NUM_RETURN_VALUES 2U

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

#define TIM_CHANNEL_1                      0x00000000U                          /*!< Capture/compare channel 1 identifier      */
#define TIM_CHANNEL_2                      0x00000004U                          /*!< Capture/compare channel 2 identifier      */
#define TIM_CHANNEL_3                      0x00000008U                          /*!< Capture/compare channel 3 identifier      */
#define TIM_CHANNEL_4                      0x0000000CU                          /*!< Capture/compare channel 4 identifier      */
#define TIM_CHANNEL_5                      0x00000010U                          /*!< Compare channel 5 identifier              */
#define TIM_CHANNEL_6                      0x00000014U                          /*!< Compare channel 6 identifier              */
#define TIM_CHANNEL_ALL                    0x0000003CU     

typedef struct {
  int test_member;
  TIM_Base_InitTypeDef Init;
  HAL_TIM_ActiveChannel Channel;
} TIM_HandleTypeDef;


typedef struct {
  TIM_HandleTypeDef* htim;
  uint32_t channel;
  int which_return;
  HAL_StatusTypeDef return_value[NUM_RETURN_VALUES];
} HalTimPwmStopMockValues;

extern HalTimPwmStopMockValues hal_tim_pwm_stop_mock_values;

HAL_StatusTypeDef HAL_TIM_PWM_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);

typedef struct {
  int timer_clock;
  int target_timer_clock_rate;
  uint32_t return_value;
}HalTimCalcPscMockValues;

extern HalTimCalcPscMockValues hal_tim_calc_psc_mock_values;

uint32_t __HAL_TIM_CALC_PSC(int timer_clock, int target_timer_clock_rate);

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

extern HalTimPwmConfigChannelMockValues hal_tim_pwm_config_channel_mock_values;

HAL_StatusTypeDef HAL_TIM_PWM_ConfigChannel(TIM_HandleTypeDef *htim, TIM_OC_InitTypeDef *sConfig, uint32_t Channel);

typedef struct{
  TIM_HandleTypeDef* htim;
  int which_return;
  HAL_StatusTypeDef return_value[NUM_RETURN_VALUES];
} HalTimPwmInitMockValues;

extern HalTimPwmInitMockValues hal_tim_pwm_init_mock_values;

HAL_StatusTypeDef HAL_TIM_PWM_Init(TIM_HandleTypeDef *htim);

typedef struct{
  TIM_HandleTypeDef *htim;
  uint32_t channel;
  HAL_StatusTypeDef return_value;
}HalTimPwmStartMockValues;

extern HalTimPwmStartMockValues hal_tim_pwm_start_mock_values;

HAL_StatusTypeDef HAL_TIM_PWM_Start(TIM_HandleTypeDef *htim, uint32_t Channel);

#ifdef __cplusplus
}
#endif

#endif