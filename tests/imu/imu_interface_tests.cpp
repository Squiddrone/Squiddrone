#include "gtest/gtest.h"
#include "i2c.hpp"
#include "inertial_measurement.hpp"

namespace {

class ImuInterfaceTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    auto i2c_handler_ = std::make_unique<i2c::I2C>();
    unit_under_test_ = std::make_unique<imu::InertialMeasurement>(std::move(i2c_handler_));
  }

  std::unique_ptr<i2c::I2C> i2c_handler_;
  std::unique_ptr<imu::InertialMeasurement> unit_under_test_;
};

TEST_F(ImuInterfaceTests, interface_set_gyroscope_sensitivity_finest) {
  auto sensitivity = types::GyroscopeSensitivity::FINEST;
  unit_under_test_->SetGyroscopeSensitivity(sensitivity);
  auto gyroscope_sensitivity_return = unit_under_test_->GetGyroscopeSensitivity();
  EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
}

TEST_F(ImuInterfaceTests, interface_set_gyroscope_sensitivity_finer) {
  auto sensitivity = types::GyroscopeSensitivity::FINER;
  unit_under_test_->SetGyroscopeSensitivity(sensitivity);
  auto gyroscope_sensitivity_return = unit_under_test_->GetGyroscopeSensitivity();
  EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
}

TEST_F(ImuInterfaceTests, interface_set_gyroscope_sensitivity_rougher) {
  auto sensitivity = types::GyroscopeSensitivity::ROUGHER;
  unit_under_test_->SetGyroscopeSensitivity(sensitivity);
  auto gyroscope_sensitivity_return = unit_under_test_->GetGyroscopeSensitivity();
  EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
}

TEST_F(ImuInterfaceTests, interface_set_gyroscope_sensitivity_roughest) {
  auto sensitivity = types::GyroscopeSensitivity::ROUGHEST;
  unit_under_test_->SetGyroscopeSensitivity(sensitivity);
  auto gyroscope_sensitivity_return = unit_under_test_->GetGyroscopeSensitivity();
  EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
}

TEST_F(ImuInterfaceTests, interface_get_gyroscope_sensitivity_default) {
  auto sensitivity = types::GyroscopeSensitivity::FINEST;
  auto gyroscope_sensitivity_return = unit_under_test_->GetGyroscopeSensitivity();
  EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
}

TEST_F(ImuInterfaceTests, interface_set_accelerometer_sensitivity_finest) {
  auto sensitivity = types::AccelerometerSensitivity::FINEST;
  unit_under_test_->SetAccelerometerSensitivity(sensitivity);
  auto accelerometer_sensitivity_return = unit_under_test_->GetAccelerometerSensitivity();
  EXPECT_EQ(accelerometer_sensitivity_return, sensitivity);
}

TEST_F(ImuInterfaceTests, interface_set_accelerometer_sensitivity_finer) {
  auto sensitivity = types::AccelerometerSensitivity::FINER;
  unit_under_test_->SetAccelerometerSensitivity(sensitivity);
  auto accelerometer_sensitivity_return = unit_under_test_->GetAccelerometerSensitivity();
  EXPECT_EQ(accelerometer_sensitivity_return, sensitivity);
}

TEST_F(ImuInterfaceTests, interface_set_accelerometer_sensitivity_rougher) {
  auto sensitivity = types::AccelerometerSensitivity::ROUGHER;
  unit_under_test_->SetAccelerometerSensitivity(sensitivity);
  auto accelerometer_sensitivity_return = unit_under_test_->GetAccelerometerSensitivity();
  EXPECT_EQ(accelerometer_sensitivity_return, sensitivity);
}

TEST_F(ImuInterfaceTests, interface_set_accelerometer_sensitivity_roughest) {
  auto sensitivity = types::AccelerometerSensitivity::ROUGHEST;
  unit_under_test_->SetAccelerometerSensitivity(sensitivity);
  auto accelerometer_sensitivity_return = unit_under_test_->GetAccelerometerSensitivity();
  EXPECT_EQ(accelerometer_sensitivity_return, sensitivity);
}

TEST_F(ImuInterfaceTests, interface_get_accelerometer_sensitivity_default) {
  auto sensitivity = types::AccelerometerSensitivity::FINEST;
  auto accelerometer_sensitivity_return = unit_under_test_->GetAccelerometerSensitivity();
  EXPECT_EQ(accelerometer_sensitivity_return, sensitivity);
}

TEST_F(ImuInterfaceTests, interface_get_gyroscope) {
  types::EuclideanVector<float> expected_value{1.5, 2.5, 3.5};
  auto gyroscope_return = unit_under_test_->GetGyroscope();
  EXPECT_EQ(gyroscope_return.x, expected_value.x);
  EXPECT_EQ(gyroscope_return.y, expected_value.y);
  EXPECT_EQ(gyroscope_return.z, expected_value.z);
}

TEST_F(ImuInterfaceTests, interface_get_accelerometer) {
  types::EuclideanVector<float> expected_value{4.5, 5.5, 6.5};
  auto accelerometer_return = unit_under_test_->GetAccelerometer();
  EXPECT_EQ(accelerometer_return.x, expected_value.x);
  EXPECT_EQ(accelerometer_return.y, expected_value.y);
  EXPECT_EQ(accelerometer_return.z, expected_value.z);
}

TEST_F(ImuInterfaceTests, interface_get_magnetometer) {
  types::EuclideanVector<float> expected_value{7.5, 8.5, 9.5};
  auto magnetometer_return = unit_under_test_->GetMagnetometer();
  EXPECT_EQ(magnetometer_return.x, expected_value.x);
  EXPECT_EQ(magnetometer_return.y, expected_value.y);
  EXPECT_EQ(magnetometer_return.z, expected_value.z);
}

TEST_F(ImuInterfaceTests, interface_get_temperature) {
  auto expected_value = 17;
  auto temperature_return = unit_under_test_->GetTemperature();
  EXPECT_EQ(temperature_return, expected_value);
}
}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}