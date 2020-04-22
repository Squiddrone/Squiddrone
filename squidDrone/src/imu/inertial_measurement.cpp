#include "inertial_measurement.hpp"

namespace imu
{

  void InertialMeasurement::SetGyroscopeSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept {
    mpu9250_->SetGyroscopeSensitivity(gyroscope_sensitivity);
  }

  types::GyroscopeSensitivity InertialMeasurement::GetGyroscopeSensitivity(void) noexcept {
    return mpu9250_->GetGyroscopeSensitivity();
  }

  void InertialMeasurement::SetAccelerometerSensitivity(types::AccelerometerSensitivity accelerometer_sensitivity) noexcept {
    mpu9250_->SetAccelerometerSensitivity(accelerometer_sensitivity);
  }

  types::AccelerometerSensitivity InertialMeasurement::GetAccelerometerSensitivity(void) noexcept {
    return mpu9250_->GetAccelerometerSensitivity();
  }

  types::EuclideanVector<float> InertialMeasurement::GetGyroscope(void) noexcept {
    return mpu9250_->GetGyroscope();
  }

  types::EuclideanVector<float> InertialMeasurement::GetAccelerometer(void) noexcept {
    return mpu9250_->GetAccelerometer();
  }

  types::EuclideanVector<float> InertialMeasurement::GetMagnetometer(void) noexcept {
    return mpu9250_->GetMagnetometer();
  }

  int InertialMeasurement::GetTemperature(void) noexcept {
    return mpu9250_->GetTemperature();
  }

} // namespace imu