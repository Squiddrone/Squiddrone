#include "mpu9255.hpp"

namespace imu {

auto Mpu9255::Init(void) noexcept -> types::DriverStatus {
  if (gyroscope_ == NULL) {
    gyroscope_ = std::make_unique<imu::Gyroscope>(i2c_handler_);
  }
  if (accelerometer_ == NULL) {
    accelerometer_ = std::make_unique<imu::Accelerometer>(i2c_handler_);
  }
  if (magnetometer_ == NULL) {
    magnetometer_ = std::make_unique<imu::Magnetometer>(i2c_handler_);
  }

  auto gyro_init = gyroscope_->Init(WHO_AM_I_MPU9255_ADDRESS);
  auto accel_init = accelerometer_->Init(WHO_AM_I_MPU9255_ADDRESS);

  SetInitConfig();

  auto magneto_init = magnetometer_->Init(WHO_AM_I_AK8963_ADDRESS);
  if (AllSensorsAreOK(gyro_init, accel_init, magneto_init)) {
    initialized_ = true;
    return types::DriverStatus::OK;
  }
  return types::DriverStatus::HAL_ERROR;
}

auto Mpu9255::SetInitConfig(void) -> void {
  i2c_handler_->Write(WHO_AM_I_MPU9255_ADDRESS, {INT_PIN_CFG, 0x22});
  i2c_handler_->Write(WHO_AM_I_MPU9255_ADDRESS, {INT_ENABLE, 0x01});
}

auto Mpu9255::Update(void) noexcept -> types::DriverStatus {
  if (!IsInitialized())
    return types::DriverStatus::HAL_ERROR;

  if (AllSensorsAreOK(gyroscope_->Update(), accelerometer_->Update(), magnetometer_->Update())) {
    initialized_ = true;
    return types::DriverStatus::OK;
  }
  return types::DriverStatus::HAL_ERROR;
}

auto Mpu9255::SetGyroscopeSensitivity(types::ImuSensitivity gyroscope_sensitivity) noexcept -> types::DriverStatus {
  if (!IsInitialized())
    return types::DriverStatus::HAL_ERROR;

  return gyroscope_->SetSensitivity(gyroscope_sensitivity);
}

auto Mpu9255::GetGyroscopeSensitivity(void) noexcept -> types::ImuSensitivity {
  return gyroscope_->GetSensitivity();
}

auto Mpu9255::SetAccelerometerSensitivity(types::ImuSensitivity accelerometer_sensitivity) noexcept -> types::DriverStatus {
  if (!IsInitialized())
    return types::DriverStatus::HAL_ERROR;

  return accelerometer_->SetSensitivity(accelerometer_sensitivity);
}

auto Mpu9255::GetAccelerometerSensitivity(void) noexcept -> types::ImuSensitivity {
  return accelerometer_->GetSensitivity();
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
  if (!IsInitialized()) {
    return types::EuclideanVector<std::int16_t>{-1, -1, -1};
  }

  return magnetometer_->Get();
}

auto Mpu9255::GetTemperature(void) noexcept -> int {
  return 0;
}

auto Mpu9255::IsInitialized(void) noexcept -> bool {
  return initialized_;
}

auto Mpu9255::AllSensorsAreOK(types::DriverStatus gyroscope_status,
                              types::DriverStatus accelerometer_status,
                              types::DriverStatus magnetometer_status) noexcept -> bool {
  if (gyroscope_status == types::DriverStatus::OK &&
      accelerometer_status == types::DriverStatus::OK &&
      magnetometer_status == types::DriverStatus::OK) {
    return true;
  } else {
    return false;
  }
}

auto Mpu9255::UnitTestSetGyroscope(std::unique_ptr<imu::GyroscopeInterface> gyroscope) -> void {
  gyroscope_ = std::move(gyroscope);
}

auto Mpu9255::UnitTestSetAccelerometer(std::unique_ptr<imu::AccelerometerInterface> accelerometer) -> void {
  accelerometer_ = std::move(accelerometer);
}

auto Mpu9255::UnitTestSetMagnetometer(std::unique_ptr<imu::MagnetometerInterface> magnetometer) -> void {
  magnetometer_ = std::move(magnetometer);
}

}  // namespace imu