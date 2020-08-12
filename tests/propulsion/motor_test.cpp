#include "motor.hpp"
#include <memory>
#include <utility>
#include "gtest/gtest.h"

namespace {

class ConcreteMotor final : public propulsion::Motor {
 public:
  using propulsion::Motor::esc_;
  float speed_;

  explicit ConcreteMotor() : propulsion::Motor(std::make_unique<propulsion::Esc>()), speed_(1) {}

  auto GetCurrentSpeedInPercent() const noexcept -> const float override {
    return static_cast<float>(10.1);
  }

  auto SetSpeedInPercent(const float speed) noexcept -> types::DriverStatus override {
    speed_ = speed;
    return types::DriverStatus::OK;
  }
};

TEST(motor_test, is_constructible) {
  ConcreteMotor unit_under_test{};
  ASSERT_FLOAT_EQ(1, unit_under_test.speed_);
}

TEST(motor_test, set_current_speed) {
  ConcreteMotor unit_under_test{};
  unit_under_test.SetSpeedInPercent(20.2);
  ASSERT_FLOAT_EQ(20.2, unit_under_test.speed_);
}

TEST(motor_test, get_current_speed) {
  ConcreteMotor unit_under_test{};
  ASSERT_FLOAT_EQ(10.1, unit_under_test.GetCurrentSpeedInPercent());
}

TEST(motor_test, set_current_speed_input_correct) {
  ConcreteMotor unit_under_test{};
  ASSERT_EQ(types::DriverStatus::OK, unit_under_test.SetSpeedInPercent(10.2));
}
}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}