#ifndef TESTS_MOCK_LIBRARIES_PROPULSION_LETODAR_2204_MOCK_HPP_
#define TESTS_MOCK_LIBRARIES_PROPULSION_LETODAR_2204_MOCK_HPP_

#include <memory>

#include "little_bee_20_a_mock.hpp"
#include "motor_mock.hpp"

namespace propulsion {
class LeTodar2204 : public Motor {
 public:
  explicit LeTodar2204(std::unique_ptr<Esc> esc) : Motor{std::move(esc)} {}
  auto GetCurrentSpeedInPercent() const noexcept -> const float override {
    return 1.0;
  }
  auto SetSpeedInPercent(const float speed) noexcept -> types::InputError override {
    return types::InputError::INPUT_CORRECT;
  }
};
}  // namespace propulsion

#endif