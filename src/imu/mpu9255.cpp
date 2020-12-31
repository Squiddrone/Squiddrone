#include "mpu9255.hpp"

namespace imu {

auto Mpu9255::Init(void) noexcept -> types::DriverStatus {
  if (gyroscope_ == NULL) {
    gyroscope_ = std::make_unique<imu::Gyroscope>(i2c_handler_);
  }
  if (accelerometer_ == NULL) {
    accelerometer_ = std::make_unique<imu::Accelerometer>(i2c_handler_);
  }

  accelerometer_->Init(WHO_AM_I_MPU9255_ADDRESS);
  initialized_ = true;
  return gyroscope_->Init(WHO_AM_I_MPU9255_ADDRESS);
}

auto Mpu9255::Update(void) noexcept -> types::DriverStatus {
  if (!IsInitialized())
    return types::DriverStatus::HAL_ERROR;

  accelerometer_->Update();
  return gyroscope_->Update();
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

auto Mpu9255::GetGyroscope(void) noexcept -> types::EuclideanVector<std::int16_t> {
  if (!IsInitialized()) {
    return types::EuclideanVector<std::int16_t>{-1, -1, -1};
  }

  return gyroscope_->Get();
}

auto Mpu9255::GetAccelerometer(void) noexcept -> types::EuclideanVector<std::int16_t> {
  if (!IsInitialized()) {
    return types::EuclideanVector<std::int16_t>{-1, -1, -1};
  }

  return accelerometer_->Get();
}

auto Mpu9255::GetMagnetometer(void) noexcept -> types::EuclideanVector<std::int16_t> {
  types::EuclideanVector<std::int16_t> value{0, 0, 0};
  return value;
}

auto Mpu9255::GetTemperature(void) noexcept -> int {
  return 0;
}

auto Mpu9255::IsInitialized(void) noexcept -> bool {
  return initialized_;
}

auto Mpu9255::UnitTestSetGyroscope(std::unique_ptr<imu::GyroscopeInterface> gyroscope) -> void {
  gyroscope_ = std::move(gyroscope);
}

auto Mpu9255::UnitTestSetAccelerometer(std::unique_ptr<imu::AccelerometerInterface> accelerometer) -> void {
  accelerometer_ = std::move(accelerometer);
}

}  // namespace imu