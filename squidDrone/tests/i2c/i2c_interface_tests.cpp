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

  TEST_F(I2CInterfaceTests, read_successful){
    auto address = 0x01;
    auto byte_size = 3;
    auto timeout = 2;
    i2c::I2CStatus result_status;
    std::vector<uint8_t> result_data;
    std::tie(result_status, result_data) = unit_under_test_->read(address, byte_size, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL);
    EXPECT_THAT(result_data, testing::ElementsAre(1, 2, 3));
  }

  TEST_F(I2CInterfaceTests, read_failed){
    auto address = 0x02;
    auto byte_size = 3;
    auto timeout = 2;
    i2c::I2CStatus result_status;
    std::vector<uint8_t> result_data;
    std::tie(result_status, result_data) = unit_under_test_->read(address, byte_size, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_TRANSACTION_FAILED);
  }

  TEST_F(I2CInterfaceTests, read_timeout){
    auto address = 0x03;
    auto byte_size = 3;
    auto timeout = 2;
    i2c::I2CStatus result_status;
    std::vector<uint8_t> result_data;
    std::tie(result_status, result_data) = unit_under_test_->read(address, byte_size, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_TRANSACTION_TIMEOUT);
  }

  TEST_F(I2CInterfaceTests, read_busy){
    auto address = 0x04;
    auto byte_size = 3;
    auto timeout = 2;
    i2c::I2CStatus result_status;
    std::vector<uint8_t> result_data;
    std::tie(result_status, result_data) = unit_under_test_->read(address, byte_size, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_TRANSACTION_BUSY);
  }

  TEST_F(I2CInterfaceTests, read_byte_size_0){
    auto address = 0x01;
    auto byte_size = 0;
    auto timeout = 2;
    i2c::I2CStatus result_status;
    std::vector<uint8_t> result_data;
    std::tie(result_status, result_data) = unit_under_test_->read(address, byte_size, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_TRANSACTION_FAILED);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}