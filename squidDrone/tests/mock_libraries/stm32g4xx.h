#ifndef TESTS_MOCK_LIBRARIES_STM32G4XX_HAL_TIM_H_
#define TESTS_MOCK_LIBRARIES_STM32G4XX_HAL_TIM_H_

using TIM_HandleTypeDef = struct TimerType{
    int test_member;
};

#endif