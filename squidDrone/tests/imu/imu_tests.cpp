#include "gtest/gtest.h"
#include "imu_interface.hpp"

namespace{

  TEST(imu_interface, set_gyroscope_sensitivity){
    i2c::I2CHandler i2c_handler;
    imu::InertialMeasurementInterface imu_interface(i2c_handler);
    types::GyroscopeSensitivity sensitivity = types::GyroscopeSensitivity::FINEST;
    imu_interface.SetGyroscopeSensitivity(sensitivity);
    EXPECT_EQ(1, 2);
  }

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}