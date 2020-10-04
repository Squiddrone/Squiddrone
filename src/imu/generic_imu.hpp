#ifndef SRC_GENERIC_IMU_HPP_
#define SRC_GENERIC_IMU_HPP_

#include <memory>
#include "basic_types.hpp"
#include "i2c.hpp"
#include "imu_sensitivity.hpp"

namespace imu {

class GenericInertialMeasurementUnit {
 public:
  GenericInertialMeasurementUnit() = delete;
  virtual ~GenericInertialMeasurementUnit() = default;
  explicit GenericInertialMeasurementUnit(std::unique_ptr<i2c::I2CInterface> i2c_handler) : i2c_handler_(std::move(i2c_handler)) {}
  virtual void SetGyroscopeSensitivity(types::ImuSensitivity gyroscope_sensitivity) noexcept = 0;
  virtual auto GetGyroscopeSensitivity(void) noexcept -> types::ImuSensitivity = 0;
  virtual void SetAccelerometerSensitivity(types::ImuSensitivity accelerometer_sensitivity) noexcept = 0;
  virtual auto GetAccelerometerSensitivity(void) noexcept -> types::ImuSensitivity = 0;
  virtual auto GetGyroscope(void) noexcept -> types::EuclideanVector<float> = 0;
  virtual auto GetAccelerometer(void) noexcept -> types::EuclideanVector<float> = 0;
  virtual auto GetMagnetometer(void) noexcept -> types::EuclideanVector<float> = 0;
  virtual auto GetTemperature(void) noexcept -> int = 0;

 protected:
  types::ImuSensitivity gyroscope_sensitivity_ = types::ImuSensitivity::FINEST;
  types::ImuSensitivity accelerometer_sensitivity_ = types::ImuSensitivity::FINEST;
  std::unique_ptr<i2c::I2CInterface> i2c_handler_;
};

}  // namespace imu

#endif