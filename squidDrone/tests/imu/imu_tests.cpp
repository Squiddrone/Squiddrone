#include "gtest/gtest.h"
#include "imu_interface.hpp"

namespace{

  TEST(imu, imu_interface_set_gyroscope_sensitivity_finest){
    i2c::I2CHandler i2c_handler;
    imu::InertialMeasurementInterface imu_interface(i2c_handler);
    types::GyroscopeSensitivity sensitivity = types::GyroscopeSensitivity::FINEST;
    imu_interface.SetGyroscopeSensitivity(sensitivity);
    types::GyroscopeSensitivity gyroscope_sensitivity_return = imu_interface.GetGyroscopeSensitivity();
    EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
  }

  TEST(imu, imu_interface_set_gyroscope_sensitivity_finer){
    i2c::I2CHandler i2c_handler;
    imu::InertialMeasurementInterface imu_interface(i2c_handler);
    types::GyroscopeSensitivity sensitivity = types::GyroscopeSensitivity::FINER;
    imu_interface.SetGyroscopeSensitivity(sensitivity);
    types::GyroscopeSensitivity gyroscope_sensitivity_return = imu_interface.GetGyroscopeSensitivity();
    EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
  }

  TEST(imu, imu_interface_set_gyroscope_sensitivity_rougher){
    i2c::I2CHandler i2c_handler;
    imu::InertialMeasurementInterface imu_interface(i2c_handler);
    types::GyroscopeSensitivity sensitivity = types::GyroscopeSensitivity::ROUGHER;
    imu_interface.SetGyroscopeSensitivity(sensitivity);
    types::GyroscopeSensitivity gyroscope_sensitivity_return = imu_interface.GetGyroscopeSensitivity();
    EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
  }

  TEST(imu, imu_interface_set_gyroscope_sensitivity_roughest){
    i2c::I2CHandler i2c_handler;
    imu::InertialMeasurementInterface imu_interface(i2c_handler);
    types::GyroscopeSensitivity sensitivity = types::GyroscopeSensitivity::ROUGHEST;
    imu_interface.SetGyroscopeSensitivity(sensitivity);
    types::GyroscopeSensitivity gyroscope_sensitivity_return = imu_interface.GetGyroscopeSensitivity();
    EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
  }

  TEST(imu, imu_interface_get_gyroscope_sensitivity_default){
    i2c::I2CHandler i2c_handler;
    imu::InertialMeasurementInterface imu_interface(i2c_handler);
    types::GyroscopeSensitivity sensitivity = types::GyroscopeSensitivity::FINEST;
    types::GyroscopeSensitivity gyroscope_sensitivity_return = imu_interface.GetGyroscopeSensitivity();
    EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
  }

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}