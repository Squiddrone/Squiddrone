#include <gmock/gmock.h>
#include "gtest/gtest.h"
#include "gyroscope.hpp"
#include "mock_i2c.hpp"

using ::testing::_;
using ::testing::Return;

namespace {

class GyroscopeTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    i2c_handler_ = std::make_unique<i2c::MOCKI2C>();
  }
  uint8_t i2c_address_ = 0x68;
  std::unique_ptr<i2c::MOCKI2C> i2c_handler_;
};

TEST_F(GyroscopeTests, gyroscope_Init_working) {
  EXPECT_CALL(*i2c_handler_, Write(_, _, _))
      .WillRepeatedly(Return(i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL));

  std::tuple<i2c::I2CStatus, std::vector<std::uint8_t>> answer_who_am_i{
      i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL, {imu::WHO_AM_I_MPU9255_VALUE}};
  std::tuple<i2c::I2CStatus, std::vector<std::uint8_t>> answer_config{
      i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL, {0b11111111}};
  EXPECT_CALL(*i2c_handler_, Read(_, _, _))
      .WillOnce(Return(answer_who_am_i))
      .WillOnce(Return(answer_config));

  std::unique_ptr<imu::Gyroscope> unit_under_test_ = std::make_unique<imu::Gyroscope>(std::move(i2c_handler_));

  auto gyroscope_init_return = unit_under_test_->Init(i2c_address_);

  EXPECT_EQ(gyroscope_init_return, types::HalError::WORKING);
}

TEST_F(GyroscopeTests, gyroscope_Init_failed) {
  EXPECT_CALL(*i2c_handler_, Write(_, _, _))
      .WillRepeatedly(Return(i2c::I2CStatus::I2C_TRANSACTION_FAILED));

  std::unique_ptr<imu::Gyroscope> unit_under_test_ = std::make_unique<imu::Gyroscope>(std::move(i2c_handler_));

  auto gyroscope_init_return = unit_under_test_->Init(0);

  EXPECT_EQ(gyroscope_init_return, types::HalError::CONFIG_ERROR);
}

TEST_F(GyroscopeTests, gyroscope_Update) {
  EXPECT_CALL(*i2c_handler_, Write(_, _, _))
      .WillRepeatedly(Return(i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL));

  std::tuple<i2c::I2CStatus, std::vector<std::uint8_t>> answer_who_am_i{
      i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL, {imu::WHO_AM_I_MPU9255_VALUE}};
  std::tuple<i2c::I2CStatus, std::vector<std::uint8_t>> answer_config{
      i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL, {0b11111111}};
  std::tuple<i2c::I2CStatus, std::vector<std::uint8_t>> answer_update{
      i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL, {0, 15, 0, 25, 0, 35}};
  EXPECT_CALL(*i2c_handler_, Read(_, _, _))
      .WillOnce(Return(answer_who_am_i))
      .WillOnce(Return(answer_config))
      .WillOnce(Return(answer_update));

  std::unique_ptr<imu::Gyroscope> unit_under_test_ = std::make_unique<imu::Gyroscope>(std::move(i2c_handler_));

  unit_under_test_->Init(i2c_address_);
  auto gyroscope_update_return = unit_under_test_->Update();
  EXPECT_EQ(gyroscope_update_return, types::HalError::WORKING);
}

TEST_F(GyroscopeTests, gyroscope_Update_without_Init_first) {
  std::unique_ptr<imu::Gyroscope> unit_under_test_ = std::make_unique<imu::Gyroscope>(std::move(i2c_handler_));

  auto gyroscope_update_return = unit_under_test_->Update();
  EXPECT_EQ(gyroscope_update_return, types::HalError::CONFIG_ERROR);
}

