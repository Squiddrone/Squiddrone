#ifndef SRC_GENERIC_IMU_HPP_
#define SRC_GENERIC_IMU_HPP_

#include <memory>
#include "basic_types.hpp"
#include "gyroscope.hpp"
#include "gyroscope_virtual_interface.hpp"
#include "i2c.hpp"
#include "imu_sensitivity.hpp"

namespace imu {

class GenericInertialMeasurementUnit {
 public:
  GenericInertialMeasurementUnit() = delete;
  virtual ~GenericInertialMeasurementUnit() = default;
  explicit GenericInertialMeasurementUnit(std::unique_ptr<i2c::I2CInterface> i2c_handler) : i2c_handler_(std::move(i2c_handler)) {}
  virtual auto Init(void) noexcept -> types::DriverStatus = 0;
  virtual auto SetGyroscopeSensitivity(types::ImuSensitivity gyroscope_sensitivity) noexcept -> void = 0;
  virtual auto GetGyroscopeSensitivity(void) noexcept -> types::ImuSensitivity = 0;
  virtual auto SetAccelerometerSensitivity(types::ImuSensitivity accelerometer_sensitivity) noexcept -> void = 0;
  virtual auto GetAccelerometerSensitivity(void) noexcept -> types::ImuSensitivity = 0;
  virtual auto GetGyroscope(void) noexcept -> types::EuclideanVector<float> = 0;
  virtual auto GetAccelerometer(void) noexcept -> types::EuclideanVector<float> = 0;
  virtual auto GetMagnetometer(void) noexcept -> types::EuclideanVector<float> = 0;
  virtual auto GetTemperature(void) noexcept -> int = 0;

 protected:
  types::ImuSensitivity gyroscope_sensitivity_ = types::ImuSensitivity::FINEST;
  types::ImuSensitivity accelerometer_sensitivity_ = types::ImuSensitivity::FINEST;
  std::unique_ptr<i2c::I2CInterface> i2c_handler_;
  std::unique_ptr<imu::GyroscopeInterface> gyroscope_ = NULL;
};

}  // namespace imu

#endif