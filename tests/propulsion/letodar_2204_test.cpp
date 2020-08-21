#include "letodar_2204.hpp"
#include <utility>
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace {
class Letodar2204Tests : public ::testing::Test {
 protected:
  Letodar2204Tests() {}
  virtual void SetUp() {
    EXPECT_CALL(esc_, GetMaxPulseDurationInMicroSeconds()).Times(1).WillOnce(::testing::Return(1));
    unit_under_test_ = std::make_unique<propulsion::LeTodar2204>(std::unique_ptr<MockEsc>(esc_));
  }

  MockEsc esc_;
  std::unique_ptr<propulsion::LeTodar2204> unit_under_test_;
};

TEST_F(Letodar2204Tests, get_current_speed_in_percent_works) {
  auto current_speed = unit_under_test_->GetCurrentSpeedInPercent();
  ASSERT_FLOAT_EQ(0.0, current_speed);
}

TEST_F(Letodar2204Tests, set_speed_in_percent_lower_illegal_bounds) {
  auto set_speed_return = unit_under_test_->SetSpeedInPercent(-1.0);
  ASSERT_EQ(types::DriverStatus::INPUT_ERROR, set_speed_return);
}

// // TEST_F(Letodar2204Tests, set_speed_in_percent_upper_illegal_bounds) {
// //   auto set_speed_return = unit_under_test_->SetSpeedInPercent(100.1);
// //   ASSERT_EQ(types::DriverStatus::INPUT_ERROR, set_speed_return);
// // }

TEST_F(Letodar2204Tests, set_speed_in_percent_legal_range) {
  auto set_speed_return = unit_under_test_->SetSpeedInPercent(50.0);
  ASSERT_EQ(types::DriverStatus::OK, set_speed_return);
}

// TEST_F(Letodar2204Tests, set_speed_in_percent_hal_error_triggered) {
//   auto set_speed_return = unit_under_test_->SetSpeedInPercent(50.0);
//   ASSERT_EQ(types::DriverStatus::HAL_ERROR, set_speed_return);
// }
}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}