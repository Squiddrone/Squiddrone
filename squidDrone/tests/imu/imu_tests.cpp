#include "gtest/gtest.h"
#include "inertial_measurement.hpp"

namespace{

  TEST(imu, interface_set_gyroscope_sensitivity_finest){
    i2c::I2CHandler i2c_handler;
    imu::InertialMeasurement imu_interface(i2c_handler);
    types::GyroscopeSensitivity sensitivity = types::GyroscopeSensitivity::FINEST;
    imu_interface.SetGyroscopeSensitivity(sensitivity);
    types::GyroscopeSensitivity gyroscope_sensitivity_return = imu_interface.GetGyroscopeSensitivity();
    EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
  }

  TEST(imu, interface_set_gyroscope_sensitivity_finer){
    i2c::I2CHandler i2c_handler;
    imu::InertialMeasurement imu_interface(i2c_handler);
    types::GyroscopeSensitivity sensitivity = types::GyroscopeSensitivity::FINER;
    imu_interface.SetGyroscopeSensitivity(sensitivity);
    types::GyroscopeSensitivity gyroscope_sensitivity_return = imu_interface.GetGyroscopeSensitivity();
    EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
  }

  TEST(imu, interface_set_gyroscope_sensitivity_rougher){
    i2c::I2CHandler i2c_handler;
    imu::InertialMeasurement imu_interface(i2c_handler);
    types::GyroscopeSensitivity sensitivity = types::GyroscopeSensitivity::ROUGHER;
    imu_interface.SetGyroscopeSensitivity(sensitivity);
    types::GyroscopeSensitivity gyroscope_sensitivity_return = imu_interface.GetGyroscopeSensitivity();
    EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
  }

  TEST(imu, interface_set_gyroscope_sensitivity_roughest){
    i2c::I2CHandler i2c_handler;
    imu::InertialMeasurement imu_interface(i2c_handler);
    types::GyroscopeSensitivity sensitivity = types::GyroscopeSensitivity::ROUGHEST;
    imu_interface.SetGyroscopeSensitivity(sensitivity);
    types::GyroscopeSensitivity gyroscope_sensitivity_return = imu_interface.GetGyroscopeSensitivity();
    EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
  }

  TEST(imu, interface_get_gyroscope_sensitivity_default){
    i2c::I2CHandler i2c_handler;
    imu::InertialMeasurement imu_interface(i2c_handler);
    types::GyroscopeSensitivity sensitivity = types::GyroscopeSensitivity::FINEST;
    types::GyroscopeSensitivity gyroscope_sensitivity_return = imu_interface.GetGyroscopeSensitivity();
    EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
  }

  TEST(imu, interface_set_accelerometer_sensitivity_finest){
    i2c::I2CHandler i2c_handler;
    imu::InertialMeasurement imu_interface(i2c_handler);
    types::AccelerometerSensitivity sensitivity = types::AccelerometerSensitivity::FINEST;
    imu_interface.SetAccelerometerSensitivity(sensitivity);
    types::AccelerometerSensitivity gyroscope_sensitivity_return = imu_interface.GetAccelerometerSensitivity();
    EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
  }

  TEST(imu, interface_set_accelerometer_sensitivity_finer){
    i2c::I2CHandler i2c_handler;
    imu::InertialMeasurement imu_interface(i2c_handler);
    types::AccelerometerSensitivity sensitivity = types::AccelerometerSensitivity::FINER;
    imu_interface.SetAccelerometerSensitivity(sensitivity);
    types::AccelerometerSensitivity gyroscope_sensitivity_return = imu_interface.GetAccelerometerSensitivity();
    EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
  }

  TEST(imu, interface_set_accelerometer_sensitivity_rougher){
    i2c::I2CHandler i2c_handler;
    imu::InertialMeasurement imu_interface(i2c_handler);
    types::AccelerometerSensitivity sensitivity = types::AccelerometerSensitivity::ROUGHER;
    imu_interface.SetAccelerometerSensitivity(sensitivity);
    types::AccelerometerSensitivity gyroscope_sensitivity_return = imu_interface.GetAccelerometerSensitivity();
    EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
  }

  TEST(imu, interface_set_accelerometer_sensitivity_roughest){
    i2c::I2CHandler i2c_handler;
    imu::InertialMeasurement imu_interface(i2c_handler);
    types::AccelerometerSensitivity sensitivity = types::AccelerometerSensitivity::ROUGHEST;
    imu_interface.SetAccelerometerSensitivity(sensitivity);
    types::AccelerometerSensitivity gyroscope_sensitivity_return = imu_interface.GetAccelerometerSensitivity();
    EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
  }

  TEST(imu, interface_get_accelerometer_sensitivity_default){
    i2c::I2CHandler i2c_handler;
    imu::InertialMeasurement imu_interface(i2c_handler);
    types::AccelerometerSensitivity sensitivity = types::AccelerometerSensitivity::FINEST;
    types::AccelerometerSensitivity gyroscope_sensitivity_return = imu_interface.GetAccelerometerSensitivity();
    EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
  }

  TEST(imu, interface_get_gyroscope){
    i2c::I2CHandler i2c_handler;
    imu::InertialMeasurement imu_interface(i2c_handler);
    types::EuclideanVector<float> expected_value{1.5, 2.5, 3.5};
    types::EuclideanVector<float> gyroscope_return = imu_interface.GetGyroscope();
    EXPECT_EQ(gyroscope_return.x, expected_value.x);
    EXPECT_EQ(gyroscope_return.y, expected_value.y);
    EXPECT_EQ(gyroscope_return.z, expected_value.z);
  }

  TEST(imu, interface_get_accelerometer){
    i2c::I2CHandler i2c_handler;
    imu::InertialMeasurement imu_interface(i2c_handler);
    types::EuclideanVector<float> expected_value{4.5, 5.5, 6.5};
    types::EuclideanVector<float> accelerometer_return = imu_interface.GetAccelerometer();
    EXPECT_EQ(accelerometer_return.x, expected_value.x);
    EXPECT_EQ(accelerometer_return.y, expected_value.y);
    EXPECT_EQ(accelerometer_return.z, expected_value.z);
  }

  TEST(imu, interface_get_magnetometer){
    i2c::I2CHandler i2c_handler;
    imu::InertialMeasurement imu_interface(i2c_handler);
    types::EuclideanVector<float> expected_value{7.5, 8.5, 9.5};
    types::EuclideanVector<float> magnetometer_return = imu_interface.GetMagnetometer();
    EXPECT_EQ(magnetometer_return.x, expected_value.x);
    EXPECT_EQ(magnetometer_return.y, expected_value.y);
    EXPECT_EQ(magnetometer_return.z, expected_value.z);
  }

  TEST(imu, interface_get_temperature){
    i2c::I2CHandler i2c_handler;
    imu::InertialMeasurement imu_interface(i2c_handler);
    int expected_value = 17;
    int temperature_return = imu_interface.GetTemperature();
    EXPECT_EQ(temperature_return, expected_value);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}