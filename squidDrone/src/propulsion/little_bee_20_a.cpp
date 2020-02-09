#include "little_bee_20_a.hpp"
#include "globals.hpp"

namespace propulsion{

  const auto LittleBee20A::SetPulseDuration(int pulse_duration, int repetition_period) noexcept -> types::HalError{
    types::HalError error_state;
    const bool pulse_limit_breach = pulse_duration > oneshot_125_max_pulse_duration_in_us_ || pulse_duration < oneshot_125_min_pulse_duration_in_us_;
    const bool period_limit_breach = repetition_period < pulse_duration || repetition_period > max_repetition_period_;
    if(pulse_limit_breach || period_limit_breach){
      error_state = types::HalError::parameter_error;
    }else{
      if(!timer_is_configured_){
          error_state = ConfigureTimer();
      }
      const std::uint32_t pulse_duration_in_ticks = pulse_duration * ticks_per_us_;
      const std::uint32_t period = repetition_period * ticks_per_us_;
      error_state = SetPwm(period, pulse_duration_in_ticks);
    }
    return error_state;
  }

  const auto LittleBee20A::ConfigureTimer() noexcept -> types::HalError{
    types::HalError error_state = types::HalError::working;
    if(HAL_TIM_PWM_Stop(timer_, timer_->Channel) != HAL_OK){
      error_state = types::HalError::config_error;
    }
    uint32_t prescaler_10_mhz = __HAL_TIM_CALC_PSC(TIMER_CLOCK, target_timer_clock_rate_); //calculate timer input clock
    timer_->Init.Prescaler = prescaler_10_mhz;
    if(HAL_TIM_PWM_Init(timer_) != HAL_OK){
      error_state = types::HalError::config_error;
    }
    timer_is_configured_ = true;
    return error_state;
  }

  const auto LittleBee20A::SetPwm(std::uint32_t period, std::uint32_t pulse) const noexcept -> types::HalError{
    types::HalError error_state = types::HalError::working;
    if(HAL_TIM_PWM_Stop(timer_, timer_->Channel) != HAL_OK){
      error_state = types::HalError::config_error;
    }
    TIM_OC_InitTypeDef new_timer_configuration = {0};
    timer_->Init.Period = period;
    if(HAL_TIM_PWM_Init(timer_) != HAL_OK){
      error_state = types::HalError::config_error;
    }
    new_timer_configuration.OCMode = TIM_OCMODE_PWM1;
    new_timer_configuration.Pulse = pulse;
    new_timer_configuration.OCPolarity = TIM_OCPOLARITY_HIGH;
    new_timer_configuration.OCFastMode = TIM_OCFAST_DISABLE;
    if(HAL_TIM_PWM_ConfigChannel(timer_, &new_timer_configuration, timer_->Channel) != HAL_OK){
      error_state = types::HalError::config_error;
    }
    if(HAL_TIM_PWM_Start(timer_, timer_->Channel) != HAL_OK){
      error_state = types::HalError::config_error;
    }
    return error_state;
  }
}