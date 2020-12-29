#include "inertial_measurement.hpp"

namespace imu {

auto InertialMeasurement::Init(void) noexcept -> types::DriverStatus {
  return imu_->Init();
}

void InertialMeasurement::SetGyroscopeSensitivity(types::ImuSensitivity gyroscope_sensitivity) noexcept {
  imu_->SetGyroscopeSensitivity(gyroscope_sensitivity);
}

auto InertialMeasurement::GetGyroscopeSensitivity(void) noexcept -> types::ImuSensitivity {
  return imu_->GetGyroscopeSensitivity();
}

void InertialMeasurement::SetAccelerometerSensitivity(types::ImuSensitivity accelerometer_sensitivity) noexcept {
  imu_->SetAccelerometerSensitivity(accelerometer_sensitivity);
}

auto InertialMeasurement::GetAccelerometerSensitivity(void) noexcept -> types::ImuSensitivity {
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

auto InertialMeasurement::UnitTestSetImuSeam(std::unique_ptr<imu::GenericInertialMeasurementUnit> imu) noexcept -> void {
  imu_ = std::move(imu);
}

}  // namespace imu