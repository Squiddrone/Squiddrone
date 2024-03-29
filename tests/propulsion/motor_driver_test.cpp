#include "motor_driver.hpp"
#include <array>
#include "esc_mock.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "letodar_2204_mock.hpp"
#include "motor.hpp"
#include "motor_builder_mock.hpp"

using ::testing::_;
using ::testing::Between;
using ::testing::NiceMock;
using ::testing::Return;
namespace {

struct MotorSpeedFloatFactory {
 public:
  MotorSpeedFloatFactory() = default;
  float GetSpeed() {
    if (i > MAX_I_) {
      i = MAX_I_;
    }
    auto result = subsequent_speeds.at(i);
    i++;
    return result;
  }

 private:
  static constexpr int MAX_I_ = 1;
  int i = 0;
  std::array<float, 2> subsequent_speeds = {50.0, -1.0};
};

class MotorDriverTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    ON_CALL(*builder_, Create).WillByDefault([&](propulsion::PropulsionHardwareConfig &) {
      std::unique_ptr<NiceMock<propulsion::MotorMock>> motor = std::make_unique<NiceMock<propulsion::MotorMock>>();
      ON_CALL(*motor, SetSpeedInPercent).WillByDefault(Return(types::DriverStatus::OK));
      ON_CALL(*motor, SetSpeedInPercent(66.6)).WillByDefault(Return(types::DriverStatus::HAL_ERROR));
      ON_CALL(*motor, GetCurrentSpeedInPercent).WillByDefault([&]() {
        return float_factory_.GetSpeed();
      });
      return motor;
    });
  }

  auto CreateUnitUnderTest() -> void {
    unit_under_test_ = std::make_unique<propulsion::MotorDriver>(std::move(builder_));
  }

  auto MotorFailsSetSpeedAtCall(const int which_call) -> const void {
    ON_CALL(*builder_, Create).WillByDefault([=](propulsion::PropulsionHardwareConfig &) {
      std::unique_ptr<NiceMock<propulsion::MotorMock>> motor = std::make_unique<NiceMock<propulsion::MotorMock>>();
      if (which_call == 1) {
        EXPECT_CALL(*motor, SetSpeedInPercent(_))
            .Times(Between(0, 1))
            .WillOnce(Return(types::DriverStatus::HAL_ERROR));
      } else if (which_call == 2) {
        EXPECT_CALL(*motor, SetSpeedInPercent(_))
            .Times(Between(1, 2))
            .WillOnce(Return(types::DriverStatus::OK))
            .WillOnce(Return(types::DriverStatus::HAL_ERROR));
      } else if (which_call == 3) {
        EXPECT_CALL(*motor, SetSpeedInPercent(_))
            .Times(Between(2, 3))
            .WillOnce(Return(types::DriverStatus::OK))
            .WillOnce(Return(types::DriverStatus::OK))
            .WillOnce(Return(types::DriverStatus::HAL_ERROR));
      } else {
        EXPECT_CALL(*motor, SetSpeedInPercent(_))
            .WillRepeatedly(Return(types::DriverStatus::OK));
      }
      return motor;
    });
  }

  static constexpr float DEFAULT_SPEED_ = 50.0;
  MotorSpeedFloatFactory float_factory_;
  std::unique_ptr<NiceMock<MockMotorBuilder>> builder_ = std::make_unique<NiceMock<MockMotorBuilder>>();
  std::unique_ptr<propulsion::MotorDriver> unit_under_test_;
};

TEST_F(MotorDriverTest, set_motor_speed_with_legal_motor_and_speed) {
  CreateUnitUnderTest();
  auto position = propulsion::MotorPosition::LEFT_FRONT;
  ASSERT_EQ(unit_under_test_->SetMotorSpeed(position, 50.0), types::DriverStatus::OK);
}

TEST_F(MotorDriverTest, set_motor_speed_with_illegal_lower_bounds_speed) {
  CreateUnitUnderTest();
  auto position = propulsion::MotorPosition::LEFT_REAR;
  ASSERT_EQ(unit_under_test_->SetMotorSpeed(position, -1.0), types::DriverStatus::INPUT_ERROR);
}

