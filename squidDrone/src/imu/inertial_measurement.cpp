#include "inertial_measurement.hpp"

namespace imu
{

  void InertialMeasurement::SetGyroscopeSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept {
    generic_imu_->SetGyroscopeSensitivity(gyroscope_sensitivity);
  }

  auto InertialMeasurement::GetGyroscopeSensitivity(void) noexcept -> types::GyroscopeSensitivity {
    return generic_imu_->GetGyroscopeSensitivity();
  }

  void InertialMeasurement::SetAccelerometerSensitivity(types::AccelerometerSensitivity accelerometer_sensitivity) noexcept {
    generic_imu_->SetAccelerometerSensitivity(accelerometer_sensitivity);
  }

  auto InertialMeasurement::GetAccelerometerSensitivity(void) noexcept -> types::AccelerometerSensitivity {
    return generic_imu_->GetAccelerometerSensitivity();
  }

  auto InertialMeasurement::GetGyroscope(void) noexcept -> types::EuclideanVector<float> {
    return generic_imu_->GetGyroscope();
  }

  auto InertialMeasurement::GetAccelerometer(void) noexcept -> types::EuclideanVector<float> {
    return generic_imu_->GetAccelerometer();
  }

  auto InertialMeasurement::GetMagnetometer(void) noexcept -> types::EuclideanVector<float> {
    return generic_imu_->GetMagnetometer();
  }

  auto InertialMeasurement::GetTemperature(void) noexcept -> int {
    return generic_imu_->GetTemperature();
  }

} // namespace imu