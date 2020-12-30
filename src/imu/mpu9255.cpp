#include "mpu9255.hpp"

namespace imu {

auto Mpu9255::Init(void) noexcept -> types::DriverStatus {
  if (gyroscope_ == NULL) {
    gyroscope_ = std::make_unique<imu::Gyroscope>(std::move(i2c_handler_));
  }

  return gyroscope_->Init(WHO_AM_I_MPU9255_ADDRESS);
}

auto Mpu9255::SetGyroscopeSensitivity(types::ImuSensitivity gyroscope_sensitivity) noexcept -> void {
  gyroscope_sensitivity_ = gyroscope_sensitivity;
}

auto Mpu9255::GetGyroscopeSensitivity(void) noexcept -> types::ImuSensitivity {
  return gyroscope_sensitivity_;
}

auto Mpu9255::SetAccelerometerSensitivity(types::ImuSensitivity accelerometer_sensitivity) noexcept -> void {
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

auto Mpu9255::UnitTestSetGyroscope(std::unique_ptr<imu::GyroscopeInterface> gyroscope) -> void {
  gyroscope_ = std::move(gyroscope);
}

}  // namespace imu