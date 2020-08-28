#include "esc_mock.hpp"

namespace propulsion {

auto Esc::SetPulseDuration(int pulse_duration, int repetition_period) noexcept -> types::DriverStatus {
  auto return_value = set_pulse_duration_return_value_;
  return return_value;
}
}  // namespace propulsion