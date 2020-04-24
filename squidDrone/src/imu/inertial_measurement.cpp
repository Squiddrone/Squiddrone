#include "inertial_measurement.hpp"

namespace imu
{

  void InertialMeasurement::SetGyroscopeSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept {
    mpu9250_->SetGyroscopeSensitivity(gyroscope_sensitivity);
  }

  auto InertialMeasurement::GetGyroscopeSensitivity(void) noexcept -> types::GyroscopeSensitivity {
    return mpu9250_->GetGyroscopeSensitivity();
  }

  void InertialMeasurement::SetAccelerometerSensitivity(types::AccelerometerSensitivity accelerometer_sensitivity) noexcept {
    mpu9250_->SetAccelerometerSensitivity(accelerometer_sensitivity);
  }

  auto InertialMeasurement::GetAccelerometerSensitivity(void) noexcept -> types::AccelerometerSensitivity {
    return mpu9250_->GetAccelerometerSensitivity();
  }

  auto InertialMeasurement::GetGyroscope(void) noexcept -> types::EuclideanVector<float> {
    return mpu9250_->GetGyroscope();
  }

  auto InertialMeasurement::GetAccelerometer(void) noexcept -> types::EuclideanVector<float> {
    return mpu9250_->GetAccelerometer();
  }

  auto InertialMeasurement::GetMagnetometer(void) noexcept -> types::EuclideanVector<float> {
    return mpu9250_->GetMagnetometer();
  }

  auto InertialMeasurement::GetTemperature(void) noexcept -> int {
    return mpu9250_->GetTemperature();
  }

} // namespace imu