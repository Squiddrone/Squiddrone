#include <gmock/gmock.h>
#include "gtest/gtest.h"
#include "imu_interface.hpp"
#include "inertial_measurement.hpp"
#include "mock_i2c.hpp"
#include "mock_mpu9255.hpp"

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;

namespace {

class ImuInterfaceTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    ON_CALL(*mock_mpu9255_, GetGyroscopeSensitivity)
        .WillByDefault(Return(types::ImuSensitivity::FINEST));
    ON_CALL(*mock_mpu9255_, GetAccelerometerSensitivity)
        .WillByDefault(Return(types::ImuSensitivity::FINEST));
    ON_CALL(*mock_mpu9255_, GetGyroscope)
        .WillByDefault(Return(gyroscope));
    ON_CALL(*mock_mpu9255_, GetAccelerometer)
        .WillByDefault(Return(gyroscope));
    ON_CALL(*mock_mpu9255_, GetMagnetometer)
        .WillByDefault(Return(gyroscope));
    ON_CALL(*mock_mpu9255_, GetTemperature)
        .WillByDefault(Return(17));
  }

  virtual void ConfigureUnitUnderTest() {
    unit_under_test_ = std::make_unique<imu::InertialMeasurement>(std::move(i2c_handler_));
    unit_under_test_->SetImuSeam(std::move(mock_mpu9255_));
  }

  std::unique_ptr<i2c::MOCKI2C> i2c_handler_ = std::make_unique<NiceMock<i2c::MOCKI2C>>();
  std::unique_ptr<imu::MOCKMPU9255> mock_mpu9255_ = std::make_unique<imu::MOCKMPU9255>();
  std::unique_ptr<imu::InertialMeasurement> unit_under_test_;
  types::EuclideanVector<float> gyroscope{1.5, 2.5, 3.5};
};

TEST_F(ImuInterfaceTests, interface_set_gyroscope_sensitivity_finest) {
  ConfigureUnitUnderTest();

  auto sensitivity = types::ImuSensitivity::FINEST;
  unit_under_test_->SetGyroscopeSensitivity(sensitivity);
  auto gyroscope_sensitivity_return = unit_under_test_->GetGyroscopeSensitivity();
  EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
}

TEST_F(ImuInterfaceTests, interface_set_gyroscope_sensitivity_finer) {
  ConfigureUnitUnderTest();

  auto sensitivity = types::ImuSensitivity::FINER;
  unit_under_test_->SetGyroscopeSensitivity(sensitivity);
  auto gyroscope_sensitivity_return = unit_under_test_->GetGyroscopeSensitivity();
  EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
}

TEST_F(ImuInterfaceTests, interface_set_gyroscope_sensitivity_rougher) {
  ConfigureUnitUnderTest();

  auto sensitivity = types::ImuSensitivity::ROUGHER;
  unit_under_test_->SetGyroscopeSensitivity(sensitivity);
  auto gyroscope_sensitivity_return = unit_under_test_->GetGyroscopeSensitivity();
  EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
}

TEST_F(ImuInterfaceTests, interface_set_gyroscope_sensitivity_roughest) {
  ConfigureUnitUnderTest();

  auto sensitivity = types::ImuSensitivity::ROUGHEST;
  unit_under_test_->SetGyroscopeSensitivity(sensitivity);
  auto gyroscope_sensitivity_return = unit_under_test_->GetGyroscopeSensitivity();
  EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
}

TEST_F(ImuInterfaceTests, interface_get_gyroscope_sensitivity_default) {
  ConfigureUnitUnderTest();

  auto sensitivity = types::ImuSensitivity::FINEST;
  auto gyroscope_sensitivity_return = unit_under_test_->GetGyroscopeSensitivity();
  EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
}

