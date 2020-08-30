#include "mpu9255.hpp"

namespace imu {

void Mpu9255::SetGyroscopeSensitivity(types::ImuSensitivity gyroscope_sensitivity) noexcept {
  gyroscope_sensitivity_ = gyroscope_sensitivity;
}

auto Mpu9255::GetGyroscopeSensitivity(void) noexcept -> types::ImuSensitivity {
  return gyroscope_sensitivity_;
}

void Mpu9255::SetAccelerometerSensitivity(types::ImuSensitivity accelerometer_sensitivity) noexcept {
  accelerometer_sensitivity_ = accelerometer_sensitivity;
}

auto Mpu9255::GetAccelerometerSensitivity(void) noexcept -> types::ImuSensitivity {
  return accelerometer_sensitivity_;
}

auto Mpu9255::GetGyroscope(void) noexcept -> types::EuclideanVector<float> {
  types::EuclideanVector<float> value{0, 0, 0};
  return value;
}

auto Mpu9255::GetAccelerometer(void) noexcept -> types::EuclideanVector<float> {
  types::EuclideanVector<float> value{0, 0, 0};
  return value;
}

auto Mpu9255::GetMagnetometer(void) noexcept -> types::EuclideanVector<float> {
  types::EuclideanVector<float> value{0, 0, 0};
  return value;
}

auto Mpu9255::GetTemperature(void) noexcept -> int {
  return 0;
}

}  // namespace imu