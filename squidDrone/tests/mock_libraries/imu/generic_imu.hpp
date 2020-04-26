#ifndef SRC_GENERIC_IMU_HPP_
#define SRC_GENERIC_IMU_HPP_

#include <memory>
#include "i2c_handler.hpp"
#include "basic_types.hpp"
#include "gyroscope_sensitivity.hpp"
#include "accelerometer_sensitivity.hpp"

namespace imu {

  class GenericInertialMeasurementUnit {
    public:
      GenericInertialMeasurementUnit() = delete;
      virtual ~GenericInertialMeasurementUnit() = default;
      explicit GenericInertialMeasurementUnit(std::unique_ptr<i2c::I2CHandler> i2c_handler): i2c_handler_(std::move(i2c_handler)){}
      virtual void SetGyroscopeSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept = 0;
      virtual auto GetGyroscopeSensitivity(void) noexcept -> types::GyroscopeSensitivity = 0;
      virtual void SetAccelerometerSensitivity(types::AccelerometerSensitivity accelerometer_sensitivity) noexcept = 0;
      virtual auto GetAccelerometerSensitivity(void) noexcept -> types::AccelerometerSensitivity = 0;
      virtual auto GetGyroscope(void) noexcept -> types::EuclideanVector<float> = 0;
      virtual auto GetAccelerometer(void) noexcept -> types::EuclideanVector<float> = 0;
      virtual auto GetMagnetometer(void) noexcept -> types::EuclideanVector<float> = 0;
      virtual auto GetTemperature(void) noexcept -> int = 0;
    protected:
      types::GyroscopeSensitivity gyroscope_sensitivity_ = types::GyroscopeSensitivity::FINEST;
      types::AccelerometerSensitivity accelerometer_sensitivity_ = types::AccelerometerSensitivity::FINEST;
      std::unique_ptr<i2c::I2CHandler> i2c_handler_;
  };

}

#endif