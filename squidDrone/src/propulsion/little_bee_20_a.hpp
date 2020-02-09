#ifndef SRC_PROPULSION_LITTLE_BEE_20_A_HPP_
#define SRC_PROPULSION_LITTLE_BEE_20_A_HPP_

#include "stm32g4xx.h"
#include "esc.hpp"


namespace propulsion{
  ///
  /// @class LittleBee20A 
  /// @brief The concrete class implementation of the abstract Esc class for
  /// the Little Bee 20 a hardware.
  ///
  class LittleBee20A final: public Esc{
    
    public:
      /// @brief Default constructor is deleted, because implementation need timer
      LittleBee20A() = delete;

      /// @brief Custom constructor with needed timer
      explicit LittleBee20A(TIM_HandleTypeDef& timer);

      const auto GetMaxPulseDurationInMicroSeconds() const noexcept -> decltype(auto) override;

      const auto GetMinPulseDurationInMicroSeconds() const noexcept -> decltype(auto) override;

      const auto SetPulseDuration(int pulse_duration) noexcept -> decltype(types::HalError::working) override;

  };

}

#endif