#ifndef TESTS_MOCK_LIBRARIES_PROPULSION_ESC_MOCK_HPP
#define TESTS_MOCK_LIBRARIES_PROPULSION_ESC_MOCK_HPP
#include "error_types.hpp"

namespace propulsion {
class Esc {
 public:
  auto GetMaxPulseDurationInMicroSeconds() const noexcept -> decltype(auto) {
    return 100;
  }

  auto GetMinPulseDurationInMicroSeconds() const noexcept -> decltype(auto) {
    return 10;
  }

  auto SetPulseDuration(int pulse_duration, int repetition_period) noexcept -> types::DriverStatus;

  types::DriverStatus set_pulse_duration_return_value_ = types::DriverStatus::OK;
};
}  // namespace propulsion

#endif