#ifndef SRC_IMU_INTERFACE_HPP_
#define SRC_IMU_INTERFACE_HPP_

#include <utility>
#include "i2c_handler.hpp"
#include "basic_types.hpp"
#include "gyroscope_sensitivity.hpp"
#include "accelerometer_sensitivity.hpp"

namespace imu
{

  class InertialMeasurementInterface
  {
    public:
      InertialMeasurementInterface() = delete;
      virtual ~InertialMeasurementInterface() = default;
      explicit InertialMeasurementInterface(i2c::I2CHandler i2c_handler): i2c_handler_(i2c_handler){};
      virtual void SetGyroscopeSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept = 0;
      virtual types::GyroscopeSensitivity GetGyroscopeSensitivity(void) noexcept = 0;
      virtual void SetAccelerometerSensitivity(types::AccelerometerSensitivity accelerometer_sensitivity) noexcept = 0;
      virtual types::AccelerometerSensitivity GetAccelerometerSensitivity(void) noexcept = 0;
      virtual types::EuclideanVector<float> GetGyroscope(void) noexcept = 0;
      virtual types::EuclideanVector<float> GetAccelerometer(void) noexcept = 0;
      virtual types::EuclideanVector<float> GetMagnetometer(void) noexcept = 0;
      virtual int GetTemperature(void) noexcept = 0;
    protected:
      i2c::I2CHandler i2c_handler_;
  };

} // namespace imu

#endif