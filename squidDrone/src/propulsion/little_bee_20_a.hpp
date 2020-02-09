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
      
      /// 
      /// @brief Implementation of abstract method for getting max pulse duration.  
      /// Needs to be defined in header, because of type deduction.
      /// @return Oneshot 125 maximum pulse duration for full throttle
      ///
      const auto GetMaxPulseDurationInMicroSeconds() const noexcept -> decltype(auto) override{
          return oneshot_125_max_pulse_duration_in_us_;
      }

      /// 
      /// @brief Implementation of abstract method for getting min pulse duration.  
      /// Needs to be defined in header, because of type deduction.
      /// @return Oneshot 125 minimum pulse duration for no throttle
      ///
      const auto GetMinPulseDurationInMicroSeconds() const noexcept -> decltype(auto) override{
          return oneshot_125_min_pulse_duration_in_us_;
      }

      ///
      /// @brief Sets the new pulse duration for he next cycle.
      /// Can be calculated using min and max pulse duration of oneshot 125
      /// @return types::HalError::working if the is no error
      ///         types::HalError::parameter_change_error if new pulse duration didn't work
      ///
      const auto SetPulseDuration(int pulse_duration) noexcept -> decltype(types::HalError::working) override;
    
    private:
      static constexpr int oneshot_125_max_pulse_duration_in_us_ = 250;
      static constexpr int oneshot_125_min_pulse_duration_in_us_ = 125;
  };

}

#endif