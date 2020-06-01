#include <set>
#include "motor_builder.hpp"

namespace propulsion{ 

  auto MotorBuilder::Create(propulsion::PropulsionHardwareConfig& motor_config) noexcept -> std::unique_ptr<Motor>{
    if(MotorConfigIsValid(motor_config)){
        /// good case
    }else{
      return nullptr;
    }
  }

  auto MotorBuilder::MotorConfigIsValid(propulsion::PropulsionHardwareConfig& motor_config) noexcept -> const bool{ 
    const std::set<std::uint32_t> possible_channels{TIM_CHANNEL_1, TIM_CHANNEL_2, TIM_CHANNEL_3, TIM_CHANNEL_4, TIM_CHANNEL_5, TIM_CHANNEL_6};
    const bool channel_is_in_possible_channels = possible_channels.find(motor_config.channel) != possible_channels.end(); 
    return (channel_is_in_possible_channels && motor_config.timer != nullptr);
  }
}