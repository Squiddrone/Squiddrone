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
      explicit InertialMeasurementInterface(i2c::I2CHandler i2c_handler): i2c_handler_(i2c_handler){}
      virtual void SetGyroscopeSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept;
      virtual types::GyroscopeSensitivity GetGyroscopeSensitivity(void) noexcept;
      virtual void SetAccelerometerSensitivity(types::AccelerometerSensitivity accelerometer_sensitivity) noexcept;
      virtual types::AccelerometerSensitivity GetAccelerometerSensitivity(void) noexcept;
      virtual types::EuclideanVector<float> GetGyroscope(void) noexcept;
      virtual types::EuclideanVector<float> GetAccelerometer(void) noexcept;
      virtual types::EuclideanVector<float> GetMagnetometer(void) noexcept;
      virtual int GetTemperature(void) noexcept;
    protected:
      i2c::I2CHandler i2c_handler_;
  };

} // namespace imu

#endif