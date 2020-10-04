#include <gmock/gmock.h>
#include "gtest/gtest.h"
#include "gyroscope.hpp"
#include "mock_i2c.hpp"

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;

namespace {

class GyroscopeTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    ON_CALL(*i2c_handler_, Write(_, _, _))
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
    unit_under_test_ = std::make_unique<imu::Gyroscope>(std::move(i2c_handler_));
  }

  uint8_t i2c_address_ = 0x68;
  std::unique_ptr<i2c::MockI2C> i2c_handler_ = std::make_unique<NiceMock<i2c::MockI2C>>();
  std::unique_ptr<imu::Gyroscope> unit_under_test_;

  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_to_who_am_i{
      types::DriverStatus::OK, {imu::WHO_AM_I_MPU9255_VALUE}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_to_gyro_config{
      types::DriverStatus::OK, {0b11111111}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_to_update{
      types::DriverStatus::OK, {0, 15, 0, 25, 0, 35}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_read_mismatch{
      types::DriverStatus::OK, {0, 15}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_invalid{
      types::DriverStatus::HAL_ERROR, {}};
};

TEST_F(GyroscopeTests, gyroscope_Init_OK) {
  ConfigureUnitUnderTest();

  auto gyroscope_init_return = unit_under_test_->Init(i2c_address_);

  EXPECT_EQ(gyroscope_init_return, types::DriverStatus::OK);
}

TEST_F(GyroscopeTests, gyroscope_Init_failed) {
  ON_CALL(*i2c_handler_, Write(0, _, _))
      .WillByDefault(Return(types::DriverStatus::HAL_ERROR));

  ConfigureUnitUnderTest();

  auto gyroscope_init_return = unit_under_test_->Init(0);

  EXPECT_EQ(gyroscope_init_return, types::DriverStatus::HAL_ERROR);
}

TEST_F(GyroscopeTests, gyroscope_Update) {
  ConfigureUnitUnderTest();

  unit_under_test_->Init(i2c_address_);
  auto gyroscope_update_return = unit_under_test_->Update();
  EXPECT_EQ(gyroscope_update_return, types::DriverStatus::OK);
}

TEST_F(GyroscopeTests, gyroscope_Update_without_Init_first) {
  ConfigureUnitUnderTest();

  auto gyroscope_update_return = unit_under_test_->Update();
  EXPECT_EQ(gyroscope_update_return, types::DriverStatus::HAL_ERROR);
}

TEST_F(GyroscopeTests, gyroscope_Get_without_Update_and_Init_first) {
  ConfigureUnitUnderTest();

  types::EuclideanVector<std::int16_t> expected_value{-1, -1, -1};
  auto gyroscope_get_return = unit_under_test_->Get();

  EXPECT_EQ(gyroscope_get_return.x, expected_value.x);
  EXPECT_EQ(gyroscope_get_return.y, expected_value.y);
  EXPECT_EQ(gyroscope_get_return.z, expected_value.z);
}

TEST_F(GyroscopeTests, gyroscope_Get_without_Update_first) {
  ConfigureUnitUnderTest();

  types::EuclideanVector<std::int16_t> expected_value{0, 0, 0};
  unit_under_test_->Init(i2c_address_);
  auto gyroscope_get_return = unit_under_test_->Get();

  EXPECT_EQ(gyroscope_get_return.x, expected_value.x);
  EXPECT_EQ(gyroscope_get_return.y, expected_value.y);
  EXPECT_EQ(gyroscope_get_return.z, expected_value.z);
}

TEST_F(GyroscopeTests, gyroscope_full) {
  ConfigureUnitUnderTest();

  types::EuclideanVector<std::int16_t> expected_value{15, 25, 35};
  unit_under_test_->Init(i2c_address_);
  unit_under_test_->Update();
  auto gyroscope_get_return = unit_under_test_->Get();

  EXPECT_EQ(gyroscope_get_return.x, expected_value.x);
  EXPECT_EQ(gyroscope_get_return.y, expected_value.y);
  EXPECT_EQ(gyroscope_get_return.z, expected_value.z);
}

TEST_F(GyroscopeTests, gyroscope_SetSensitivity_finest) {
  const std::vector<std::uint8_t> expected_data_finest{imu::GYRO_CONFIG, 0b11100111};
  EXPECT_CALL(*i2c_handler_, Write(i2c_address_, expected_data_finest, _))
      .WillOnce(Return(types::DriverStatus::OK))
      .WillOnce(Return(types::DriverStatus::OK));

  ConfigureUnitUnderTest();

  unit_under_test_->Init(i2c_address_);
  auto gyroscope_sensitivity_return = unit_under_test_->SetSensitivity(types::ImuSensitivity::FINEST);
  EXPECT_EQ(gyroscope_sensitivity_return, types::DriverStatus::OK);
}

TEST_F(GyroscopeTests, gyroscope_SetSensitivity_finer) {
  const std::vector<std::uint8_t> expected_data_finest{imu::GYRO_CONFIG, 0b11100111};
  const std::vector<std::uint8_t> expected_data_finer{imu::GYRO_CONFIG, 0b11101111};

  EXPECT_CALL(*i2c_handler_, Write(i2c_address_, expected_data_finest, _))
      .WillOnce(Return(types::DriverStatus::OK));
  EXPECT_CALL(*i2c_handler_, Write(i2c_address_, expected_data_finer, _))
      .WillOnce(Return(types::DriverStatus::OK));

  ConfigureUnitUnderTest();

  unit_under_test_->Init(i2c_address_);
  auto gyroscope_sensitivity_return = unit_under_test_->SetSensitivity(types::ImuSensitivity::FINER);
  EXPECT_EQ(gyroscope_sensitivity_return, types::DriverStatus::OK);
}

TEST_F(GyroscopeTests, gyroscope_SetSensitivity_rougher) {
  const std::vector<std::uint8_t> expected_data_finest{imu::GYRO_CONFIG, 0b11100111};
  const std::vector<std::uint8_t> expected_data_rougher{imu::GYRO_CONFIG, 0b11110111};

  EXPECT_CALL(*i2c_handler_, Write(i2c_address_, expected_data_finest, _))
      .WillOnce(Return(types::DriverStatus::OK));
  EXPECT_CALL(*i2c_handler_, Write(i2c_address_, expected_data_rougher, _))
      .WillOnce(Return(types::DriverStatus::OK));

  ConfigureUnitUnderTest();

  unit_under_test_->Init(i2c_address_);
  auto gyroscope_sensitivity_return = unit_under_test_->SetSensitivity(types::ImuSensitivity::ROUGHER);
  EXPECT_EQ(gyroscope_sensitivity_return, types::DriverStatus::OK);
}

TEST_F(GyroscopeTests, gyroscope_SetSensitivity_roughest) {
  const std::vector<std::uint8_t> expected_data_finest{imu::GYRO_CONFIG, 0b11100111};
  const std::vector<std::uint8_t> expected_data_roughest{imu::GYRO_CONFIG, 0b11111111};

  EXPECT_CALL(*i2c_handler_, Write(i2c_address_, expected_data_finest, _))
      .WillOnce(Return(types::DriverStatus::OK));
  EXPECT_CALL(*i2c_handler_, Write(i2c_address_, expected_data_roughest, _))
      .WillOnce(Return(types::DriverStatus::OK));

  ConfigureUnitUnderTest();

  unit_under_test_->Init(i2c_address_);
  auto gyroscope_sensitivity_return = unit_under_test_->SetSensitivity(types::ImuSensitivity::ROUGHEST);
  EXPECT_EQ(gyroscope_sensitivity_return, types::DriverStatus::OK);
}

TEST_F(GyroscopeTests, gyroscope_SetSensitivity_failes_stored_sensitivity_stays_same) {
  ON_CALL(*i2c_handler_, ReadContentFromRegister(0, _, _, _))
      .WillByDefault(Return(answer_invalid));

  ConfigureUnitUnderTest();

  unit_under_test_->Init(i2c_address_);
  auto set_sensitivity = types::ImuSensitivity::ROUGHEST;
  auto gyroscope_sensitivity_return = unit_under_test_->SetSensitivity(set_sensitivity);
  auto gyroscope_get = unit_under_test_->GetSensitivity();
  EXPECT_EQ(gyroscope_sensitivity_return, types::DriverStatus::OK);
  EXPECT_EQ(gyroscope_get, set_sensitivity);

  unit_under_test_->Init(0);
  gyroscope_sensitivity_return = unit_under_test_->SetSensitivity(types::ImuSensitivity::FINEST);
  EXPECT_EQ(gyroscope_sensitivity_return, types::DriverStatus::HAL_ERROR);
  EXPECT_EQ(gyroscope_get, set_sensitivity);
}

TEST_F(GyroscopeTests, gyroscope_SetSensitivity_without_Init_first) {
  ConfigureUnitUnderTest();

  auto gyroscope_sensitivity_return = unit_under_test_->SetSensitivity(types::ImuSensitivity::ROUGHEST);
  EXPECT_EQ(gyroscope_sensitivity_return, types::DriverStatus::HAL_ERROR);
}

TEST_F(GyroscopeTests, gyroscope_SetSensitivity_GetSensitivity) {
  ConfigureUnitUnderTest();

  unit_under_test_->Init(i2c_address_);

  auto set_sensitivity = types::ImuSensitivity::ROUGHEST;
  unit_under_test_->SetSensitivity(set_sensitivity);
  auto gyroscope_get = unit_under_test_->GetSensitivity();
  EXPECT_EQ(gyroscope_get, set_sensitivity);

  set_sensitivity = types::ImuSensitivity::FINEST;
  unit_under_test_->SetSensitivity(set_sensitivity);
  gyroscope_get = unit_under_test_->GetSensitivity();
  EXPECT_EQ(gyroscope_get, set_sensitivity);
}

TEST_F(GyroscopeTests, gyroscope_connection_failed_after_Mpu9255Detected) {
  EXPECT_CALL(*i2c_handler_, Write(_, _, _))
      .WillOnce(Return(types::DriverStatus::HAL_ERROR));

  ConfigureUnitUnderTest();

  auto init_return = unit_under_test_->Init(i2c_address_);
  EXPECT_EQ(init_return, types::DriverStatus::HAL_ERROR);
}

TEST_F(GyroscopeTests, gyroscope_read_bytesize_mismatch) {
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