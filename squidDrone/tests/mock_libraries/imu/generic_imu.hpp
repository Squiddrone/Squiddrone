#ifndef MOCK_GENERIC_IMU_HPP_
#define MOCK_GENERIC_IMU_HPP_

#include "i2c_handler.hpp"
#include "basic_types.hpp"
#include "gyroscope_sensitivity.hpp"
#include "accelerometer_sensitivity.hpp"

namespace imu
{

  /// Mocklibrary for generic IMU
  class GenericInertialMeasurementUnit
  {
      GenericInertialMeasurementUnit() = delete;
      ~GenericInertialMeasurementUnit() = default;
      explicit GenericInertialMeasurementUnit(i2c::I2CHandler i2c_handler): i2c_handler_(i2c_handler){}
      void SetGyroscopeSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept;
      types::GyroscopeSensitivity GetGyroscopeSensitivity(void) noexcept;
      void SetAccelerometerSensitivity(types::AccelerometerSensitivity accelerometer_sensitivity) noexcept;
      types::EuclideanVector<float> GetGyroscope(void) noexcept;
      types::EuclideanVector<float> GetAccelerometer(void) noexcept;
      types::EuclideanVector<float> GetMagnetometer(void) noexcept;
      int GetTemperature(void) noexcept;
    private:
      types::GyroscopeSensitivity gyroscope_sensitivity = types::GyroscopeSensitivity::FINEST;
      types::AccelerometerSensitivity accelerometer_sensitivity = types::AccelerometerSensitivity::FINEST;
      i2c::I2CHandler i2c_handler_;
  };

}

#endif