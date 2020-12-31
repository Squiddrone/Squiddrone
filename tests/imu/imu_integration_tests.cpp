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

class ImuIntegrationTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    ON_CALL(*i2c_handler_, Write)
        .WillByDefault(Return(types::DriverStatus::OK));

    ON_CALL(*i2c_handler_, ReadContentFromRegister(_, _, _, _))
        .WillByDefault(Return(answer_to_who_am_i));
    ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::WHO_AM_I_MPU9255_REGISTER, _, _))
        .WillByDefault(Return(answer_to_who_am_i));
    ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::GYRO_CONFIG, _, _))
        .WillByDefault(Return(answer_to_gyro_config));
    ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::GYRO_XOUT_H, _, _))
        .WillByDefault(Return(answer_to_gyro_update));
    ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::ACCEL_CONFIG, _, _))
        .WillByDefault(Return(answer_to_accelerometer_config));
    ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::ACCEL_XOUT_H, _, _))
        .WillByDefault(Return(answer_to_accelerometer_update));
  }

  virtual void ConfigureUnitUnderTest() {
    unit_under_test_ = std::make_unique<imu::InertialMeasurement>(i2c_handler_);
  }

  std::shared_ptr<i2c::MockI2C> i2c_handler_ = std::make_shared<NiceMock<i2c::MockI2C>>();
  std::unique_ptr<imu::InertialMeasurement> unit_under_test_;

  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_to_who_am_i{
      types::DriverStatus::OK, {imu::WHO_AM_I_MPU9255_VALUE}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_to_gyro_config{
      types::DriverStatus::OK, {0b11111111}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_to_accelerometer_config{
      types::DriverStatus::OK, {0b11111111}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_to_gyro_update{
      types::DriverStatus::OK, {0, 15, 0, 25, 0, 35}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_to_accelerometer_update{
      types::DriverStatus::OK, {0, 45, 0, 55, 0, 65}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_to_magnetometer_update{
      types::DriverStatus::OK, {0, 75, 0, 85, 0, 95}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_to_temperature_update{
      types::DriverStatus::OK, 37};
};

TEST_F(ImuIntegrationTests, integration_test_gyroscope_happy_path) {
  ConfigureUnitUnderTest();

  auto init_return = unit_under_test_->Init();

  EXPECT_EQ(init_return, types::DriverStatus::OK);

  auto update_return = unit_under_test_->Update();

  EXPECT_EQ(update_return, types::DriverStatus::OK);

  auto gyroscope_return = unit_under_test_->GetGyroscope();

  EXPECT_EQ(gyroscope_return.x, 15);
  EXPECT_EQ(gyroscope_return.y, 25);
  EXPECT_EQ(gyroscope_return.z, 35);
}

TEST_F(ImuIntegrationTests, integration_test_accelerometer_happy_path) {
  ConfigureUnitUnderTest();

  auto init_return = unit_under_test_->Init();

  EXPECT_EQ(init_return, types::DriverStatus::OK);

  auto update_return = unit_under_test_->Update();

  EXPECT_EQ(update_return, types::DriverStatus::OK);

  auto accelerometer_return = unit_under_test_->GetAccelerometer();

  EXPECT_EQ(accelerometer_return.x, 45);
  EXPECT_EQ(accelerometer_return.y, 55);
  EXPECT_EQ(accelerometer_return.z, 65);
}

TEST_F(ImuIntegrationTests, integration_test_magnetometer_happy_path) {
  GTEST_SKIP_("Not implemented yet.");

  ConfigureUnitUnderTest();

  auto init_return = unit_under_test_->Init();

  EXPECT_EQ(init_return, types::DriverStatus::OK);

  auto update_return = unit_under_test_->Update();

  EXPECT_EQ(update_return, types::DriverStatus::OK);

  auto magnetometer_return = unit_under_test_->GetMagnetometer();

  EXPECT_EQ(magnetometer_return.x, 75);
  EXPECT_EQ(magnetometer_return.y, 85);
  EXPECT_EQ(magnetometer_return.z, 95);
}

TEST_F(ImuIntegrationTests, integration_test_temperature_happy_path) {
  GTEST_SKIP_("Not implemented yet.");

  ConfigureUnitUnderTest();

  auto init_return = unit_under_test_->Init();

  EXPECT_EQ(init_return, types::DriverStatus::OK);

  auto update_return = unit_under_test_->Update();

  EXPECT_EQ(update_return, types::DriverStatus::OK);

  auto temperature_return = unit_under_test_->GetTemperature();

  EXPECT_EQ(temperature_return, 37);
}

TEST_F(ImuIntegrationTests, integration_test_Update_without_Init) {
  ConfigureUnitUnderTest();

  auto update_return = unit_under_test_->Update();

  EXPECT_EQ(update_return, types::DriverStatus::HAL_ERROR);
}

TEST_F(ImuIntegrationTests, integration_GetGyroscope_without_Init) {
  ConfigureUnitUnderTest();

  auto gyroscope_return = unit_under_test_->GetGyroscope();

  EXPECT_EQ(gyroscope_return.x, -1);
  EXPECT_EQ(gyroscope_return.y, -1);
  EXPECT_EQ(gyroscope_return.z, -1);
}

TEST_F(ImuIntegrationTests, integration_SetGyroscopeSensitivity) {
  ConfigureUnitUnderTest();

  unit_under_test_->SetGyroscopeSensitivity(types::ImuSensitivity::FINEST);

  EXPECT_EQ(unit_under_test_->GetGyroscopeSensitivity(), types::ImuSensitivity::FINEST);

  unit_under_test_->SetGyroscopeSensitivity(types::ImuSensitivity::ROUGHEST);

  EXPECT_EQ(unit_under_test_->GetGyroscopeSensitivity(), types::ImuSensitivity::ROUGHEST);
}

TEST_F(ImuIntegrationTests, integration_SetAccelerometerSensitivity) {
  ConfigureUnitUnderTest();

  unit_under_test_->SetAccelerometerSensitivity(types::ImuSensitivity::FINEST);

  EXPECT_EQ(unit_under_test_->GetAccelerometerSensitivity(), types::ImuSensitivity::FINEST);

  unit_under_test_->SetAccelerometerSensitivity(types::ImuSensitivity::ROUGHEST);

  EXPECT_EQ(unit_under_test_->GetAccelerometerSensitivity(), types::ImuSensitivity::ROUGHEST);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}