TEST_F(MotorDriverTest, set_motor_speed_with_illegal_upper_bounds_speed) {
  CreateUnitUnderTest();
  auto position = propulsion::MotorPosition::RIGHT_FRONT;
  ASSERT_EQ(unit_under_test_->SetMotorSpeed(position, 101.0), types::DriverStatus::INPUT_ERROR);
}

TEST_F(MotorDriverTest, set_motor_speed_with_legal_lower_bounds_speed) {
  CreateUnitUnderTest();
  auto position = propulsion::MotorPosition::RIGHT_REAR;
  ASSERT_EQ(unit_under_test_->SetMotorSpeed(position, 0.0), types::DriverStatus::OK);
}

TEST_F(MotorDriverTest, set_motor_speed_with_legal_upper_bounds_speed) {
  CreateUnitUnderTest();
  auto position = propulsion::MotorPosition::LEFT_FRONT;
  ASSERT_EQ(unit_under_test_->SetMotorSpeed(position, 100.0), types::DriverStatus::OK);
}

TEST_F(MotorDriverTest, set_motor_speed_hal_error) {
  CreateUnitUnderTest();
  auto position = propulsion::MotorPosition::LEFT_FRONT;
  ASSERT_EQ(unit_under_test_->SetMotorSpeed(position, 66.6), types::DriverStatus::HAL_ERROR);
}

TEST_F(MotorDriverTest, get_motor_speed_get_legal_speed) {
  CreateUnitUnderTest();
  auto position = propulsion::MotorPosition::LEFT_FRONT;
  auto result = unit_under_test_->GetMotorSpeed(position);
  ASSERT_FLOAT_EQ(result.second, DEFAULT_SPEED_);
}

TEST_F(MotorDriverTest, get_motor_speed_get_legal_status) {
  CreateUnitUnderTest();
  auto position = propulsion::MotorPosition::LEFT_FRONT;
  auto result = unit_under_test_->GetMotorSpeed(position);
  ASSERT_EQ(result.first, types::DriverStatus::OK);
}

TEST_F(MotorDriverTest, get_motor_speed_get_illegal_speed) {
  CreateUnitUnderTest();
  auto position = propulsion::MotorPosition::LEFT_FRONT;
  auto result = unit_under_test_->GetMotorSpeed(position);  //for using the MotorSpeedFloatFactory as intended
  result = unit_under_test_->GetMotorSpeed(position);
  ASSERT_FLOAT_EQ(result.second, -1.0);
}

TEST_F(MotorDriverTest, get_motor_speed_get_illegal_status) {
  CreateUnitUnderTest();
  auto position = propulsion::MotorPosition::LEFT_FRONT;
  auto result = unit_under_test_->GetMotorSpeed(position);  //for using the MotorSpeedFloatFactory as intended
  result = unit_under_test_->GetMotorSpeed(position);
  ASSERT_EQ(result.first, types::DriverStatus::HAL_ERROR);
}

TEST_F(MotorDriverTest, arm_escs_everything_works) {
  CreateUnitUnderTest();
  auto status = unit_under_test_->ArmEscs();
  ASSERT_EQ(status, types::DriverStatus::OK);
}

TEST_F(MotorDriverTest, arm_escs_first_set_speed_fails) {
  MotorFailsSetSpeedAtCall(1);
  CreateUnitUnderTest();
  auto status = unit_under_test_->ArmEscs();
  ASSERT_EQ(status, types::DriverStatus::HAL_ERROR);
}

TEST_F(MotorDriverTest, arm_escs_second_set_speed_fails) {
  MotorFailsSetSpeedAtCall(2);
  CreateUnitUnderTest();
  auto status = unit_under_test_->ArmEscs();
  ASSERT_EQ(status, types::DriverStatus::HAL_ERROR);
}

TEST_F(MotorDriverTest, arm_escs_last_set_speed_fails) {
  MotorFailsSetSpeedAtCall(3);
  CreateUnitUnderTest();
  auto status = unit_under_test_->ArmEscs();
  ASSERT_EQ(status, types::DriverStatus::HAL_ERROR);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}