#ifndef SRC_IMU_INTERFACE_HPP_
#define SRC_IMU_INTERFACE_HPP_

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
      ~InertialMeasurementInterface() = default;
      explicit InertialMeasurementInterface(i2c::I2CHandler i2c_handler): i2c_handler_(i2c_handler){}
      void SetGyroscopeSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept;
      types::GyroscopeSensitivity GetGyroscopeSensitivity(void) noexcept;
      void SetAccelerometerSensitivity(types::AccelerometerSensitivity accelerometer_sensitivity) noexcept;
      types::EuclideanVector<float> GetGyroscope(void) noexcept;
      types::EuclideanVector<float> GetAccelerometer(void) noexcept;
      types::EuclideanVector<float> GetMagnetometer(void) noexcept;
      int GetTemperature(void) noexcept;
    private:
      i2c::I2CHandler i2c_handler_;
  };

} // namespace imu

#endif