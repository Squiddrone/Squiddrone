#include <gmock/gmock.h>
#include "gtest/gtest.h"
#include "mock_i2c.hpp"
#include "temperature.hpp"

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;

namespace {

class TemperatureTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    ON_CALL(*i2c_handler_, Write(_, _, _))
        .WillByDefault(Return(types::DriverStatus::OK));

    ON_CALL(*i2c_handler_, ReadContentFromRegister(_, _, _, _))
        .WillByDefault(Return(answer_to_who_am_i));
    ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::WHO_AM_I_MPU9255_REGISTER, _, _))
        .WillByDefault(Return(answer_to_who_am_i));
    ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::TEMP_OUT_H, _, _))
        .WillByDefault(Return(answer_to_update));
  }

  virtual void ConfigureUnitUnderTest() {
    unit_under_test_ = std::make_unique<imu::Temperature>(i2c_handler_);
  }

  uint8_t i2c_address_ = 0x68;
  std::shared_ptr<i2c::MockI2C> i2c_handler_ = std::make_shared<NiceMock<i2c::MockI2C>>();
  std::unique_ptr<imu::Temperature> unit_under_test_;

  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_to_who_am_i{
      types::DriverStatus::OK, {imu::WHO_AM_I_MPU9255_VALUE}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_to_update{
      types::DriverStatus::OK, {0, 25}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_read_mismatch{
      types::DriverStatus::OK, {0, 25, 0}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_invalid{
      types::DriverStatus::HAL_ERROR, {}};
};

TEST_F(TemperatureTests, Init_OK) {
  ConfigureUnitUnderTest();

  auto init_return = unit_under_test_->Init(i2c_address_);

  EXPECT_EQ(init_return, types::DriverStatus::OK);
}

TEST_F(TemperatureTests, Init_failed) {
  ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::WHO_AM_I_MPU9255_REGISTER, _, _))
      .WillByDefault(Return(answer_invalid));

  ConfigureUnitUnderTest();

  auto init_return = unit_under_test_->Init(0);

  EXPECT_EQ(init_return, types::DriverStatus::HAL_ERROR);
}

TEST_F(TemperatureTests, Update) {
  ConfigureUnitUnderTest();

  unit_under_test_->Init(i2c_address_);
  auto update_return = unit_under_test_->Update_();
  EXPECT_EQ(update_return, types::DriverStatus::OK);
}

TEST_F(TemperatureTests, Update_without_Init_first) {
  ConfigureUnitUnderTest();

  auto update_return = unit_under_test_->Update_();
  EXPECT_EQ(update_return, types::DriverStatus::HAL_ERROR);
}

TEST_F(TemperatureTests, Get_without_Update_and_Init_first) {
  ConfigureUnitUnderTest();

  std::int16_t expected_value = -1;
  auto get_return = unit_under_test_->Get_();

  EXPECT_EQ(get_return, expected_value);
}

TEST_F(TemperatureTests, Get_without_Update_first) {
  ConfigureUnitUnderTest();

  std::int16_t expected_value = 0;
  unit_under_test_->Init(i2c_address_);
  auto get_return = unit_under_test_->Get_();

  EXPECT_EQ(get_return, expected_value);
}

TEST_F(TemperatureTests, full) {
  ConfigureUnitUnderTest();

  std::int16_t expected_value = 25;
  unit_under_test_->Init(i2c_address_);
  unit_under_test_->Update_();
  auto get_return = unit_under_test_->Get_();

  EXPECT_EQ(get_return, expected_value);
}

TEST_F(TemperatureTests, read_bytesize_mismatch) {
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