TEST_F(ImuInterfaceTests, interface_set_accelerometer_sensitivity_finest) {
  ConfigureUnitUnderTest();

  auto sensitivity = types::ImuSensitivity::FINEST;
  unit_under_test_->SetAccelerometerSensitivity(sensitivity);
  auto accelerometer_sensitivity_return = unit_under_test_->GetAccelerometerSensitivity();
  EXPECT_EQ(accelerometer_sensitivity_return, sensitivity);
}

TEST_F(ImuInterfaceTests, interface_set_accelerometer_sensitivity_finer) {
  ConfigureUnitUnderTest();

  auto sensitivity = types::ImuSensitivity::FINER;
  unit_under_test_->SetAccelerometerSensitivity(sensitivity);
  auto accelerometer_sensitivity_return = unit_under_test_->GetAccelerometerSensitivity();
  EXPECT_EQ(accelerometer_sensitivity_return, sensitivity);
}

TEST_F(ImuInterfaceTests, interface_set_accelerometer_sensitivity_rougher) {
  ConfigureUnitUnderTest();

  auto sensitivity = types::ImuSensitivity::ROUGHER;
  unit_under_test_->SetAccelerometerSensitivity(sensitivity);
  auto accelerometer_sensitivity_return = unit_under_test_->GetAccelerometerSensitivity();
  EXPECT_EQ(accelerometer_sensitivity_return, sensitivity);
}

TEST_F(ImuInterfaceTests, interface_set_accelerometer_sensitivity_roughest) {
  ConfigureUnitUnderTest();

  auto sensitivity = types::ImuSensitivity::ROUGHEST;
  unit_under_test_->SetAccelerometerSensitivity(sensitivity);
  auto accelerometer_sensitivity_return = unit_under_test_->GetAccelerometerSensitivity();
  EXPECT_EQ(accelerometer_sensitivity_return, sensitivity);
}

TEST_F(ImuInterfaceTests, interface_get_accelerometer_sensitivity_default) {
  ConfigureUnitUnderTest();

  auto sensitivity = types::ImuSensitivity::FINEST;
  auto accelerometer_sensitivity_return = unit_under_test_->GetAccelerometerSensitivity();
  EXPECT_EQ(accelerometer_sensitivity_return, sensitivity);
}

TEST_F(ImuInterfaceTests, interface_get_gyroscope) {
  ConfigureUnitUnderTest();

  types::EuclideanVector<float> expected_value{1.5, 2.5, 3.5};
  auto gyroscope_return = unit_under_test_->GetGyroscope();
  EXPECT_EQ(gyroscope_return.x, expected_value.x);
  EXPECT_EQ(gyroscope_return.y, expected_value.y);
  EXPECT_EQ(gyroscope_return.z, expected_value.z);
}

TEST_F(ImuInterfaceTests, interface_get_accelerometer) {
  ConfigureUnitUnderTest();

  types::EuclideanVector<float> expected_value{4.5, 5.5, 6.5};
  auto accelerometer_return = unit_under_test_->GetAccelerometer();
  EXPECT_EQ(accelerometer_return.x, expected_value.x);
  EXPECT_EQ(accelerometer_return.y, expected_value.y);
  EXPECT_EQ(accelerometer_return.z, expected_value.z);
}

TEST_F(ImuInterfaceTests, interface_get_magnetometer) {
  ConfigureUnitUnderTest();

  types::EuclideanVector<float> expected_value{7.5, 8.5, 9.5};
  auto magnetometer_return = unit_under_test_->GetMagnetometer();
  EXPECT_EQ(magnetometer_return.x, expected_value.x);
  EXPECT_EQ(magnetometer_return.y, expected_value.y);
  EXPECT_EQ(magnetometer_return.z, expected_value.z);
}

TEST_F(ImuInterfaceTests, interface_get_temperature) {
  ConfigureUnitUnderTest();

  auto expected_value = 17;
  auto temperature_return = unit_under_test_->GetTemperature();
  EXPECT_EQ(temperature_return, expected_value);
}
}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}