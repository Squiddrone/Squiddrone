#include <gmock/gmock.h>
#include "gtest/gtest.h"
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
    unit_under_test_ = std::make_unique<imu::Mpu9255>(std::move(i2c_handler_));
  }

  std::unique_ptr<i2c::MOCKI2C> i2c_handler_ = std::make_unique<NiceMock<i2c::MOCKI2C>>();
  std::unique_ptr<imu::Mpu9255> unit_under_test_;
};

TEST_F(Mpu9255Tests, mpu9255_SetGyroscopeSensitivity) {
  ConfigureUnitUnderTest();

  unit_under_test_->SetGyroscopeSensitivity(types::ImuSensitivity::FINEST);
}

TEST_F(Mpu9255Tests, mpu9255_GetGyroscopeSensitivity) {
  ConfigureUnitUnderTest();

  unit_under_test_->GetGyroscopeSensitivity();
}

TEST_F(Mpu9255Tests, mpu9255_SetAccelerometerSensitivity) {
  ConfigureUnitUnderTest();

  unit_under_test_->SetAccelerometerSensitivity(types::ImuSensitivity::FINEST);
}

TEST_F(Mpu9255Tests, mpu9255_GetAccelerometerSensitivity) {
  ConfigureUnitUnderTest();

  unit_under_test_->GetAccelerometerSensitivity();
}

TEST_F(Mpu9255Tests, mpu9255_GetGyroscope) {
  ConfigureUnitUnderTest();

  unit_under_test_->GetGyroscope();
}

TEST_F(Mpu9255Tests, mpu9255_GetAccelerometer) {
  ConfigureUnitUnderTest();

  unit_under_test_->GetAccelerometer();
}

TEST_F(Mpu9255Tests, mpu9255_GetMagnetometer) {
  ConfigureUnitUnderTest();

  unit_under_test_->GetMagnetometer();
}

TEST_F(Mpu9255Tests, mpu9255_GetTemperature) {
  ConfigureUnitUnderTest();

  unit_under_test_->GetTemperature();
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}