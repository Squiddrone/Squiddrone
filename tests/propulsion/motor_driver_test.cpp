#include "motor_driver.hpp"
#include "esc_mock.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "letodar_2204_mock.hpp"
#include "motor.hpp"
#include "motor_builder_mock.hpp"

using ::testing::ByMove;
using ::testing::NiceMock;
using ::testing::Return;

namespace {
class MotorDriverTest : public ::testing::Test {
 protected:
  virtual void SetUp() override {
    ON_CALL(*builder_, Create).WillByDefault(Return(ByMove(std::make_unique<propulsion::MotorMock>())));
    unit_under_test_ = std::make_unique<propulsion::MotorDriver>(std::move(builder_));
  }

  std::unique_ptr<propulsion::MotorBuilder> builder_;
  std::unique_ptr<propulsion::MotorDriver> unit_under_test_;
};

TEST_F(MotorDriverTest, set_motor_speed_with_legal_motor_and_speed) {
  auto position = propulsion::MotorPosition::LEFT_FRONT;
  ASSERT_EQ(unit_under_test_->SetMotorSpeed(position, 50.0), types::DriverStatus::OK);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}