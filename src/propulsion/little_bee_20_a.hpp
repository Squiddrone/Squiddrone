#ifndef SRC_PROPULSION_LITTLE_BEE_20_A_HPP_
#define SRC_PROPULSION_LITTLE_BEE_20_A_HPP_

#include "cstdint"
#include "esc.hpp"
#include "stm32g4xx.h"

namespace propulsion {
/**
 * @brief The concrete class implementation of the abstract Esc class for
 * the Little Bee 20 a hardware.
 * 
 */
class LittleBee20A final : public Esc {
 public:
  /// @brief Default constructor is deleted, because implementation need timer
  LittleBee20A() = delete;

  /// @brief Destructor is set to default, because there is nothing out of the ordinary to do
  ~LittleBee20A() = default;

  /**
   * @brief Custom constructor with needed timer pointer
   * Raw pointer will be used in order to comply with C HAL
   * @param timer See ESC.hpp
   * @param channel See ESC.hpp
   * 
   */
  explicit LittleBee20A(TIM_HandleTypeDef* timer, std::uint32_t channel) : Esc(timer, channel), timer_is_configured_(false) {}

  /**
   * @brief Implementation of abstract method for getting max pulse duration.  
   * Needs to be defined in header, because of type deduction.
   * @return Oneshot 125 maximum pulse duration for full throttle
   * 
   */
  const auto GetMaxPulseDurationInMicroSeconds() const noexcept -> int override {
    return ONESHOT_125_MAX_PULSE_DURATION_IN_US_;
  }

  /**
   * @brief Implementation of abstract method for getting min pulse duration.  
   * Needs to be defined in header, because of type deduction.
   * @return Oneshot 125 minimum pulse duration for no throttle
   * 
   */
  const auto GetMinPulseDurationInMicroSeconds() const noexcept -> int override {
    return ONESHOT_125_MIN_PULSE_DURATION_IN_US_;
  }

  /**
   * @brief Sets the new pulse duration for he next cycle.
   * Can be calculated using min and max pulse duration of oneshot 125.
   *        _____               _____
   * 1     |     |             |     |
   * 0 ____|     |_____________|     |______
   *       ^-----^ pulse_duration
   *       ^-------------------^ repetition_period
   * @param pulse_duration The Oneshot125 pulse duration (125us - 250us)
   * @param repetition_period Time between pulses in microseconds (pulse_duration - 20ms)
   * @return types::HalError::working if there is no error
   *         types::HalError::parameter_error if new pulse duration didn't work
   *         types::HalError::config_error if timer config didn't work
   * 
   */
  const auto SetPulseDuration(int pulse_duration, int repetition_period) noexcept -> types::HalError override;

 private:
  static constexpr auto ONESHOT_125_MAX_PULSE_DURATION_IN_US_ = 250;
  static constexpr auto ONESHOT_125_MIN_PULSE_DURATION_IN_US_ = 125;
  static constexpr auto MAX_REPETITION_PERIOD_ = 20000;
  static constexpr auto TARGET_TIMER_CLOCK_RATE_ = 10000000;
  static constexpr auto MICROSECONDS_PER_SECOND_ = 1000000;
  static constexpr auto TICKS_PER_MICROSECOND_ = TARGET_TIMER_CLOCK_RATE_ / MICROSECONDS_PER_SECOND_;

  /**
   * @brief Does the initial reconfiguration based on prescaler
   * @return types::HalError::working if everything went fine
   *         types::HalError::config_error if an error occured
   * 
   */
  const auto ConfigureTimer() noexcept -> types::HalError;

  /**
   * @brief Set Oneshot125 pulse and period
   * The actual timer period and pulse length is calculated using MCU_CLOCK and its dividers.
   * Timer clock sources are either APB1 or APB2.
   * __HAL_TIM_CALC_PULSE helps with calculation
   * @param period The actual period count for setting PWM period.
   * @param pulse The actual pulse PWM pulse count number.
   * @return types::HalError::working if everything went fine
   *         types::HalError::config_error if an error occured
   * 
   */
  const auto SetPwm(std::uint32_t period, std::uint32_t pulse) const noexcept -> types::HalError;

  bool timer_is_configured_;
};

}  // namespace propulsion

#endif