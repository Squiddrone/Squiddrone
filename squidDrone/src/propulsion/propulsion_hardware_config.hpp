#ifndef SRC_PROPULSION_PROPULSION_HARDWARE_CONFIG_HPP_
#define SRC_PROPULSION_PROPULSION_HARDWARE_CONFIG_HPP_

#include <cstdint>
#include "stm32g4xx.h"
#include "propulsion_hardware_types.hpp"

namespace propulsion{

  /**
   * @brief A type to accumulate all the info needed to build a Motor
   * 
   */
  struct PropulsionHardwareConfig{
    /// Deleted default Ctor to forbid using this one
    PropulsionHardwareConfig() = delete;

    /// Custom Ctor to correclty construct this type
    PropulsionHardwareConfig(types::MotorType motor_type, types::EscType esc_type, TIM_HandleTypeDef* timer, std::uint32_t channel)
    : motor_type(motor_type), esc_type(esc_type), timer(timer), channel(channel){}

    /// MotorType enum defines the kind of motor used
    types::MotorType motor_type;

    /// EscType enum defines the kind of esc used
    types::EscType esc_type;

    /// A pointer to a HAL timer object. Simple pointer is used for future compatability with HAL
    TIM_HandleTypeDef* timer;

    /// Channel as defined in HAL
    std::uint32_t channel;
  };
}

#endif