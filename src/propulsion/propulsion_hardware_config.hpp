#ifndef SRC_PROPULSION_PROPULSION_HARDWARE_CONFIG_HPP_
#define SRC_PROPULSION_PROPULSION_HARDWARE_CONFIG_HPP_

#include <cstdint>

#include "propulsion_hardware_types.hpp"
#include "stm32g4xx.h"

namespace propulsion {

/**
 * @brief A type to accumulate all the info needed to build a Motor
 * 
 */
struct PropulsionHardwareConfig {
  /// Deleted default constructor to forbid using this one
  PropulsionHardwareConfig() = delete;

  /// Custom constructor to correclty construct this type
  PropulsionHardwareConfig(types::MotorType motor_type, types::EscType esc_type, TIM_HandleTypeDef* timer, std::uint32_t channel)
      : motor_type(motor_type), esc_type(esc_type), timer(timer), channel(channel) {}

  /// MotorType enum defines the kind of motor used
  types::MotorType motor_type;

  /// EscType enum defines the kind of esc used
  types::EscType esc_type;

  /// A pointer to a HAL timer object. Simple pointer is used for future compatibility with HAL
  TIM_HandleTypeDef* timer;

  /**
   * @brief Channel as defined in HAL (see below)
   *  TIM_CHANNEL_1 0x00000000U                          
   *  TIM_CHANNEL_2 0x00000004U                          
   *  TIM_CHANNEL_3 0x00000008U                        
   *  TIM_CHANNEL_4 0x0000000CU                              
   *  TIM_CHANNEL_5 0x00000010U                                       
   *  TIM_CHANNEL_6 0x00000014U                                      
   */
  std::uint32_t channel;
};
}  // namespace propulsion

#endif