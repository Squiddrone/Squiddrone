#include "gtest/gtest.h"
#include "gyroscope.hpp"
#include "i2c.hpp"

namespace {

class GyroscopeTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    auto i2c_handler_ = std::make_unique<i2c::I2C>();
    types::GyroscopeSensitivity sensitivity = types::GyroscopeSensitivity::FINEST;
    unit_under_test_ = std::make_unique<imu::Gyroscope>(std::move(i2c_handler_), sensitivity);
  }

  std::unique_ptr<i2c::I2C> i2c_handler_;
  std::unique_ptr<imu::Gyroscope> unit_under_test_;
};

TEST_F(GyroscopeTests, gyroscope_test1) {
  EXPECT_EQ(0, 1);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}