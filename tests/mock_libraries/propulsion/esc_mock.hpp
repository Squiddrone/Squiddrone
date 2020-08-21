#ifndef TESTS_MOCK_LIBRARIES_PROPULSION_ESC_MOCK_HPP
#define TESTS_MOCK_LIBRARIES_PROPULSION_ESC_MOCK_HPP
#include "error_types.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace propulsion {
class Esc {
 public:
  Esc() = default;
  virtual ~Esc() {}
  virtual auto GetMaxPulseDurationInMicroSeconds() const noexcept -> int {
    return 100;
  }

  virtual auto GetMinPulseDurationInMicroSeconds() const noexcept -> int {
    return 10;
  }

  virtual auto SetPulseDuration(int pulse_duration, int repetition_period) noexcept -> types::DriverStatus {
    return types::DriverStatus::OK;
  }

  types::DriverStatus set_pulse_duration_return_value_ = types::DriverStatus::OK;
};
}  // namespace propulsion
class MockEsc : public propulsion::Esc {
 public:
  MockEsc() {}
  MockEsc(const MockEsc&) {}
  MOCK_METHOD(int, GetMaxPulseDurationInMicroSeconds, (), (const, noexcept, override));
  MOCK_METHOD(int, GetMinPulseDurationInMicroSeconds, (), (const, noexcept, override));
  MOCK_METHOD(types::DriverStatus, SetPulseDuration, (int pulse_duration, int repetition_period), (noexcept, override));
};

#endif