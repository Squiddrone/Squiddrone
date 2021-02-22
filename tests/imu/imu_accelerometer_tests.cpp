#include <gmock/gmock.h>
#include "accelerometer.hpp"
#include "gtest/gtest.h"
#include "mock_i2c.hpp"

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;

namespace {

class AccelerometerTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    ON_CALL(*i2c_handler_, Write(_, _, _))
        .WillByDefault(Return(types::DriverStatus::OK));

    ON_CALL(*i2c_handler_, ReadContentFromRegister(_, _, _, _))
        .WillByDefault(Return(answer_to_who_am_i_MPU9255));
    ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::WHO_AM_I_MPU9255_REGISTER, _, _))
        .WillByDefault(Return(answer_to_who_am_i_MPU9255));
    ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::WHO_AM_I_AK8963_REGISTER, _, _))
        .WillByDefault(Return(answer_to_who_am_i_AK8963));
    ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::ACCEL_CONFIG, _, _))
        .WillByDefault(Return(answer_to_accel_config));
    ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::ACCEL_XOUT_H, _, _))
        .WillByDefault(Return(answer_to_update));
  }

  virtual void ConfigureUnitUnderTest() {
    unit_under_test_ = std::make_unique<imu::Accelerometer>(i2c_handler_);
  }

  uint8_t i2c_address_ = 0x68;
  std::shared_ptr<i2c::MockI2C> i2c_handler_ = std::make_shared<NiceMock<i2c::MockI2C>>();
  std::unique_ptr<imu::Accelerometer> unit_under_test_;

  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_to_who_am_i_MPU9255{
      types::DriverStatus::OK, {imu::WHO_AM_I_MPU9255_VALUE}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_to_who_am_i_AK8963{
      types::DriverStatus::OK, {imu::WHO_AM_I_AK8963_VALUE}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_to_accel_config{
      types::DriverStatus::OK, {0b11111111}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_to_update{
      types::DriverStatus::OK, {0x7F, 0xFF, 0x00, 0x00, 0x80, 0x00}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_read_mismatch{
      types::DriverStatus::OK, {0, 15}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_invalid{
      types::DriverStatus::HAL_ERROR, {}};
};

TEST_F(AccelerometerTests, Init_OK) {
  ConfigureUnitUnderTest();

  auto init_return = unit_under_test_->Init(i2c_address_);

  EXPECT_EQ(init_return, types::DriverStatus::OK);
}

TEST_F(AccelerometerTests, Init_failed) {
  ON_CALL(*i2c_handler_, Write(0, _, _))
      .WillByDefault(Return(types::DriverStatus::HAL_ERROR));

  ConfigureUnitUnderTest();

  auto init_return = unit_under_test_->Init(0);

  EXPECT_EQ(init_return, types::DriverStatus::HAL_ERROR);
}

TEST_F(AccelerometerTests, Update) {
  ConfigureUnitUnderTest();

  unit_under_test_->Init(i2c_address_);
  auto update_return = unit_under_test_->Update();
  EXPECT_EQ(update_return, types::DriverStatus::OK);
}

TEST_F(AccelerometerTests, Update_without_Init_first) {
  ConfigureUnitUnderTest();

  auto update_return = unit_under_test_->Update();
  EXPECT_EQ(update_return, types::DriverStatus::HAL_ERROR);
}

TEST_F(AccelerometerTests, Get_without_Update_and_Init_first) {
  ConfigureUnitUnderTest();

  types::EuclideanVector<std::int16_t> expected_value{-1, -1, -1};
  auto get_return = unit_under_test_->Get();

  EXPECT_EQ(get_return.x, expected_value.x);
  EXPECT_EQ(get_return.y, expected_value.y);
  EXPECT_EQ(get_return.z, expected_value.z);
}

TEST_F(AccelerometerTests, Get_without_Update_first) {
  ConfigureUnitUnderTest();

  types::EuclideanVector<std::int16_t> expected_value{0, 0, 0};
  unit_under_test_->Init(i2c_address_);
  auto get_return = unit_under_test_->Get();

  EXPECT_EQ(get_return.x, expected_value.x);
  EXPECT_EQ(get_return.y, expected_value.y);
  EXPECT_EQ(get_return.z, expected_value.z);
}

TEST_F(AccelerometerTests, Update_failes_in_ReadContentFromRegister) {
  ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::ACCEL_XOUT_H, _, _))
      .WillByDefault(Return(answer_invalid));

  ConfigureUnitUnderTest();

  unit_under_test_->Init(i2c_address_);
  auto update_return = unit_under_test_->Update();

  EXPECT_EQ(update_return, types::DriverStatus::HAL_ERROR);
}

TEST_F(AccelerometerTests, full) {
  ConfigureUnitUnderTest();

  types::EuclideanVector<std::int16_t> expected_value{16, 0, -16};
  unit_under_test_->Init(i2c_address_);
  unit_under_test_->Update();
  auto get_return = unit_under_test_->Get();

  EXPECT_EQ(get_return.x, expected_value.x);
  EXPECT_EQ(get_return.y, expected_value.y);
  EXPECT_EQ(get_return.z, expected_value.z);
}

TEST_F(AccelerometerTests, SetSensitivity_finest) {
  const std::vector<std::uint8_t> expected_data_finest{imu::ACCEL_CONFIG, 0b11100111};
  EXPECT_CALL(*i2c_handler_, Write(i2c_address_, expected_data_finest, _))
      .WillOnce(Return(types::DriverStatus::OK))
      .WillOnce(Return(types::DriverStatus::OK));

  ConfigureUnitUnderTest();

  unit_under_test_->Init(i2c_address_);
  auto sensitivity_return = unit_under_test_->SetSensitivity(types::ImuSensitivity::FINEST);
  EXPECT_EQ(sensitivity_return, types::DriverStatus::OK);
}

TEST_F(AccelerometerTests, SetSensitivity_finer) {
  const std::vector<std::uint8_t> expected_data_finest{imu::ACCEL_CONFIG, 0b11100111};
  const std::vector<std::uint8_t> expected_data_finer{imu::ACCEL_CONFIG, 0b11101111};

  EXPECT_CALL(*i2c_handler_, Write(i2c_address_, expected_data_finest, _))
      .WillOnce(Return(types::DriverStatus::OK));
  EXPECT_CALL(*i2c_handler_, Write(i2c_address_, expected_data_finer, _))
      .WillOnce(Return(types::DriverStatus::OK));

  ConfigureUnitUnderTest();

  unit_under_test_->Init(i2c_address_);
  auto sensitivity_return = unit_under_test_->SetSensitivity(types::ImuSensitivity::FINER);
  EXPECT_EQ(sensitivity_return, types::DriverStatus::OK);
}

TEST_F(AccelerometerTests, SetSensitivity_rougher) {
  const std::vector<std::uint8_t> expected_data_finest{imu::ACCEL_CONFIG, 0b11100111};
  const std::vector<std::uint8_t> expected_data_rougher{imu::ACCEL_CONFIG, 0b11110111};

  EXPECT_CALL(*i2c_handler_, Write(i2c_address_, expected_data_finest, _))
      .WillOnce(Return(types::DriverStatus::OK));
  EXPECT_CALL(*i2c_handler_, Write(i2c_address_, expected_data_rougher, _))
      .WillOnce(Return(types::DriverStatus::OK));

  ConfigureUnitUnderTest();

  unit_under_test_->Init(i2c_address_);
  auto sensitivity_return = unit_under_test_->SetSensitivity(types::ImuSensitivity::ROUGHER);
  EXPECT_EQ(sensitivity_return, types::DriverStatus::OK);
}

TEST_F(AccelerometerTests, SetSensitivity_roughest) {
  const std::vector<std::uint8_t> expected_data_finest{imu::ACCEL_CONFIG, 0b11100111};
  const std::vector<std::uint8_t> expected_data_roughest{imu::ACCEL_CONFIG, 0b11111111};

  EXPECT_CALL(*i2c_handler_, Write(i2c_address_, expected_data_finest, _))
      .WillOnce(Return(types::DriverStatus::OK));
  EXPECT_CALL(*i2c_handler_, Write(i2c_address_, expected_data_roughest, _))
      .WillOnce(Return(types::DriverStatus::OK));

  ConfigureUnitUnderTest();

  unit_under_test_->Init(i2c_address_);
  auto sensitivity_return = unit_under_test_->SetSensitivity(types::ImuSensitivity::ROUGHEST);
  EXPECT_EQ(sensitivity_return, types::DriverStatus::OK);
}

TEST_F(AccelerometerTests, SetSensitivity_failes_stored_sensitivity_stays_same) {
  ON_CALL(*i2c_handler_, ReadContentFromRegister(0, _, _, _))
      .WillByDefault(Return(answer_invalid));

  ConfigureUnitUnderTest();

  unit_under_test_->Init(i2c_address_);
  auto set_sensitivity = types::ImuSensitivity::ROUGHEST;
  auto sensitivity_return = unit_under_test_->SetSensitivity(set_sensitivity);
  auto get = unit_under_test_->GetSensitivity();
  EXPECT_EQ(sensitivity_return, types::DriverStatus::OK);
  EXPECT_EQ(get, set_sensitivity);

  unit_under_test_->Init(0);
  sensitivity_return = unit_under_test_->SetSensitivity(types::ImuSensitivity::FINEST);
  EXPECT_EQ(sensitivity_return, types::DriverStatus::HAL_ERROR);
  EXPECT_EQ(get, set_sensitivity);
}

TEST_F(AccelerometerTests, SetSensitivity_without_Init_first) {
  ConfigureUnitUnderTest();

  auto sensitivity_return = unit_under_test_->SetSensitivity(types::ImuSensitivity::ROUGHEST);
  EXPECT_EQ(sensitivity_return, types::DriverStatus::HAL_ERROR);
}

TEST_F(AccelerometerTests, SetSensitivity_GetSensitivity) {
  ConfigureUnitUnderTest();

  unit_under_test_->Init(i2c_address_);

  auto set_sensitivity = types::ImuSensitivity::ROUGHEST;
  unit_under_test_->SetSensitivity(set_sensitivity);
  auto get = unit_under_test_->GetSensitivity();
  EXPECT_EQ(get, set_sensitivity);

  set_sensitivity = types::ImuSensitivity::FINEST;
  unit_under_test_->SetSensitivity(set_sensitivity);
  get = unit_under_test_->GetSensitivity();
  EXPECT_EQ(get, set_sensitivity);
}

TEST_F(AccelerometerTests, connection_failed_after_Mpu9255Detected) {
  EXPECT_CALL(*i2c_handler_, Write(_, _, _))
      .WillOnce(Return(types::DriverStatus::HAL_ERROR));

  ConfigureUnitUnderTest();

  auto init_return = unit_under_test_->Init(i2c_address_);
  EXPECT_EQ(init_return, types::DriverStatus::HAL_ERROR);
}

TEST_F(AccelerometerTests, read_bytesize_mismatch) {
  ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::WHO_AM_I_MPU9255_REGISTER, _, _))
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