TEST_F(GyroscopeTests, gyroscope_Get_without_Update_and_Init_first) {
  std::unique_ptr<imu::Gyroscope> unit_under_test_ = std::make_unique<imu::Gyroscope>(std::move(i2c_handler_));

  types::EuclideanVector<float> expected_value{-1, -1, -1};
  auto gyroscope_get_return = unit_under_test_->Get();

  EXPECT_EQ(gyroscope_get_return.x, expected_value.x);
  EXPECT_EQ(gyroscope_get_return.y, expected_value.y);
  EXPECT_EQ(gyroscope_get_return.z, expected_value.z);
}

TEST_F(GyroscopeTests, gyroscope_Get_without_Update_first) {
  EXPECT_CALL(*i2c_handler_, Write(_, _, _))
      .WillRepeatedly(Return(i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL));

  std::tuple<i2c::I2CStatus, std::vector<std::uint8_t>> answer_who_am_i{
      i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL, {imu::WHO_AM_I_MPU9255_VALUE}};
  std::tuple<i2c::I2CStatus, std::vector<std::uint8_t>> answer_config{
      i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL, {0b11111111}};
  EXPECT_CALL(*i2c_handler_, Read(_, _, _))
      .WillOnce(Return(answer_who_am_i))
      .WillOnce(Return(answer_config));

  std::unique_ptr<imu::Gyroscope> unit_under_test_ = std::make_unique<imu::Gyroscope>(std::move(i2c_handler_));

  types::EuclideanVector<float> expected_value{0, 0, 0};
  unit_under_test_->Init(i2c_address_);
  auto gyroscope_get_return = unit_under_test_->Get();

  EXPECT_EQ(gyroscope_get_return.x, expected_value.x);
  EXPECT_EQ(gyroscope_get_return.y, expected_value.y);
  EXPECT_EQ(gyroscope_get_return.z, expected_value.z);
}

TEST_F(GyroscopeTests, gyroscope_full) {
  EXPECT_CALL(*i2c_handler_, Write(_, _, _))
      .WillRepeatedly(Return(i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL));

  std::tuple<i2c::I2CStatus, std::vector<std::uint8_t>> answer_who_am_i{
      i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL, {imu::WHO_AM_I_MPU9255_VALUE}};
  std::tuple<i2c::I2CStatus, std::vector<std::uint8_t>> answer_config{
      i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL, {0b11111111}};
  std::tuple<i2c::I2CStatus, std::vector<std::uint8_t>> answer_update{
      i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL, {0, 15, 0, 25, 0, 35}};
  EXPECT_CALL(*i2c_handler_, Read(_, _, _))
      .WillOnce(Return(answer_who_am_i))
      .WillOnce(Return(answer_config))
      .WillOnce(Return(answer_update));

  std::unique_ptr<imu::Gyroscope> unit_under_test_ = std::make_unique<imu::Gyroscope>(std::move(i2c_handler_));

  types::EuclideanVector<float> expected_value{15, 25, 35};
  unit_under_test_->Init(i2c_address_);
  unit_under_test_->Update();
  auto gyroscope_get_return = unit_under_test_->Get();

  EXPECT_EQ(gyroscope_get_return.x, expected_value.x);
  EXPECT_EQ(gyroscope_get_return.y, expected_value.y);
  EXPECT_EQ(gyroscope_get_return.z, expected_value.z);
}

TEST_F(GyroscopeTests, gyroscope_SetSensitivity_finest) {
  EXPECT_CALL(*i2c_handler_, Write(_, _, _))
      .WillRepeatedly(Return(i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL));

  std::tuple<i2c::I2CStatus, std::vector<std::uint8_t>> answer_who_am_i{
      i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL, {imu::WHO_AM_I_MPU9255_VALUE}};
  std::tuple<i2c::I2CStatus, std::vector<std::uint8_t>> answer_config{
      i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL, {0b11111111}};
  EXPECT_CALL(*i2c_handler_, Read(_, _, _))
      .WillOnce(Return(answer_who_am_i))
      .WillOnce(Return(answer_config))
      .WillOnce(Return(answer_config));

  std::unique_ptr<imu::Gyroscope> unit_under_test_ = std::make_unique<imu::Gyroscope>(std::move(i2c_handler_));

  unit_under_test_->Init(i2c_address_);
  auto gyroscope_sensitivity_return = unit_under_test_->SetSensitivity(types::GyroscopeSensitivity::FINEST);
  EXPECT_EQ(gyroscope_sensitivity_return, types::HalError::WORKING);
}

