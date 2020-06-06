#ifndef TESTS_MOCK_LIBRARIES_PROPULSION_PROPULSION_HARDWARE_CONFIG_MOCK_HPP_
#define TESTS_MOCK_LIBRARIES_PROPULSION_PROPULSION_HARDWARE_CONFIG_MOCK_HPP_

#include "stm32g4xx_hal_tim.h"

namespace types {

enum class MotorType : int {
  LETODAR_2204,
};

enum class EscType : int {
  LITTLE_BEE_20_A,
};

}  // namespace types

namespace propulsion {

struct PropulsionHardwareConfig {
  types::MotorType motor_type;
  types::EscType esc_type;
  TIM_HandleTypeDef* timer;
  int channel;
};
}  // namespace propulsion

#endif