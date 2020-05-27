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
    auto address = 0x10;
    auto byte_size = 3;
    auto timeout = 2;
    i2c::I2CStatus result_status;
    std::vector<uint8_t> result_data;
    std::tie(result_status, result_data) = unit_under_test_->read(address, byte_size, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL);
    EXPECT_THAT(result_data, testing::ElementsAre(1, 2, 3));
  }

  TEST_F(I2CInterfaceTests, read_failed){
    auto address = 0x11;
    auto byte_size = 3;
    auto timeout = 2;
    i2c::I2CStatus result_status;
    std::vector<uint8_t> result_data;
    std::tie(result_status, result_data) = unit_under_test_->read(address, byte_size, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_TRANSACTION_FAILED);
  }

  TEST_F(I2CInterfaceTests, read_timeout){
    auto address = 0x12;
    auto byte_size = 3;
    auto timeout = 2;
    i2c::I2CStatus result_status;
    std::vector<uint8_t> result_data;
    std::tie(result_status, result_data) = unit_under_test_->read(address, byte_size, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_TRANSACTION_TIMEOUT);
  }

  TEST_F(I2CInterfaceTests, read_busy){
    auto address = 0x13;
    auto byte_size = 3;
    auto timeout = 2;
    i2c::I2CStatus result_status;
    std::vector<uint8_t> result_data;
    std::tie(result_status, result_data) = unit_under_test_->read(address, byte_size, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_TRANSACTION_BUSY);
  }

  TEST_F(I2CInterfaceTests, read_byte_size_0){
    auto address = 0x10;
    auto byte_size = 0;
    auto timeout = 2;
    i2c::I2CStatus result_status;
    std::vector<uint8_t> result_data;
    std::tie(result_status, result_data) = unit_under_test_->read(address, byte_size, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_PARAMETER_ERROR);
  }

  TEST_F(I2CInterfaceTests, read_timeout_0){
    auto address = 0x10;
    auto byte_size = 3;
    auto timeout = 0;
    i2c::I2CStatus result_status;
    std::vector<uint8_t> result_data;
    std::tie(result_status, result_data) = unit_under_test_->read(address, byte_size, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_PARAMETER_ERROR);
  }

  TEST_F(I2CInterfaceTests, read_address_out_of_range_0){
    auto address = 0x00;
    auto byte_size = 3;
    auto timeout = 2;
    i2c::I2CStatus result_status;
    std::vector<uint8_t> result_data;
    std::tie(result_status, result_data) = unit_under_test_->read(address, byte_size, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_PARAMETER_ERROR);
  }

  TEST_F(I2CInterfaceTests, read_address_out_of_range_0x78){
    auto address = 0x78;
    auto byte_size = 3;
    auto timeout = 2;
    i2c::I2CStatus result_status;
    std::vector<uint8_t> result_data;
    std::tie(result_status, result_data) = unit_under_test_->read(address, byte_size, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_PARAMETER_ERROR);
  }

    TEST_F(I2CInterfaceTests, write_successful){
    auto address = 0x10;
    std::vector<uint8_t> data = {1, 2};
    auto timeout = 2;
    std::vector<uint8_t> result_data;
    auto result_status = unit_under_test_->write(address, data, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL);
  }

  TEST_F(I2CInterfaceTests, write_failed){
    auto address = 0x11;
    std::vector<uint8_t> data = {1, 2};
    auto timeout = 2;
    std::vector<uint8_t> result_data;
    auto result_status = unit_under_test_->write(address, data, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_TRANSACTION_FAILED);
  }

  TEST_F(I2CInterfaceTests, write_timeout){
    auto address = 0x12;
    std::vector<uint8_t> data = {1, 2};
    auto timeout = 2;
    std::vector<uint8_t> result_data;
    auto result_status = unit_under_test_->write(address, data, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_TRANSACTION_TIMEOUT);
  }

  TEST_F(I2CInterfaceTests, write_busy){
    auto address = 0x13;
    std::vector<uint8_t> data = {1, 2};
    auto timeout = 2;
    std::vector<uint8_t> result_data;
    auto result_status = unit_under_test_->write(address, data, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_TRANSACTION_BUSY);
  }

  TEST_F(I2CInterfaceTests, write_data_empty){
    auto address = 0x10;
    std::vector<uint8_t> data = {};
    auto timeout = 2;
    std::vector<uint8_t> result_data;
    auto result_status = unit_under_test_->write(address, data, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_PARAMETER_ERROR);
  }

  TEST_F(I2CInterfaceTests, write_timeout_0){
    auto address = 0x10;
    std::vector<uint8_t> data = {1, 2};
    auto timeout = 0;
    std::vector<uint8_t> result_data;
    auto result_status = unit_under_test_->write(address, data, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_PARAMETER_ERROR);
  }

  TEST_F(I2CInterfaceTests, write_address_out_of_range_0){
    auto address = 0x0;
    std::vector<uint8_t> data = {1, 2};
    auto timeout = 2;
    std::vector<uint8_t> result_data;
    auto result_status = unit_under_test_->write(address, data, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_PARAMETER_ERROR);
  }

  TEST_F(I2CInterfaceTests, write_address_out_of_range_0x78){
    auto address = 0x78;
    std::vector<uint8_t> data = {1, 2};
    auto timeout = 2;
    std::vector<uint8_t> result_data;
    auto result_status = unit_under_test_->write(address, data, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_PARAMETER_ERROR);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}