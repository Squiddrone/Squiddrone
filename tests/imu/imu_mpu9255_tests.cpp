#include <gmock/gmock.h>
#include <chrono>
#include "gtest/gtest.h"
#include "mock_accelerometer.hpp"
#include "mock_gyroscope.hpp"
#include "mock_i2c.hpp"
#include "mock_magnetometer.hpp"
#include "mock_temperature.hpp"
#include "mpu9255.hpp"

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;

namespace {

class Mpu9255Tests : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }

  virtual void ConfigureUnitUnderTest() {
    unit_under_test_ = std::make_unique<imu::Mpu9255>(i2c_handler_);
    unit_under_test_->UnitTestSetGyroscope(std::move(mock_gyroscope_));
    unit_under_test_->UnitTestSetAccelerometer(std::move(mock_accelerometer_));
    unit_under_test_->UnitTestSetMagnetometer(std::move(mock_magnetometer_));
    unit_under_test_->UnitTestSetTemperature(std::move(mock_temperature_));
  }

  std::shared_ptr<i2c::MockI2C> i2c_handler_ = std::make_shared<NiceMock<i2c::MockI2C>>();
  std::unique_ptr<imu::Mpu9255> unit_under_test_;
  std::unique_ptr<imu::MockGyroscope> mock_gyroscope_ = std::make_unique<NiceMock<imu::MockGyroscope>>();
  std::unique_ptr<imu::MockAccelerometer> mock_accelerometer_ = std::make_unique<NiceMock<imu::MockAccelerometer>>();
  std::unique_ptr<imu::MockMagnetometer> mock_magnetometer_ = std::make_unique<NiceMock<imu::MockMagnetometer>>();
  std::unique_ptr<imu::MockTemperature> mock_temperature_ = std::make_unique<NiceMock<imu::MockTemperature>>();

  types::EuclideanVector<std::int16_t> sensor_values_gyroscope{1, 2, 3};
  types::EuclideanVector<std::int16_t> sensor_values_accelerometer{4, 5, 6};
  types::EuclideanVector<std::int16_t> sensor_values_magnetometer{7, 8, 9};
};

TEST_F(Mpu9255Tests, mpu9255_Init_all_sensors_ok) {
  ON_CALL(*mock_gyroscope_, Init)
      .WillByDefault(Return(types::DriverStatus::OK));
  ON_CALL(*mock_accelerometer_, Init)
      .WillByDefault(Return(types::DriverStatus::OK));
  ON_CALL(*mock_magnetometer_, Init)
      .WillByDefault(Return(types::DriverStatus::OK));

  ConfigureUnitUnderTest();

  EXPECT_EQ(unit_under_test_->Init(), types::DriverStatus::OK);
  EXPECT_EQ(unit_under_test_->IsInitialized(), true);
}

TEST_F(Mpu9255Tests, mpu9255_Init_gyroscope_failed) {
  ON_CALL(*mock_gyroscope_, Init)
      .WillByDefault(Return(types::DriverStatus::HAL_ERROR));
  ON_CALL(*mock_accelerometer_, Init)
      .WillByDefault(Return(types::DriverStatus::OK));
  ON_CALL(*mock_magnetometer_, Init)
      .WillByDefault(Return(types::DriverStatus::OK));

  ConfigureUnitUnderTest();

  EXPECT_EQ(unit_under_test_->Init(), types::DriverStatus::HAL_ERROR);
  EXPECT_EQ(unit_under_test_->IsInitialized(), false);
}

TEST_F(Mpu9255Tests, mpu9255_Init_accelerometer_failed) {
  ON_CALL(*mock_gyroscope_, Init)
      .WillByDefault(Return(types::DriverStatus::OK));
  ON_CALL(*mock_accelerometer_, Init)
      .WillByDefault(Return(types::DriverStatus::HAL_ERROR));
  ON_CALL(*mock_magnetometer_, Init)
      .WillByDefault(Return(types::DriverStatus::OK));

  ConfigureUnitUnderTest();

  EXPECT_EQ(unit_under_test_->Init(), types::DriverStatus::HAL_ERROR);
  EXPECT_EQ(unit_under_test_->IsInitialized(), false);
}

TEST_F(Mpu9255Tests, mpu9255_Init_magnetometer_failed) {
  ON_CALL(*mock_gyroscope_, Init)
      .WillByDefault(Return(types::DriverStatus::OK));
  ON_CALL(*mock_accelerometer_, Init)
      .WillByDefault(Return(types::DriverStatus::OK));
  ON_CALL(*mock_magnetometer_, Init)
      .WillByDefault(Return(types::DriverStatus::HAL_ERROR));

  ConfigureUnitUnderTest();

  EXPECT_EQ(unit_under_test_->Init(), types::DriverStatus::HAL_ERROR);
  EXPECT_EQ(unit_under_test_->IsInitialized(), false);
}

