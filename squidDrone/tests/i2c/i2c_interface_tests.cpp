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

  TEST_F(I2CInterfaceTests, dummy){
    auto command = 0x01;
    auto data = std::vector<uint8_t>{1, 2, 3};
    auto timeout = 2;
    auto result = unit_under_test_->read(command, data, timeout);

    EXPECT_THAT(result, testing::ElementsAre(1, 2, 3));
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}