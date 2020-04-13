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

  TEST(imu, imu_interface_set_accelerometer_sensitivity_finest){
    i2c::I2CHandler i2c_handler;
    imu::InertialMeasurementInterface imu_interface(i2c_handler);
    types::AccelerometerSensitivity sensitivity = types::AccelerometerSensitivity::FINEST;
    imu_interface.SetAccelerometerSensitivity(sensitivity);
    types::AccelerometerSensitivity gyroscope_sensitivity_return = imu_interface.GetAccelerometerSensitivity();
    EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
  }

  TEST(imu, imu_interface_set_accelerometer_sensitivity_finer){
    i2c::I2CHandler i2c_handler;
    imu::InertialMeasurementInterface imu_interface(i2c_handler);
    types::AccelerometerSensitivity sensitivity = types::AccelerometerSensitivity::FINER;
    imu_interface.SetAccelerometerSensitivity(sensitivity);
    types::AccelerometerSensitivity gyroscope_sensitivity_return = imu_interface.GetAccelerometerSensitivity();
    EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
  }

  TEST(imu, imu_interface_set_accelerometer_sensitivity_rougher){
    i2c::I2CHandler i2c_handler;
    imu::InertialMeasurementInterface imu_interface(i2c_handler);
    types::AccelerometerSensitivity sensitivity = types::AccelerometerSensitivity::ROUGHER;
    imu_interface.SetAccelerometerSensitivity(sensitivity);
    types::AccelerometerSensitivity gyroscope_sensitivity_return = imu_interface.GetAccelerometerSensitivity();
    EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
  }

  TEST(imu, imu_interface_set_accelerometer_sensitivity_roughest){
    i2c::I2CHandler i2c_handler;
    imu::InertialMeasurementInterface imu_interface(i2c_handler);
    types::AccelerometerSensitivity sensitivity = types::AccelerometerSensitivity::ROUGHEST;
    imu_interface.SetAccelerometerSensitivity(sensitivity);
    types::AccelerometerSensitivity gyroscope_sensitivity_return = imu_interface.GetAccelerometerSensitivity();
    EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
  }

  TEST(imu, imu_interface_get_accelerometer_sensitivity_default){
    i2c::I2CHandler i2c_handler;
    imu::InertialMeasurementInterface imu_interface(i2c_handler);
    types::AccelerometerSensitivity sensitivity = types::AccelerometerSensitivity::FINEST;
    types::AccelerometerSensitivity gyroscope_sensitivity_return = imu_interface.GetAccelerometerSensitivity();
    EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}