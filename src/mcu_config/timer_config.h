#ifndef SRC_MCU_CONFIG_TIMER_CONFIG_H_
#define SRC_MCU_CONFIG_TIMER_CONFIG_H_


#ifdef __cplusplus
	extern "C" {
#endif

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim16;
extern TIM_HandleTypeDef htim17;

void MX_TIM2_Init(void);
void MX_TIM3_Init(void);
void MX_TIM4_Init(void);
void MX_TIM16_Init(void);
void MX_TIM17_Init(void);

#ifdef __cplusplus
	}
#endif


#endif
