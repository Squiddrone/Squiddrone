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
    public:
      GenericInertialMeasurementUnit() = delete;
      ~GenericInertialMeasurementUnit() = default;
      explicit GenericInertialMeasurementUnit(i2c::I2CHandler i2c_handler): i2c_handler_(i2c_handler){}
      void SetGyroscopeSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept
      {

      }

      types::GyroscopeSensitivity GetGyroscopeSensitivity(void) noexcept
      {
        return gyroscope_sensitivity;
      }

      void SetAccelerometerSensitivity(types::AccelerometerSensitivity accelerometer_sensitivity) noexcept
      {

      }
      
      types::AccelerometerSensitivity GetAccelerometerSensitivity(void) noexcept
      {
        return accelerometer_sensitivity;
      }

      types::EuclideanVector<float> GetGyroscope(void) noexcept
      {
        types::EuclideanVector<float> value{0, 0, 0};
      }

      types::EuclideanVector<float> GetAccelerometer(void) noexcept
      {
        types::EuclideanVector<float> value{0, 0, 0};
      }

      types::EuclideanVector<float> GetMagnetometer(void) noexcept
      {
        types::EuclideanVector<float> value{0, 0, 0};
      }

      int GetTemperature(void) noexcept
      {
        return 17;
      }
    protected:
      types::GyroscopeSensitivity gyroscope_sensitivity = types::GyroscopeSensitivity::FINEST;
      types::AccelerometerSensitivity accelerometer_sensitivity = types::AccelerometerSensitivity::FINEST;
      i2c::I2CHandler i2c_handler_;
  };

}

#endif