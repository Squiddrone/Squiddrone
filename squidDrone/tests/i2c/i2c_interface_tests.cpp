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

    uint8_t address = 0x10;
    uint16_t byte_size = 3;
    uint32_t timeout = 2;
    std::vector<uint8_t> data = {1, 2};

    i2c::I2CStatus result_status;
    std::vector<uint8_t> result_data;
  };

  TEST_F(I2CInterfaceTests, read_successful){
    std::tie(result_status, result_data) = unit_under_test_->Read(address, byte_size, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL);
    EXPECT_THAT(result_data, testing::ElementsAre(1, 2, 3));
  }

  TEST_F(I2CInterfaceTests, read_failed){
    address = 0x11;
    std::tie(result_status, result_data) = unit_under_test_->Read(address, byte_size, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_TRANSACTION_FAILED);
  }

  TEST_F(I2CInterfaceTests, read_timeout){
    address = 0x12;
    std::tie(result_status, result_data) = unit_under_test_->Read(address, byte_size, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_TRANSACTION_TIMEOUT);
  }

  TEST_F(I2CInterfaceTests, read_busy){
    address = 0x13;
    std::tie(result_status, result_data) = unit_under_test_->Read(address, byte_size, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_TRANSACTION_BUSY);
  }

  TEST_F(I2CInterfaceTests, read_byte_size_0){
    byte_size = 0;
    std::tie(result_status, result_data) = unit_under_test_->Read(address, byte_size, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_PARAMETER_ERROR);
  }

  TEST_F(I2CInterfaceTests, read_timeout_0){
    timeout = 0;
    std::tie(result_status, result_data) = unit_under_test_->Read(address, byte_size, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_PARAMETER_ERROR);
  }

  TEST_F(I2CInterfaceTests, read_address_out_of_range_0){
    address = 0x00;
    std::tie(result_status, result_data) = unit_under_test_->Read(address, byte_size, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_PARAMETER_ERROR);
  }

  TEST_F(I2CInterfaceTests, read_address_out_of_range_0x78){
    address = 0x78;
    std::tie(result_status, result_data) = unit_under_test_->Read(address, byte_size, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_PARAMETER_ERROR);
  }

  TEST_F(I2CInterfaceTests, write_successful){
    auto result_status = unit_under_test_->Write(address, data, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL);
  }

  TEST_F(I2CInterfaceTests, write_failed){
    address = 0x11;
    auto result_status = unit_under_test_->Write(address, data, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_TRANSACTION_FAILED);
  }

  TEST_F(I2CInterfaceTests, write_timeout){
    address = 0x12;
    auto result_status = unit_under_test_->Write(address, data, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_TRANSACTION_TIMEOUT);
  }

  TEST_F(I2CInterfaceTests, write_busy){
    address = 0x13;
    auto result_status = unit_under_test_->Write(address, data, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_TRANSACTION_BUSY);
  }

  TEST_F(I2CInterfaceTests, write_data_empty){
    data.clear();
    auto result_status = unit_under_test_->Write(address, data, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_PARAMETER_ERROR);
  }

  TEST_F(I2CInterfaceTests, write_timeout_0){
    timeout = 0;
    auto result_status = unit_under_test_->Write(address, data, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_PARAMETER_ERROR);
  }

  TEST_F(I2CInterfaceTests, write_address_out_of_range_0){
    address = 0x0;
    auto result_status = unit_under_test_->Write(address, data, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_PARAMETER_ERROR);
  }

  TEST_F(I2CInterfaceTests, write_address_out_of_range_0x78){
    address = 0x78;
    auto result_status = unit_under_test_->Write(address, data, timeout);

    EXPECT_EQ(result_status, i2c::I2CStatus::I2C_PARAMETER_ERROR);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}