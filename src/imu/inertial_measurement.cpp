#include "inertial_measurement.hpp"

namespace imu {

void InertialMeasurement::SetGyroscopeSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept {
  imu_->SetGyroscopeSensitivity(gyroscope_sensitivity);
}

auto InertialMeasurement::GetGyroscopeSensitivity(void) noexcept -> types::GyroscopeSensitivity {
  return imu_->GetGyroscopeSensitivity();
}

void InertialMeasurement::SetAccelerometerSensitivity(types::AccelerometerSensitivity accelerometer_sensitivity) noexcept {
  imu_->SetAccelerometerSensitivity(accelerometer_sensitivity);
}

auto InertialMeasurement::GetAccelerometerSensitivity(void) noexcept -> types::AccelerometerSensitivity {
  return imu_->GetAccelerometerSensitivity();
}

auto InertialMeasurement::GetGyroscope(void) noexcept -> types::EuclideanVector<float> {
  return imu_->GetGyroscope();
}

auto InertialMeasurement::GetAccelerometer(void) noexcept -> types::EuclideanVector<float> {
  return imu_->GetAccelerometer();
}

auto InertialMeasurement::GetMagnetometer(void) noexcept -> types::EuclideanVector<float> {
  return imu_->GetMagnetometer();
}

auto InertialMeasurement::GetTemperature(void) noexcept -> int {
  return imu_->GetTemperature();
}

}  // namespace imu