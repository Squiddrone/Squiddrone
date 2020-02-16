#include "little_bee_20_a.hpp"
#include "globals.hpp"

namespace propulsion{

  const auto LittleBee20A::SetPulseDuration(int pulse_duration, int repetition_period) noexcept -> types::HalError{
    types::HalError error_state;
    const bool pulse_limit_breach = pulse_duration > ONESHOT_125_MAX_PULSE_DURATION_IN_US_ || pulse_duration < ONESHOT_125_MIN_PULSE_DURATION_IN_US_;
    const bool period_limit_breach = repetition_period < pulse_duration || repetition_period > MAX_REPETITION_PERIOD_;
    if(pulse_limit_breach || period_limit_breach){
      return types::HalError::PARAMETER_ERROR;
    }else{
      if(!timer_is_configured_){
        auto configuration_error_state = ConfigureTimer();
        if(configuration_error_state != types::HalError::WORKING){
          return types::HalError::CONFIG_ERROR;
        }
      }
      const std::uint32_t pulse_duration_in_ticks = static_cast<std::uint32_t>(pulse_duration * TICKS_PER_MICROSECOND_);
      const std::uint32_t period = static_cast<std::uint32_t>(repetition_period * TICKS_PER_MICROSECOND_);
      error_state = SetPwm(period, pulse_duration_in_ticks);
    }
    return error_state;
  }

  const auto LittleBee20A::ConfigureTimer() noexcept -> types::HalError{
    if(HAL_TIM_PWM_Stop(timer_, timer_->Channel) != HAL_OK){
      return types::HalError::CONFIG_ERROR;
    }
    uint32_t prescaler_10_mhz = __HAL_TIM_CALC_PSC(TIMER_CLOCK, TARGET_TIMER_CLOCK_RATE_); //calculate timer input clock
    timer_->Init.Prescaler = prescaler_10_mhz;
    if(HAL_TIM_PWM_Init(timer_) != HAL_OK){
      return types::HalError::CONFIG_ERROR;
    }
    timer_is_configured_ = true;
    return types::HalError::WORKING;
  }

  const auto LittleBee20A::SetPwm(std::uint32_t period, std::uint32_t pulse) const noexcept -> types::HalError{
    if(HAL_TIM_PWM_Stop(timer_, timer_->Channel) != HAL_OK){
      return types::HalError::CONFIG_ERROR;
    }
    TIM_OC_InitTypeDef new_timer_configuration = {0};
    timer_->Init.Period = period;
    if(HAL_TIM_PWM_Init(timer_) != HAL_OK){
      return types::HalError::CONFIG_ERROR;
    }
    new_timer_configuration.OCMode = TIM_OCMODE_PWM1;
    new_timer_configuration.Pulse = pulse;
    new_timer_configuration.OCPolarity = TIM_OCPOLARITY_HIGH;
    new_timer_configuration.OCFastMode = TIM_OCFAST_DISABLE;
    if(HAL_TIM_PWM_ConfigChannel(timer_, &new_timer_configuration, timer_->Channel) != HAL_OK){
      return types::HalError::CONFIG_ERROR;
    }
    if(HAL_TIM_PWM_Start(timer_, timer_->Channel) != HAL_OK){
      return types::HalError::CONFIG_ERROR;
    }
    return types::HalError::WORKING;
  }
}