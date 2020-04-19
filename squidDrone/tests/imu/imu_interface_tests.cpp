#include "gtest/gtest.h"
#include "i2c_handler.hpp"
#include "inertial_measurement.hpp"

namespace{

  class ImuInterfaceTests: public ::testing::Test{
  protected:
    virtual void SetUp(){
      std::unique_ptr<i2c::I2CHandler> i2c_handler_ = std::make_unique<i2c::I2CHandler>();
      unit_under_test_ = std::make_unique<imu::InertialMeasurement>(std::move(i2c_handler_));
    }

    std::unique_ptr<i2c::I2CHandler> i2c_handler_;
    std::unique_ptr<imu::InertialMeasurement> unit_under_test_;
  };

  TEST_F(ImuInterfaceTests, interface_set_gyroscope_sensitivity_finest){
    types::GyroscopeSensitivity sensitivity = types::GyroscopeSensitivity::FINEST;
    unit_under_test_->SetGyroscopeSensitivity(sensitivity);
    types::GyroscopeSensitivity gyroscope_sensitivity_return = unit_under_test_->GetGyroscopeSensitivity();
    EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
  }

  TEST_F(ImuInterfaceTests, interface_set_gyroscope_sensitivity_finer){
    types::GyroscopeSensitivity sensitivity = types::GyroscopeSensitivity::FINER;
    unit_under_test_->SetGyroscopeSensitivity(sensitivity);
    types::GyroscopeSensitivity gyroscope_sensitivity_return = unit_under_test_->GetGyroscopeSensitivity();
    EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
  }

  TEST_F(ImuInterfaceTests, interface_set_gyroscope_sensitivity_rougher){
    types::GyroscopeSensitivity sensitivity = types::GyroscopeSensitivity::ROUGHER;
    unit_under_test_->SetGyroscopeSensitivity(sensitivity);
    types::GyroscopeSensitivity gyroscope_sensitivity_return = unit_under_test_->GetGyroscopeSensitivity();
    EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
  }

  TEST_F(ImuInterfaceTests, interface_set_gyroscope_sensitivity_roughest){
    types::GyroscopeSensitivity sensitivity = types::GyroscopeSensitivity::ROUGHEST;
    unit_under_test_->SetGyroscopeSensitivity(sensitivity);
    types::GyroscopeSensitivity gyroscope_sensitivity_return = unit_under_test_->GetGyroscopeSensitivity();
    EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
  }

  TEST_F(ImuInterfaceTests, interface_get_gyroscope_sensitivity_default){
    types::GyroscopeSensitivity sensitivity = types::GyroscopeSensitivity::FINEST;
    types::GyroscopeSensitivity gyroscope_sensitivity_return = unit_under_test_->GetGyroscopeSensitivity();
    EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
  }

  TEST_F(ImuInterfaceTests, interface_set_accelerometer_sensitivity_finest){
    types::AccelerometerSensitivity sensitivity = types::AccelerometerSensitivity::FINEST;
    unit_under_test_->SetAccelerometerSensitivity(sensitivity);
    types::AccelerometerSensitivity gyroscope_sensitivity_return = unit_under_test_->GetAccelerometerSensitivity();
    EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
  }

  TEST_F(ImuInterfaceTests, interface_set_accelerometer_sensitivity_finer){
    types::AccelerometerSensitivity sensitivity = types::AccelerometerSensitivity::FINER;
    unit_under_test_->SetAccelerometerSensitivity(sensitivity);
    types::AccelerometerSensitivity gyroscope_sensitivity_return = unit_under_test_->GetAccelerometerSensitivity();
    EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
  }

  TEST_F(ImuInterfaceTests, interface_set_accelerometer_sensitivity_rougher){
    types::AccelerometerSensitivity sensitivity = types::AccelerometerSensitivity::ROUGHER;
    unit_under_test_->SetAccelerometerSensitivity(sensitivity);
    types::AccelerometerSensitivity gyroscope_sensitivity_return = unit_under_test_->GetAccelerometerSensitivity();
    EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
  }

  TEST_F(ImuInterfaceTests, interface_set_accelerometer_sensitivity_roughest){
    types::AccelerometerSensitivity sensitivity = types::AccelerometerSensitivity::ROUGHEST;
    unit_under_test_->SetAccelerometerSensitivity(sensitivity);
    types::AccelerometerSensitivity gyroscope_sensitivity_return = unit_under_test_->GetAccelerometerSensitivity();
    EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
  }

  TEST_F(ImuInterfaceTests, interface_get_accelerometer_sensitivity_default){
    types::AccelerometerSensitivity sensitivity = types::AccelerometerSensitivity::FINEST;
    types::AccelerometerSensitivity gyroscope_sensitivity_return = unit_under_test_->GetAccelerometerSensitivity();
    EXPECT_EQ(gyroscope_sensitivity_return, sensitivity);
  }

  TEST_F(ImuInterfaceTests, interface_get_gyroscope){
    types::EuclideanVector<float> expected_value{1.5, 2.5, 3.5};
    types::EuclideanVector<float> gyroscope_return = unit_under_test_->GetGyroscope();
    EXPECT_EQ(gyroscope_return.x, expected_value.x);
    EXPECT_EQ(gyroscope_return.y, expected_value.y);
    EXPECT_EQ(gyroscope_return.z, expected_value.z);
  }

  TEST_F(ImuInterfaceTests, interface_get_accelerometer){
    types::EuclideanVector<float> expected_value{4.5, 5.5, 6.5};
    types::EuclideanVector<float> accelerometer_return = unit_under_test_->GetAccelerometer();
    EXPECT_EQ(accelerometer_return.x, expected_value.x);
    EXPECT_EQ(accelerometer_return.y, expected_value.y);
    EXPECT_EQ(accelerometer_return.z, expected_value.z);
  }

  TEST_F(ImuInterfaceTests, interface_get_magnetometer){
    types::EuclideanVector<float> expected_value{7.5, 8.5, 9.5};
    types::EuclideanVector<float> magnetometer_return = unit_under_test_->GetMagnetometer();
    EXPECT_EQ(magnetometer_return.x, expected_value.x);
    EXPECT_EQ(magnetometer_return.y, expected_value.y);
    EXPECT_EQ(magnetometer_return.z, expected_value.z);
  }

  TEST_F(ImuInterfaceTests, interface_get_temperature){
    int expected_value = 17;
    int temperature_return = unit_under_test_->GetTemperature();
    EXPECT_EQ(temperature_return, expected_value);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}