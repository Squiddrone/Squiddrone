#include <gmock/gmock.h>
#include "gtest/gtest.h"
#include "magnetometer.hpp"
#include "mock_i2c.hpp"

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;

namespace {

class MagnetometerTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    ON_CALL(*i2c_handler_, Write(_, _, _))
        .WillByDefault(Return(types::DriverStatus::OK));

    ON_CALL(*i2c_handler_, ReadContentFromRegister(_, _, _, _))
        .WillByDefault(Return(answer_to_who_am_i_AK8963));
    ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::AK8963_ASAX, _, _))
        .WillByDefault(Return(answer_calibration_values));
    ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::AK8963_ST1, _, _))
        .WillByDefault(Return(answer_to_measurement_ready));
    ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::WHO_AM_I_MPU9255_REGISTER, _, _))
        .WillByDefault(Return(answer_to_who_am_i_MPU9255));
    ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::WHO_AM_I_AK8963_REGISTER, _, _))
        .WillByDefault(Return(answer_to_who_am_i_AK8963));
    ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::MAGNETOMETER_XOUT_L, _, _))
        .WillByDefault(Return(answer_to_update));
  }

  virtual void ConfigureUnitUnderTest() {
    unit_under_test_ = std::make_unique<imu::Magnetometer>(i2c_handler_);
  }

  uint8_t i2c_address_ = imu::AK8963_ADDRESS;
  std::shared_ptr<i2c::MockI2C> i2c_handler_ = std::make_shared<NiceMock<i2c::MockI2C>>();
  std::unique_ptr<imu::Magnetometer> unit_under_test_;

  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_to_who_am_i_AK8963{
      types::DriverStatus::OK, {imu::WHO_AM_I_AK8963_VALUE}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_to_who_am_i_MPU9255{
      types::DriverStatus::OK, {imu::WHO_AM_I_MPU9255_VALUE}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_to_update{
      types::DriverStatus::OK, {0b11111000, 0b01111111, 0, 0, 0b00001000, 0b10000000, 0}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_to_update_magnetic_overflow{
      types::DriverStatus::OK, {0b11111000, 0b01111111, 0, 0, 0b00001000, 0b10000000, 0x08}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_to_measurement_ready{
      types::DriverStatus::OK, {0b00000001}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_to_measurement_not_ready{
      types::DriverStatus::OK, {0b00000000}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_read_mismatch{
      types::DriverStatus::OK, {0, 15}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_calibration_values{
      types::DriverStatus::OK, {128, 128, 128}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_invalid{
      types::DriverStatus::HAL_ERROR, {}};
};

TEST_F(MagnetometerTests, Init_OK) {
  ConfigureUnitUnderTest();

  auto init_return = unit_under_test_->Init(i2c_address_);

  EXPECT_EQ(init_return, types::DriverStatus::OK);
}

TEST_F(MagnetometerTests, Init_failed) {
  ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::WHO_AM_I_AK8963_REGISTER, _, _))
      .WillByDefault(Return(answer_invalid));

  ConfigureUnitUnderTest();

  auto init_return = unit_under_test_->Init(0);

  EXPECT_EQ(init_return, types::DriverStatus::HAL_ERROR);
}

TEST_F(MagnetometerTests, Update) {
  ConfigureUnitUnderTest();

  unit_under_test_->Init(i2c_address_);
  auto update_return = unit_under_test_->Update();
  EXPECT_EQ(update_return, types::DriverStatus::OK);
}

TEST_F(MagnetometerTests, Update_without_Init_first) {
  ConfigureUnitUnderTest();

  auto update_return = unit_under_test_->Update();
  EXPECT_EQ(update_return, types::DriverStatus::HAL_ERROR);
}

TEST_F(MagnetometerTests, Get_without_Update_and_Init_first) {
  ConfigureUnitUnderTest();

  types::EuclideanVector<std::int16_t> expected_value{-1, -1, -1};
  auto get_return = unit_under_test_->Get();

  EXPECT_EQ(get_return.x, expected_value.x);
  EXPECT_EQ(get_return.y, expected_value.y);
  EXPECT_EQ(get_return.z, expected_value.z);
}

TEST_F(MagnetometerTests, Get_without_Update_first) {
  ConfigureUnitUnderTest();

  types::EuclideanVector<std::int16_t> expected_value{0, 0, 0};
  unit_under_test_->Init(i2c_address_);
  auto get_return = unit_under_test_->Get();

  EXPECT_EQ(get_return.x, expected_value.x);
  EXPECT_EQ(get_return.y, expected_value.y);
  EXPECT_EQ(get_return.z, expected_value.z);
}

TEST_F(MagnetometerTests, Update_but_measurement_is_not_ready) {
  ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::AK8963_ST1, _, _))
      .WillByDefault(Return(answer_to_measurement_not_ready));

  ConfigureUnitUnderTest();

  unit_under_test_->Init(i2c_address_);
  auto update_return = unit_under_test_->Update();

  EXPECT_EQ(update_return, types::DriverStatus::HAL_ERROR);
}

TEST_F(MagnetometerTests, Update_magnetic_overflow_occured) {
  ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::MAGNETOMETER_XOUT_L, _, _))
      .WillByDefault(Return(answer_to_update_magnetic_overflow));

  ConfigureUnitUnderTest();

  unit_under_test_->Init(i2c_address_);
  auto update_return = unit_under_test_->Update();

  EXPECT_EQ(update_return, types::DriverStatus::HAL_ERROR);
}

TEST_F(MagnetometerTests, full) {
  ConfigureUnitUnderTest();

  types::EuclideanVector<std::int16_t> expected_value{4912, 0, -4912};
  unit_under_test_->Init(i2c_address_);
  unit_under_test_->Update();
  auto get_return = unit_under_test_->Get();

  EXPECT_EQ(get_return.x, expected_value.x);
  EXPECT_EQ(get_return.y, expected_value.y);
  EXPECT_EQ(get_return.z, expected_value.z);
}

TEST_F(MagnetometerTests, connection_failed_after_successful_init) {
  ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::MAGNETOMETER_XOUT_L, _, _))
      .WillByDefault(Return(answer_invalid));

  ConfigureUnitUnderTest();

  auto init_return = unit_under_test_->Init(i2c_address_);
  auto update_return = unit_under_test_->Update();

  EXPECT_EQ(init_return, types::DriverStatus::OK);
  EXPECT_EQ(update_return, types::DriverStatus::HAL_ERROR);
}

TEST_F(MagnetometerTests, read_bytesize_mismatch) {
  ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::WHO_AM_I_AK8963_REGISTER, _, _))
      .WillByDefault(Return(answer_read_mismatch));

  ConfigureUnitUnderTest();

  auto init_return = unit_under_test_->Init(i2c_address_);
  EXPECT_EQ(init_return, types::DriverStatus::HAL_ERROR);
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}