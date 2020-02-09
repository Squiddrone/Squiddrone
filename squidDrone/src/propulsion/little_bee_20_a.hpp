#ifndef SRC_PROPULSION_LITTLE_BEE_20_A_HPP_
#define SRC_PROPULSION_LITTLE_BEE_20_A_HPP_

#include "stm32g4xx.h"
#include "esc.hpp"


namespace propulsion{
    
  class LittleBee20A final: public Esc{
    
    public:
      
      LittleBee20A() = delete;

      explicit LittleBee20A(TIM_HandleTypeDef& timer);

      const auto GetMaxPulseDurationInMicroSeconds() const noexcept -> decltype(auto);

      const auto GetMinPulseDurationInMicroSeconds() const noexcept -> decltype(auto);

      const auto SetPulseDuration(int pulse_duration) noexcept -> decltype(types::HalError::working);

  };

}

#endif