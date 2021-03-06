#ifndef SRC_MPU9255_HPP_
#define SRC_MPU9255_HPP_

#include "generic_imu.hpp"

namespace imu {

class Mpu9255 final : public GenericInertialMeasurementUnit {
 public:
  Mpu9255() = delete;
  virtual ~Mpu9255() = default;
  explicit Mpu9255(std::unique_ptr<i2c::I2CInterface> i2c_handler) : GenericInertialMeasurementUnit(std::move(i2c_handler)) {}
  void SetGyroscopeSensitivity(types::ImuSensitivity gyroscope_sensitivity) noexcept override;
  auto GetGyroscopeSensitivity(void) noexcept -> types::ImuSensitivity override;
  void SetAccelerometerSensitivity(types::ImuSensitivity accelerometer_sensitivity) noexcept override;
  auto GetAccelerometerSensitivity(void) noexcept -> types::ImuSensitivity override;
  auto GetGyroscope(void) noexcept -> types::EuclideanVector<float> override;
  auto GetAccelerometer(void) noexcept -> types::EuclideanVector<float> override;
  auto GetMagnetometer(void) noexcept -> types::EuclideanVector<float> override;
  auto GetTemperature(void) noexcept -> int override;
};

}  // namespace imu

#endif