TEST_F(GyroscopeTests, gyroscope_SetSensitivity_finer) {
  EXPECT_CALL(*i2c_handler_, Write(_, _, _))
      .WillRepeatedly(Return(i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL));

  std::tuple<i2c::I2CStatus, std::vector<std::uint8_t>> answer_who_am_i{
      i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL, {imu::WHO_AM_I_MPU9255_VALUE}};
  std::tuple<i2c::I2CStatus, std::vector<std::uint8_t>> answer_config{
      i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL, {0b11111111}};
  EXPECT_CALL(*i2c_handler_, Read(_, _, _))
      .WillOnce(Return(answer_who_am_i))
      .WillOnce(Return(answer_config))
      .WillOnce(Return(answer_config));

  std::unique_ptr<imu::Gyroscope> unit_under_test_ = std::make_unique<imu::Gyroscope>(std::move(i2c_handler_));

  unit_under_test_->Init(i2c_address_);
  auto gyroscope_sensitivity_return = unit_under_test_->SetSensitivity(types::GyroscopeSensitivity::FINER);
  EXPECT_EQ(gyroscope_sensitivity_return, types::HalError::WORKING);
}

TEST_F(GyroscopeTests, gyroscope_SetSensitivity_rougher) {
  EXPECT_CALL(*i2c_handler_, Write(_, _, _))
      .WillRepeatedly(Return(i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL));

  std::tuple<i2c::I2CStatus, std::vector<std::uint8_t>> answer_who_am_i{
      i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL, {imu::WHO_AM_I_MPU9255_VALUE}};
  std::tuple<i2c::I2CStatus, std::vector<std::uint8_t>> answer_config{
      i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL, {0b11111111}};
  EXPECT_CALL(*i2c_handler_, Read(_, _, _))
      .WillOnce(Return(answer_who_am_i))
      .WillOnce(Return(answer_config))
      .WillOnce(Return(answer_config));

  std::unique_ptr<imu::Gyroscope> unit_under_test_ = std::make_unique<imu::Gyroscope>(std::move(i2c_handler_));

  unit_under_test_->Init(i2c_address_);
  auto gyroscope_sensitivity_return = unit_under_test_->SetSensitivity(types::GyroscopeSensitivity::ROUGHER);
  EXPECT_EQ(gyroscope_sensitivity_return, types::HalError::WORKING);
}

TEST_F(GyroscopeTests, gyroscope_SetSensitivity_roughest) {
  EXPECT_CALL(*i2c_handler_, Write(_, _, _))
      .WillRepeatedly(Return(i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL));

  std::tuple<i2c::I2CStatus, std::vector<std::uint8_t>> answer_who_am_i{
      i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL, {imu::WHO_AM_I_MPU9255_VALUE}};
  std::tuple<i2c::I2CStatus, std::vector<std::uint8_t>> answer_config{
      i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL, {0b11111111}};
  EXPECT_CALL(*i2c_handler_, Read(_, _, _))
      .WillOnce(Return(answer_who_am_i))
      .WillOnce(Return(answer_config))
      .WillOnce(Return(answer_config));

  std::unique_ptr<imu::Gyroscope> unit_under_test_ = std::make_unique<imu::Gyroscope>(std::move(i2c_handler_));

  unit_under_test_->Init(i2c_address_);
  auto gyroscope_sensitivity_return = unit_under_test_->SetSensitivity(types::GyroscopeSensitivity::ROUGHEST);
  EXPECT_EQ(gyroscope_sensitivity_return, types::HalError::WORKING);
}

