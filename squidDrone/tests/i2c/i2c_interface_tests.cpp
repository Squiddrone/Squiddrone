#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "i2c.hpp"

namespace{

  class I2CInterfaceTests: public ::testing::Test{
  protected:
    virtual void SetUp(){
      unit_under_test_ = std::make_unique<i2c::I2C>();
    }

    std::unique_ptr<i2c::I2C> unit_under_test_;
  };

  TEST_F(I2CInterfaceTests, read_command_successful){
    auto command = 0x01;
    auto data = std::vector<uint8_t>{1, 2, 3};
    auto timeout = 2;
    i2c::I2CStatus result_status;
    std::vector<uint8_t> result_data;
    std::tie(result_status, result_data) = unit_under_test_->read(command, data, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL);
    EXPECT_THAT(result_data, testing::ElementsAre(1, 2, 3));
  }

  TEST_F(I2CInterfaceTests, read_command_failed){
    auto command = 0x02;
    auto data = std::vector<uint8_t>{0, 0};
    auto timeout = 2;
    i2c::I2CStatus result_status;
    std::vector<uint8_t> result_data;
    std::tie(result_status, result_data) = unit_under_test_->read(command, data, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_TRANSACTION_FAILED);
  }

  TEST_F(I2CInterfaceTests, read_command_timeout){
    auto command = 0x03;
    auto data = std::vector<uint8_t>{0, 0};
    auto timeout = 2;
    i2c::I2CStatus result_status;
    std::vector<uint8_t> result_data;
    std::tie(result_status, result_data) = unit_under_test_->read(command, data, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_TRANSACTION_TIMEOUT);
  }

  TEST_F(I2CInterfaceTests, read_command_busy){
    auto command = 0x04;
    auto data = std::vector<uint8_t>{0, 0};
    auto timeout = 2;
    i2c::I2CStatus result_status;
    std::vector<uint8_t> result_data;
    std::tie(result_status, result_data) = unit_under_test_->read(command, data, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_TRANSACTION_BUSY);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}