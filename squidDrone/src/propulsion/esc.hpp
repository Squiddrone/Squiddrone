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
      /// @brief  The single argument custom constructor is
      ///         the one to be used. 
      /// @param  timer The timer handle struct defined by hal driver 
      ///               stm32g4xx_hal_tim.h. 
      /// The only thing this constructor does, is to set the protected 
      /// member variable timer_.
      ///
      explicit Esc(TIM_HandleTypeDef& timer): timer_(timer){};

      ///
      /// @brief The default destructor is sufficent
      ///
      virtual ~Esc() = default;

      ///
      /// @brief Abstract method for returning the maximum pulse duration for the concrete ESC
      /// @return Pulse duration in microseconds. 
      ///
      virtual const auto GetMaxPulseDurationInMicroSeconds() const noexcept -> decltype(auto) = 0;

      ///
      /// @brief Abstract method for returning the minimum pulse duration for the concrete ESC
      /// @return Pulse duration in microseconds. 
      ///
      virtual const auto GetMinPulseDurationInMicroSeconds() const noexcept -> decltype(auto) = 0;

      ///
      /// @brief Abstract method for setting the pulse duration based on the min and max values
      /// @param pulse_duration Desired Pulse duration in microseconds
      /// @return A types::HalError type confirmation whether it was working or not
      ///
      virtual const auto SetPulseDuration(int pulse_duration) noexcept -> decltype(types::HalError::working) = 0;

    protected:
      ///
      /// Hal provided timer interface is protected, so
      /// the concrete implementation can use it.
      ///
      TIM_HandleTypeDef& timer_;
  };  

}






#endif