TEST_F(GyroscopeTests, gyroscope_SetSensitivity_failes_stored_sensitivity_stays_same) {
  EXPECT_CALL(*i2c_handler_, Write(_, _, _))
      .WillRepeatedly(Return(i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL));

  std::tuple<i2c::I2CStatus, std::vector<std::uint8_t>> answer_who_am_i{
      i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL, {imu::WHO_AM_I_MPU9255_VALUE}};
  std::tuple<i2c::I2CStatus, std::vector<std::uint8_t>> answer_config{
      i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL, {0b11111111}};
  EXPECT_CALL(*i2c_handler_, Read(_, _, _))
      .WillOnce(Return(answer_who_am_i))
      .WillOnce(Return(answer_config))
      .WillOnce(Return(answer_config))
      .WillOnce(Return(answer_config));

  std::unique_ptr<imu::Gyroscope> unit_under_test_ = std::make_unique<imu::Gyroscope>(std::move(i2c_handler_));

  unit_under_test_->Init(i2c_address_);
  auto set_sensitivity = types::GyroscopeSensitivity::ROUGHEST;
  auto gyroscope_sensitivity_return = unit_under_test_->SetSensitivity(set_sensitivity);
  auto gyroscope_get = unit_under_test_->GetSensitivity();
  EXPECT_EQ(gyroscope_sensitivity_return, types::HalError::WORKING);
  EXPECT_EQ(gyroscope_get, set_sensitivity);
  unit_under_test_->Init(0);
  gyroscope_sensitivity_return = unit_under_test_->SetSensitivity(types::GyroscopeSensitivity::FINEST);
  EXPECT_EQ(gyroscope_sensitivity_return, types::HalError::CONFIG_ERROR);
  EXPECT_EQ(gyroscope_get, set_sensitivity);
}

TEST_F(GyroscopeTests, gyroscope_SetSensitivity_without_Init_first) {
  std::unique_ptr<imu::Gyroscope> unit_under_test_ = std::make_unique<imu::Gyroscope>(std::move(i2c_handler_));

  auto gyroscope_sensitivity_return = unit_under_test_->SetSensitivity(types::GyroscopeSensitivity::ROUGHEST);
  EXPECT_EQ(gyroscope_sensitivity_return, types::HalError::CONFIG_ERROR);
}

TEST_F(GyroscopeTests, gyroscope_SetSensitivity_GetSensitivity) {
  EXPECT_CALL(*i2c_handler_, Write(_, _, _))
      .WillRepeatedly(Return(i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL));

  std::tuple<i2c::I2CStatus, std::vector<std::uint8_t>> answer_who_am_i{
      i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL, {imu::WHO_AM_I_MPU9255_VALUE}};
  std::tuple<i2c::I2CStatus, std::vector<std::uint8_t>> answer_config{
      i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL, {0b11111111}};
  EXPECT_CALL(*i2c_handler_, Read(_, _, _))
      .WillOnce(Return(answer_who_am_i))
      .WillOnce(Return(answer_config))
      .WillOnce(Return(answer_config))
      .WillOnce(Return(answer_config));

  std::unique_ptr<imu::Gyroscope> unit_under_test_ = std::make_unique<imu::Gyroscope>(std::move(i2c_handler_));

  unit_under_test_->Init(i2c_address_);
  auto set_sensitivity = types::GyroscopeSensitivity::ROUGHEST;
  unit_under_test_->SetSensitivity(set_sensitivity);
  auto gyroscope_get = unit_under_test_->GetSensitivity();
  EXPECT_EQ(gyroscope_get, set_sensitivity);
  set_sensitivity = types::GyroscopeSensitivity::FINEST;
  unit_under_test_->SetSensitivity(set_sensitivity);
  gyroscope_get = unit_under_test_->GetSensitivity();
  EXPECT_EQ(gyroscope_get, set_sensitivity);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}