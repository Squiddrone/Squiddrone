#ifndef TESTS_MOCK_LIBRARIES_PROPULSION_ESC_MOCK_HPP
#define TESTS_MOCK_LIBRARIES_PROPULSION_ESC_MOCK_HPP
#include "error_types.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace propulsion {
class Esc {
 public:
  virtual auto GetMaxPulseDurationInMicroSeconds() const noexcept -> decltype(auto) {
    return 100;
  }

  virtual auto GetMinPulseDurationInMicroSeconds() const noexcept -> decltype(auto) {
    return 10;
  }

  auto SetPulseDuration(int pulse_duration, int repetition_period) noexcept -> types::DriverStatus;

  types::DriverStatus set_pulse_duration_return_value_ = types::DriverStatus::OK;
};
}  // namespace propulsion
class MockEsc : public propulsion::Esc {
 public:
  MockEsc() {}
  MockEsc(MockEsc&) {}
  MOCK_METHOD0(GetMaxPulseDurationInMicroSeconds, int());
  MOCK_METHOD0(GetMinPulseDurationInMicroSeconds, int());
  MOCK_METHOD2(SetPulseDuration, types::DriverStatus(int, int));
};

#endif