TEST_F(Mpu9255Tests, mpu9255_Update_all_sensors_ok) {
  ON_CALL(*mock_gyroscope_, Init)
      .WillByDefault(Return(types::DriverStatus::OK));
  ON_CALL(*mock_accelerometer_, Init)
      .WillByDefault(Return(types::DriverStatus::OK));
  ON_CALL(*mock_magnetometer_, Init)
      .WillByDefault(Return(types::DriverStatus::OK));
  ON_CALL(*mock_gyroscope_, Update)
      .WillByDefault(Return(types::DriverStatus::OK));
  ON_CALL(*mock_accelerometer_, Update)
      .WillByDefault(Return(types::DriverStatus::OK));
  ON_CALL(*mock_magnetometer_, Update)
      .WillByDefault(Return(types::DriverStatus::OK));

  ConfigureUnitUnderTest();

  unit_under_test_->Init();

  EXPECT_EQ(unit_under_test_->Update(), types::DriverStatus::OK);
}

TEST_F(Mpu9255Tests, mpu9255_Update_accelerometer_failed) {
  ON_CALL(*mock_gyroscope_, Init)
      .WillByDefault(Return(types::DriverStatus::OK));
  ON_CALL(*mock_accelerometer_, Init)
      .WillByDefault(Return(types::DriverStatus::OK));
  ON_CALL(*mock_magnetometer_, Init)
      .WillByDefault(Return(types::DriverStatus::OK));
  ON_CALL(*mock_gyroscope_, Update)
      .WillByDefault(Return(types::DriverStatus::OK));
  ON_CALL(*mock_accelerometer_, Update)
      .WillByDefault(Return(types::DriverStatus::HAL_ERROR));
  ON_CALL(*mock_magnetometer_, Update)
      .WillByDefault(Return(types::DriverStatus::OK));

  ConfigureUnitUnderTest();

  unit_under_test_->Init();
  EXPECT_EQ(unit_under_test_->Update(), types::DriverStatus::HAL_ERROR);
}

TEST_F(Mpu9255Tests, mpu9255_SetGyroscopeSensitivity) {
  ON_CALL(*mock_gyroscope_, GetSensitivity)
      .WillByDefault(Return(types::ImuSensitivity::FINEST));

  ConfigureUnitUnderTest();

  unit_under_test_->Init();

  auto set_return = unit_under_test_->SetGyroscopeSensitivity(types::ImuSensitivity::FINEST);

  EXPECT_EQ(set_return, types::DriverStatus::OK);
  EXPECT_EQ(unit_under_test_->GetGyroscopeSensitivity(), types::ImuSensitivity::FINEST);
}

TEST_F(Mpu9255Tests, mpu9255_GetGyroscopeSensitivity_without_Init) {
  ConfigureUnitUnderTest();

  EXPECT_EQ(unit_under_test_->GetGyroscopeSensitivity(), types::ImuSensitivity::FINEST);
}

TEST_F(Mpu9255Tests, mpu9255_SetGyroscopeSensitivity_without_Init) {
  ConfigureUnitUnderTest();

  EXPECT_EQ(unit_under_test_->SetGyroscopeSensitivity(types::ImuSensitivity::FINEST), types::DriverStatus::HAL_ERROR);
}

TEST_F(Mpu9255Tests, mpu9255_SetAccelerometerSensitivity) {
  ON_CALL(*mock_accelerometer_, GetSensitivity)
      .WillByDefault(Return(types::ImuSensitivity::FINEST));
  ON_CALL(*mock_accelerometer_, SetSensitivity)
      .WillByDefault(Return(types::DriverStatus::OK));

  ConfigureUnitUnderTest();

  unit_under_test_->Init();

  auto set_return = unit_under_test_->SetAccelerometerSensitivity(types::ImuSensitivity::FINEST);

  EXPECT_EQ(set_return, types::DriverStatus::OK);
  EXPECT_EQ(unit_under_test_->GetAccelerometerSensitivity(), types::ImuSensitivity::FINEST);
}

TEST_F(Mpu9255Tests, mpu9255_GetAccelerometerSensitivity_without_Init) {
  ConfigureUnitUnderTest();

  EXPECT_EQ(unit_under_test_->GetAccelerometerSensitivity(), types::ImuSensitivity::FINEST);
}

TEST_F(Mpu9255Tests, mpu9255_SetAccelerometerSensitivity_without_Init) {
  ConfigureUnitUnderTest();

  EXPECT_EQ(unit_under_test_->SetAccelerometerSensitivity(types::ImuSensitivity::FINEST), types::DriverStatus::HAL_ERROR);
}

