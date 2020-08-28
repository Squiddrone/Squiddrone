#include "letodar_2204.hpp"

namespace propulsion {

auto LeTodar2204::GetCurrentSpeedInPercent() const noexcept -> const float {
  return speed_;
}

auto LeTodar2204::SetSpeedInPercent(const float speed) noexcept -> types::DriverStatus {
  auto upper_bounds_breached = speed > UPPER_LEGAL_RANGE_LIMIT_IN_PERCENT;
  auto lower_bounds_breached = speed < LOWER_LEGAL_RANGE_LIMIT_IN_PERCENT;
  if (upper_bounds_breached || lower_bounds_breached) {
    return types::DriverStatus::INPUT_ERROR;
  } else {
    speed_ = speed;
    auto max_pulse_duration = esc_->GetMaxPulseDurationInMicroSeconds();
    auto min_pulse_duration = esc_->GetMinPulseDurationInMicroSeconds();
    auto one_percent_in_ms = (max_pulse_duration - min_pulse_duration) / PERCENTAGE_FACTOR;
    auto speed_in_ms_pulse_duration = min_pulse_duration + (speed * one_percent_in_ms);
    auto set_pulse_error = esc_->SetPulseDuration(static_cast<int>(speed_in_ms_pulse_duration), REPETITION_TIME_IN_MS);
    if (set_pulse_error != types::DriverStatus::OK) {
      return types::DriverStatus::HAL_ERROR;
    } else {
      return types::DriverStatus::OK;
    }
  }
}
}  // namespace propulsion