#ifndef SRC_MPU9255_HPP_
#define SRC_MPU9255_HPP_

#include "accelerometer.hpp"
#include "accelerometer_virtual_interface.hpp"
#include "generic_imu.hpp"
#include "gyroscope.hpp"
#include "gyroscope_virtual_interface.hpp"

namespace imu {

class Mpu9255 final : public GenericInertialMeasurementUnit {
 public:
  Mpu9255() = delete;
  virtual ~Mpu9255() = default;
  explicit Mpu9255(std::shared_ptr<i2c::I2CInterface> i2c_handler) : GenericInertialMeasurementUnit(i2c_handler) {}
  auto Init(void) noexcept -> types::DriverStatus override;
  auto Update(void) noexcept -> types::DriverStatus override;
  auto SetGyroscopeSensitivity(types::ImuSensitivity gyroscope_sensitivity) noexcept -> void override;
  auto GetGyroscopeSensitivity(void) noexcept -> types::ImuSensitivity override;
  auto SetAccelerometerSensitivity(types::ImuSensitivity accelerometer_sensitivity) noexcept -> void override;
  auto GetAccelerometerSensitivity(void) noexcept -> types::ImuSensitivity override;
  auto GetGyroscope(void) noexcept -> types::EuclideanVector<std::int16_t> override;
  auto GetAccelerometer(void) noexcept -> types::EuclideanVector<std::int16_t> override;
  auto GetMagnetometer(void) noexcept -> types::EuclideanVector<std::int16_t> override;
  auto GetTemperature(void) noexcept -> int override;

  auto UnitTestSetGyroscope(std::unique_ptr<imu::GyroscopeInterface> gyroscope) -> void;
  auto UnitTestSetAccelerometer(std::unique_ptr<imu::AccelerometerInterface> accelerometer) -> void;

 protected:
  auto IsInitialized(void) noexcept -> bool;
  auto CombineSensorResults(types::DriverStatus gyroscope_status, types::DriverStatus accelerometer_status) noexcept -> types::DriverStatus;

  bool initialized_ = false;
  std::unique_ptr<imu::GyroscopeInterface> gyroscope_ = NULL;
  std::unique_ptr<imu::AccelerometerInterface> accelerometer_ = NULL;
};

}  // namespace imu

#endif