TEST_F(Mpu9255Tests, mpu9255_GetGyroscope) {
  ON_CALL(*mock_gyroscope_, Get)
      .WillByDefault(Return(sensor_values_gyroscope));

  ConfigureUnitUnderTest();

  unit_under_test_->Init();

  auto gyroscope_return = unit_under_test_->GetGyroscope();

  EXPECT_EQ(gyroscope_return.x, sensor_values_gyroscope.x);
  EXPECT_EQ(gyroscope_return.y, sensor_values_gyroscope.y);
  EXPECT_EQ(gyroscope_return.z, sensor_values_gyroscope.z);
}

TEST_F(Mpu9255Tests, mpu9255_GetGyroscope_without_Init) {
  ConfigureUnitUnderTest();

  auto gyroscope_return = unit_under_test_->GetGyroscope();

  EXPECT_EQ(gyroscope_return.x, -1);
  EXPECT_EQ(gyroscope_return.y, -1);
  EXPECT_EQ(gyroscope_return.z, -1);
}

TEST_F(Mpu9255Tests, mpu9255_GetAccelerometer) {
  ON_CALL(*mock_accelerometer_, Get)
      .WillByDefault(Return(sensor_values_accelerometer));

  ConfigureUnitUnderTest();

  unit_under_test_->Init();

  auto accelerometer_return = unit_under_test_->GetAccelerometer();

  EXPECT_EQ(accelerometer_return.x, sensor_values_accelerometer.x);
  EXPECT_EQ(accelerometer_return.y, sensor_values_accelerometer.y);
  EXPECT_EQ(accelerometer_return.z, sensor_values_accelerometer.z);
}

TEST_F(Mpu9255Tests, mpu9255_GetAccelerometer_without_Init) {
  ConfigureUnitUnderTest();

  auto accelerometer_return = unit_under_test_->GetAccelerometer();

  EXPECT_EQ(accelerometer_return.x, -1);
  EXPECT_EQ(accelerometer_return.y, -1);
  EXPECT_EQ(accelerometer_return.z, -1);
}

TEST_F(Mpu9255Tests, mpu9255_GetMagnetometer) {
  ON_CALL(*mock_magnetometer_, Get)
      .WillByDefault(Return(sensor_values_magnetometer));

  ConfigureUnitUnderTest();

  unit_under_test_->Init();

  auto magnetometer_return = unit_under_test_->GetMagnetometer();

  EXPECT_EQ(magnetometer_return.x, sensor_values_magnetometer.x);
  EXPECT_EQ(magnetometer_return.y, sensor_values_magnetometer.y);
  EXPECT_EQ(magnetometer_return.z, sensor_values_magnetometer.z);
}

TEST_F(Mpu9255Tests, mpu9255_GetMagnetometer_without_Init) {
  ConfigureUnitUnderTest();

  auto magnetometer_return = unit_under_test_->GetMagnetometer();

  EXPECT_EQ(magnetometer_return.x, -1);
  EXPECT_EQ(magnetometer_return.y, -1);
  EXPECT_EQ(magnetometer_return.z, -1);
}

TEST_F(Mpu9255Tests, mpu9255_GetTemperature) {
  ON_CALL(*mock_temperature_, Get)
      .WillByDefault(Return(37));

  ConfigureUnitUnderTest();

  unit_under_test_->Init();

  auto temperature_return = unit_under_test_->GetTemperature();

  EXPECT_EQ(temperature_return, 37);
}

TEST_F(Mpu9255Tests, mpu9255_GetTemperature_without_Init) {
  ConfigureUnitUnderTest();

  auto temperature_return = unit_under_test_->GetTemperature();

  EXPECT_EQ(temperature_return, -1);
}

/* Deaktiviert, da jedesmal der 10 sec. timeout abgewartet werden muss. Hat als Entwicklertest funktioniert.
TEST_F(Mpu9255Tests, mpu9255_calibration_timeout) {
  std::pair<types::DriverStatus, std::vector<uint8_t>> i2c_return_value{types::DriverStatus::OK, {0}};
  ON_CALL(*mock_accelerometer_, Get)
      .WillByDefault(Return(sensor_values_accelerometer));
  ON_CALL(*i2c_handler_, ReadContentFromRegister).WillByDefault(Return(i2c_return_value));

  ConfigureUnitUnderTest();

  unit_under_test_->Init();
  auto time_measurement_start{std::chrono::steady_clock::now()};
  unit_under_test_->PerformCalibration();
  auto time_measurement_end{std::chrono::steady_clock::now()};
  std::chrono::duration<double> time_measurement{time_measurement_end - time_measurement_start};
  EXPECT_GT(time_measurement / 1s, 9.0);
  EXPECT_LT(time_measurement / 1s, 11.0);
}
*/

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}