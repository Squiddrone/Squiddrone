#ifndef SRC_MPU9250_HPP_
#define SRC_MPU9250_HPP_

#include "generic_imu.hpp"

namespace imu {

  class Mpu9250 final : public GenericInertialMeasurementUnit {
    public:
      Mpu9250() = delete;
      ~Mpu9250() = default;
      explicit Mpu9250(std::unique_ptr<i2c::I2CHandler> i2c_handler): GenericInertialMeasurementUnit(std::move(i2c_handler)){}
      void SetGyroscopeSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept override;
      auto GetGyroscopeSensitivity(void) noexcept -> types::GyroscopeSensitivity override;
      void SetAccelerometerSensitivity(types::AccelerometerSensitivity accelerometer_sensitivity) noexcept override;
      auto GetAccelerometerSensitivity(void) noexcept -> types::AccelerometerSensitivity override;
      auto GetGyroscope(void) noexcept -> types::EuclideanVector<float> override;
      auto GetAccelerometer(void) noexcept -> types::EuclideanVector<float> override;
      auto GetMagnetometer(void) noexcept -> types::EuclideanVector<float> override;
      auto GetTemperature(void) noexcept -> int override;
  };

} // namespace imu

#endif