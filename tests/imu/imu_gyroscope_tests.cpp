#include "gtest/gtest.h"
#include "gyroscope.hpp"
#include "i2c.hpp"

namespace {

class GyroscopeTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    auto i2c_handler_ = std::make_unique<i2c::I2C>();
    types::GyroscopeSensitivity sensitivity = types::GyroscopeSensitivity::FINEST;
    unit_under_test_ = std::make_unique<imu::Gyroscope>(std::move(i2c_handler_), sensitivity);
  }

  std::unique_ptr<i2c::I2C> i2c_handler_;
  std::unique_ptr<imu::Gyroscope> unit_under_test_;
  uint8_t i2c_address_ = 0x10;
  uint8_t register_ = 0x20;
};

TEST_F(GyroscopeTests, gyroscope_SetSensitivity_finest) {
  auto gyroscope_sensitivity_return = unit_under_test_->SetSensitivity(types::GyroscopeSensitivity::FINEST);
  EXPECT_EQ(gyroscope_sensitivity_return, types::HalError::WORKING);
}

TEST_F(GyroscopeTests, gyroscope_SetSensitivity_finer) {
  auto gyroscope_sensitivity_return = unit_under_test_->SetSensitivity(types::GyroscopeSensitivity::FINER);
  EXPECT_EQ(gyroscope_sensitivity_return, types::HalError::WORKING);
}

TEST_F(GyroscopeTests, gyroscope_SetSensitivity_rougher) {
  auto gyroscope_sensitivity_return = unit_under_test_->SetSensitivity(types::GyroscopeSensitivity::ROUGHER);
  EXPECT_EQ(gyroscope_sensitivity_return, types::HalError::WORKING);
}

TEST_F(GyroscopeTests, gyroscope_SetSensitivity_roughest) {
  auto gyroscope_sensitivity_return = unit_under_test_->SetSensitivity(types::GyroscopeSensitivity::ROUGHEST);
  EXPECT_EQ(gyroscope_sensitivity_return, types::HalError::WORKING);
}

TEST_F(GyroscopeTests, gyroscope_Update) {
  unit_under_test_->Init(i2c_address_, register_);
  auto gyroscope_update_return = unit_under_test_->Update();
  EXPECT_EQ(gyroscope_update_return, types::HalError::WORKING);
}

TEST_F(GyroscopeTests, gyroscope_Update_without_Init_first) {
  auto gyroscope_update_return = unit_under_test_->Update();
  EXPECT_EQ(gyroscope_update_return, types::HalError::CONFIG_ERROR);
}

TEST_F(GyroscopeTests, gyroscope_Get_without_Update_and_Init_first) {
  types::EuclideanVector<float> expected_value{-1, -1, -1};
  auto gyroscope_get_return = unit_under_test_->Get();
  EXPECT_EQ(gyroscope_get_return.x, expected_value.x);
  EXPECT_EQ(gyroscope_get_return.y, expected_value.y);
  EXPECT_EQ(gyroscope_get_return.z, expected_value.z);
}

TEST_F(GyroscopeTests, gyroscope_Get_without_Update_first) {
  types::EuclideanVector<float> expected_value{0, 0, 0};
  unit_under_test_->Init(i2c_address_, register_);
  auto gyroscope_get_return = unit_under_test_->Get();
  EXPECT_EQ(gyroscope_get_return.x, expected_value.x);
  EXPECT_EQ(gyroscope_get_return.y, expected_value.y);
  EXPECT_EQ(gyroscope_get_return.z, expected_value.z);
}

TEST_F(GyroscopeTests, gyroscope_Get_with_Update_first) {
  types::EuclideanVector<float> expected_value{1.5, 2.5, 3.5};
  unit_under_test_->Init(i2c_address_, register_);
  unit_under_test_->Update();
  auto gyroscope_get_return = unit_under_test_->Get();
  EXPECT_EQ(gyroscope_get_return.x, expected_value.x);
  EXPECT_EQ(gyroscope_get_return.y, expected_value.y);
  EXPECT_EQ(gyroscope_get_return.z, expected_value.z);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}