#include <gmock/gmock.h>
#include "gtest/gtest.h"
#include "imu_interface.hpp"
#include "inertial_measurement.hpp"
#include "mock_i2c.hpp"
#include "mock_mpu9255.hpp"

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
        .WillByDefault(Return(sensor_values_gyroscope));
    ON_CALL(*mock_mpu9255_, GetAccelerometer)
        .WillByDefault(Return(sensor_values_accelerometer));
    ON_CALL(*mock_mpu9255_, GetMagnetometer)
        .WillByDefault(Return(sensor_values_magnetometer));
    ON_CALL(*mock_mpu9255_, GetTemperature)
        .WillByDefault(Return(17));
  }

  virtual void ConfigureUnitUnderTest() {
    unit_under_test_ = std::make_unique<imu::InertialMeasurement>(i2c_handler_);
    unit_under_test_->UnitTestSetImuSeam(std::move(mock_mpu9255_));
  }

  std::shared_ptr<i2c::MockI2C> i2c_handler_ = std::make_shared<NiceMock<i2c::MockI2C>>();
  std::unique_ptr<imu::MockMpu9255> mock_mpu9255_ = std::make_unique<NiceMock<imu::MockMpu9255>>();
  std::unique_ptr<imu::InertialMeasurement> unit_under_test_;
  types::EuclideanVector<float> sensor_values_gyroscope{1.5, 2.5, 3.5};
  types::EuclideanVector<float> sensor_values_accelerometer{4.5, 5.5, 6.5};
  types::EuclideanVector<float> sensor_values_magnetometer{7.5, 8.5, 9.5};
};

TEST_F(ImuInterfaceTests, interface_Init) {
  ON_CALL(*mock_mpu9255_, Init)
      .WillByDefault(Return(types::DriverStatus::OK));

  ConfigureUnitUnderTest();

  EXPECT_EQ(unit_under_test_->Init(), types::DriverStatus::OK);
}

TEST_F(ImuInterfaceTests, interface_set_gyroscope_sensitivity_finest) {
  ON_CALL(*mock_mpu9255_, GetGyroscopeSensitivity)
      .WillByDefault(Return(types::ImuSensitivity::FINEST));

  ConfigureUnitUnderTest();

  auto sensitivity = types::ImuSensitivity::FINEST;
  unit_under_test_->SetGyroscopeSensitivity(sensitivity);
  auto gyroscope_sensitivity_return = unit_under_test_->GetGyroscopeSensitivity();
  EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
}

TEST_F(ImuInterfaceTests, interface_set_gyroscope_sensitivity_finer) {
  ON_CALL(*mock_mpu9255_, GetGyroscopeSensitivity)
      .WillByDefault(Return(types::ImuSensitivity::FINER));

  ConfigureUnitUnderTest();

  auto sensitivity = types::ImuSensitivity::FINER;
  unit_under_test_->SetGyroscopeSensitivity(sensitivity);
  auto gyroscope_sensitivity_return = unit_under_test_->GetGyroscopeSensitivity();
  EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
}

TEST_F(ImuInterfaceTests, interface_set_gyroscope_sensitivity_rougher) {
  ON_CALL(*mock_mpu9255_, GetGyroscopeSensitivity)
      .WillByDefault(Return(types::ImuSensitivity::ROUGHER));

  ConfigureUnitUnderTest();

  auto sensitivity = types::ImuSensitivity::ROUGHER;
  unit_under_test_->SetGyroscopeSensitivity(sensitivity);
  auto gyroscope_sensitivity_return = unit_under_test_->GetGyroscopeSensitivity();
  EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
}

TEST_F(ImuInterfaceTests, interface_set_gyroscope_sensitivity_roughest) {
  ON_CALL(*mock_mpu9255_, GetGyroscopeSensitivity)
      .WillByDefault(Return(types::ImuSensitivity::ROUGHEST));

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
  ON_CALL(*mock_mpu9255_, GetAccelerometerSensitivity)
      .WillByDefault(Return(types::ImuSensitivity::FINEST));

  ConfigureUnitUnderTest();

  auto sensitivity = types::ImuSensitivity::FINEST;
  unit_under_test_->SetAccelerometerSensitivity(sensitivity);
  auto accelerometer_sensitivity_return = unit_under_test_->GetAccelerometerSensitivity();
  EXPECT_EQ(accelerometer_sensitivity_return, sensitivity);
}

TEST_F(ImuInterfaceTests, interface_set_accelerometer_sensitivity_finer) {
  ON_CALL(*mock_mpu9255_, GetAccelerometerSensitivity)
      .WillByDefault(Return(types::ImuSensitivity::FINER));

  ConfigureUnitUnderTest();

  auto sensitivity = types::ImuSensitivity::FINER;
  unit_under_test_->SetAccelerometerSensitivity(sensitivity);
  auto accelerometer_sensitivity_return = unit_under_test_->GetAccelerometerSensitivity();
  EXPECT_EQ(accelerometer_sensitivity_return, sensitivity);
}

TEST_F(ImuInterfaceTests, interface_set_accelerometer_sensitivity_rougher) {
  ON_CALL(*mock_mpu9255_, GetAccelerometerSensitivity)
      .WillByDefault(Return(types::ImuSensitivity::ROUGHER));

  ConfigureUnitUnderTest();

  auto sensitivity = types::ImuSensitivity::ROUGHER;
  unit_under_test_->SetAccelerometerSensitivity(sensitivity);
  auto accelerometer_sensitivity_return = unit_under_test_->GetAccelerometerSensitivity();
  EXPECT_EQ(accelerometer_sensitivity_return, sensitivity);
}

TEST_F(ImuInterfaceTests, interface_set_accelerometer_sensitivity_roughest) {
  ON_CALL(*mock_mpu9255_, GetAccelerometerSensitivity)
      .WillByDefault(Return(types::ImuSensitivity::ROUGHEST));

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