#include "letodar_2204.hpp"
#include <utility>
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::NiceMock;
using ::testing::Return;

namespace {
class Letodar2204Tests : public ::testing::Test {
 protected:
  Letodar2204Tests() {}
  virtual void SetUp() {
    ON_CALL(*esc_, GetMaxPulseDurationInMicroSeconds).WillByDefault(Return(100));
    ON_CALL(*esc_, GetMinPulseDurationInMicroSeconds).WillByDefault(Return(10));
    ON_CALL(*esc_, SetPulseDuration).WillByDefault(Return(types::DriverStatus::OK));
  }

  virtual void ConfigureUnitUnderTest() {
    unit_under_test_ = std::make_unique<propulsion::LeTodar2204>(std::move(esc_));
  }

  std::unique_ptr<MockEsc> esc_ = std::make_unique<NiceMock<MockEsc>>();
  std::unique_ptr<propulsion::LeTodar2204> unit_under_test_;
};

TEST_F(Letodar2204Tests, get_current_speed_in_percent_works) {
  ConfigureUnitUnderTest();
  auto current_speed = unit_under_test_->GetCurrentSpeedInPercent();
  ASSERT_FLOAT_EQ(0.0, current_speed);
}

TEST_F(Letodar2204Tests, set_speed_in_percent_lower_illegal_bounds) {
  ConfigureUnitUnderTest();
  auto set_speed_return = unit_under_test_->SetSpeedInPercent(-1.0);
  ASSERT_EQ(types::DriverStatus::INPUT_ERROR, set_speed_return);
}

TEST_F(Letodar2204Tests, set_speed_in_percent_upper_illegal_bounds) {
  ConfigureUnitUnderTest();
  auto set_speed_return = unit_under_test_->SetSpeedInPercent(100.1);
  ASSERT_EQ(types::DriverStatus::INPUT_ERROR, set_speed_return);
}

TEST_F(Letodar2204Tests, set_speed_in_percent_legal_range) {
  ConfigureUnitUnderTest();
  auto set_speed_return = unit_under_test_->SetSpeedInPercent(50.0);
  ASSERT_EQ(types::DriverStatus::OK, set_speed_return);
}

TEST_F(Letodar2204Tests, set_speed_in_percent_hal_error_triggered) {
  EXPECT_CALL(*esc_, SetPulseDuration).WillOnce(Return(types::DriverStatus::HAL_ERROR));
  ConfigureUnitUnderTest();
  auto set_speed_return = unit_under_test_->SetSpeedInPercent(50.0);
  ASSERT_EQ(types::DriverStatus::HAL_ERROR, set_speed_return);
}
}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}