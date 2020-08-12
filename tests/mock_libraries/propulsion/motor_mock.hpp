#ifndef TESTS_MOCK_LIBRARIES_PROPULSION_MOTOR_MOCK_HPP_
#define TESTS_MOCK_LIBRARIES_PROPULSION_MOTOR_MOCK_HPP_

#include <memory>

#include "esc_mock.hpp"

namespace propulsion {
class Motor {
 public:
  explicit Motor(std::unique_ptr<Esc> esc) : esc_{std::move(esc)}, is_created_{true} {}
  std::unique_ptr<Esc> esc_;
  bool is_created_ = false;
  virtual auto GetCurrentSpeedInPercent() const noexcept -> const float = 0;
  virtual auto SetSpeedInPercent(const float speed) noexcept -> types::DriverStatus = 0;
};
}  // namespace propulsion

#endif