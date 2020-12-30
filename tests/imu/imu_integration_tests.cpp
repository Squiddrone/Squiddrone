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
        .WillByDefault(Return(answer_to_update));
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
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_to_update{
      types::DriverStatus::OK, {0, 15, 0, 25, 0, 35}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_read_mismatch{
      types::DriverStatus::OK, {0, 15}};
};

TEST_F(ImuIntegrationTests, integration_test_happy_path) {
  ConfigureUnitUnderTest();

  unit_under_test_->Init();

  auto update_return = unit_under_test_->Update();

  EXPECT_EQ(update_return, types::DriverStatus::OK);

  auto gyroscope_return = unit_under_test_->GetGyroscope();

  EXPECT_EQ(gyroscope_return.x, 15);
  EXPECT_EQ(gyroscope_return.y, 25);
  EXPECT_EQ(gyroscope_return.z, 35);
}

TEST_F(ImuIntegrationTests, integration_test_no_Init) {
  GTEST_SKIP_("Speicherabzugsfehler.");

  ConfigureUnitUnderTest();

  auto update_return = unit_under_test_->Update();

  EXPECT_EQ(update_return, types::DriverStatus::HAL_ERROR);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}