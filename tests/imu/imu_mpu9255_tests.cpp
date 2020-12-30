#include <gmock/gmock.h>
#include "gtest/gtest.h"
#include "mock_gyroscope.hpp"
#include "mock_i2c.hpp"
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
  }

  std::shared_ptr<i2c::MockI2C> i2c_handler_ = std::make_shared<NiceMock<i2c::MockI2C>>();
  std::unique_ptr<imu::Mpu9255> unit_under_test_;
  std::unique_ptr<imu::MockGyroscope> mock_gyroscope_ = std::make_unique<NiceMock<imu::MockGyroscope>>();

  types::EuclideanVector<std::int16_t> sensor_values_gyroscope{1, 2, 3};
};

TEST_F(Mpu9255Tests, mpu9255_Init) {
  ON_CALL(*mock_gyroscope_, Init)
      .WillByDefault(Return(types::DriverStatus::OK));

  ConfigureUnitUnderTest();

  EXPECT_EQ(unit_under_test_->Init(), types::DriverStatus::OK);
}

TEST_F(Mpu9255Tests, mpu9255_SetGyroscopeSensitivity) {
  ConfigureUnitUnderTest();

  unit_under_test_->SetGyroscopeSensitivity(types::ImuSensitivity::FINEST);

  EXPECT_EQ(unit_under_test_->GetGyroscopeSensitivity(), types::ImuSensitivity::FINEST);

  unit_under_test_->SetGyroscopeSensitivity(types::ImuSensitivity::ROUGHEST);

  EXPECT_EQ(unit_under_test_->GetGyroscopeSensitivity(), types::ImuSensitivity::ROUGHEST);
}

TEST_F(Mpu9255Tests, mpu9255_GetGyroscopeSensitivity) {
  ConfigureUnitUnderTest();

  unit_under_test_->SetGyroscopeSensitivity(types::ImuSensitivity::FINEST);

  EXPECT_EQ(unit_under_test_->GetGyroscopeSensitivity(), types::ImuSensitivity::FINEST);
}

TEST_F(Mpu9255Tests, mpu9255_SetAccelerometerSensitivity) {
  ConfigureUnitUnderTest();

  unit_under_test_->SetAccelerometerSensitivity(types::ImuSensitivity::FINEST);

  EXPECT_EQ(unit_under_test_->GetAccelerometerSensitivity(), types::ImuSensitivity::FINEST);

  unit_under_test_->SetAccelerometerSensitivity(types::ImuSensitivity::ROUGHEST);

  EXPECT_EQ(unit_under_test_->GetAccelerometerSensitivity(), types::ImuSensitivity::ROUGHEST);
}

TEST_F(Mpu9255Tests, mpu9255_GetAccelerometerSensitivity) {
  ConfigureUnitUnderTest();

  unit_under_test_->SetAccelerometerSensitivity(types::ImuSensitivity::FINEST);

  EXPECT_EQ(unit_under_test_->GetAccelerometerSensitivity(), types::ImuSensitivity::FINEST);
}

TEST_F(Mpu9255Tests, mpu9255_GetGyroscope) {
  ON_CALL(*mock_gyroscope_, Get)
      .WillByDefault(Return(sensor_values_gyroscope));

  ConfigureUnitUnderTest();

  auto gyroscope_return = unit_under_test_->GetGyroscope();

  EXPECT_EQ(gyroscope_return.x, sensor_values_gyroscope.x);
  EXPECT_EQ(gyroscope_return.y, sensor_values_gyroscope.y);
  EXPECT_EQ(gyroscope_return.z, sensor_values_gyroscope.z);
}

TEST_F(Mpu9255Tests, mpu9255_GetAccelerometer) {
  GTEST_SKIP_("Not implemented yet.");

  ConfigureUnitUnderTest();

  unit_under_test_->GetAccelerometer();
}

TEST_F(Mpu9255Tests, mpu9255_GetMagnetometer) {
  GTEST_SKIP_("Not implemented yet.");

  ConfigureUnitUnderTest();

  unit_under_test_->GetMagnetometer();
}

TEST_F(Mpu9255Tests, mpu9255_GetTemperature) {
  GTEST_SKIP_("Not implemented yet.");

  ConfigureUnitUnderTest();

  unit_under_test_->GetTemperature();
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}