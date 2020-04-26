#ifndef SRC_PROPULSION_ESC_HPP_
#define SRC_PROPULSION_ESC_HPP_

#include "stm32g4xx.h"
#include "error_types.hpp"

namespace propulsion{

  ///
  /// @class Esc 
  /// @brief The abstract Esc provides a interface for concrete Esc's to implement
  /// The Esc abstract interface dictates the methods which all concrete Esc's have to
  /// implement. 
  ///
  class Esc{
    public:
      ///
      /// @brief  Default constructor may not be used, so
      ///         it is deleted.
      ///
      Esc() = delete;

      ///
      /// @brief  The custom constructor is
      ///         the one to be used. 
      /// @param  timer The timer handle struct defined by hal driver 
      ///               stm32g4xx_hal_tim.h. 
      /// @param  channel The used channel for this timer
      /// The only thing this constructor does, is to set the protected 
      /// member variables timer_ and channel_.
      ///
      explicit Esc(TIM_HandleTypeDef* timer, std::uint32_t channel): timer_(timer), channel_(channel){};

      ///
      /// @brief The default destructor is sufficent
      ///
      virtual ~Esc() = default;

      ///
      /// @brief Abstract method for returning the maximum pulse duration for the concrete ESC
      /// @return Pulse duration in microseconds. 
      ///
      virtual const auto GetMaxPulseDurationInMicroSeconds() const noexcept -> int = 0;

      ///
      /// @brief Abstract method for returning the minimum pulse duration for the concrete ESC
      /// @return Pulse duration in microseconds. 
      ///
      virtual const auto GetMinPulseDurationInMicroSeconds() const noexcept -> int = 0;

      ///
      /// @brief Abstract method for setting the pulse duration based on the min and max values
      /// @param pulse_duration Desired Pulse duration in microseconds
      /// @param repetition_period Desired time until pulse is repeated
      /// @return A types::HalError type confirmation whether it was working or not
      ///
      virtual const auto SetPulseDuration(int pulse_duration, int repetition_period) noexcept -> types::HalError = 0;

    protected:
      ///
      /// Hal provided timer interface is protected, so
      /// the concrete implementation can use it.
      ///
      TIM_HandleTypeDef* timer_;

      /// The used channel number as can be seen stm32g4xx_hal_tim.h
      std::uint32_t channel_;
  };  

}






#endif