#include "mpu9255.hpp"

namespace imu {

auto Mpu9255::Init(void) noexcept -> types::DriverStatus {
  CreateSensorPointer();

  InitGyro();
  InitAccelerometer();
  InitTemperature();

  SetInitConfigMPU9255();

  InitMagnetometer();

  if (CheckIfAllSensorsAreOK()) {
    initialized_ = true;
    return types::DriverStatus::OK;
  }
  return types::DriverStatus::HAL_ERROR;
}

auto Mpu9255::CreateSensorPointer(void) noexcept -> void {
  if (gyroscope_ == NULL) {
    gyroscope_ = std::make_unique<imu::Gyroscope>(i2c_handler_);
  }
  if (accelerometer_ == NULL) {
    accelerometer_ = std::make_unique<imu::Accelerometer>(i2c_handler_);
  }
  if (magnetometer_ == NULL) {
    magnetometer_ = std::make_unique<imu::Magnetometer>(i2c_handler_);
  }
  if (temperature_ == NULL) {
    temperature_ = std::make_unique<imu::Temperature>(i2c_handler_);
  }
}

auto Mpu9255::SetInitConfigMPU9255(void) noexcept -> void {
  SetMPU9255Register(INT_PIN_CFG, 0x22);
  SetMPU9255Register(INT_ENABLE, 0x01);
}

auto Mpu9255::SetMPU9255Register(const std::uint8_t register_, const std::uint8_t register_value) noexcept -> void {
  i2c_handler_->Write(MPU9255_ADDRESS, {register_, register_value});
}

auto Mpu9255::Update(void) noexcept -> types::DriverStatus {
  if (!IsInitialized())
    return types::DriverStatus::HAL_ERROR;

  UpdateAllSensors();

  if (CheckIfAllSensorsAreOK()) {
    initialized_ = true;
    return types::DriverStatus::OK;
  }
  return types::DriverStatus::HAL_ERROR;
}

auto Mpu9255::SetGyroscopeSensitivity(const types::ImuSensitivity gyroscope_sensitivity) noexcept -> types::DriverStatus {
  if (!IsInitialized())
    return types::DriverStatus::HAL_ERROR;

  return gyroscope_->SetSensitivity(gyroscope_sensitivity);
}

auto Mpu9255::GetGyroscopeSensitivity(void) noexcept -> types::ImuSensitivity {
  return gyroscope_->GetSensitivity();
}

auto Mpu9255::SetAccelerometerSensitivity(const types::ImuSensitivity accelerometer_sensitivity) noexcept -> types::DriverStatus {
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
  if (!IsInitialized()) {
    return -1;
  }

  return temperature_->Get();
}

auto Mpu9255::IsInitialized(void) noexcept -> bool {
  return initialized_;
}

auto Mpu9255::InitGyro(void) noexcept -> void {
  gyroscope_status_ = gyroscope_->Init(MPU9255_ADDRESS);
}

auto Mpu9255::InitAccelerometer(void) noexcept -> void {
  accelerometer_status_ = accelerometer_->Init(MPU9255_ADDRESS);
}

auto Mpu9255::InitMagnetometer(void) noexcept -> void {
  magnetometer_status_ = magnetometer_->Init(MPU9255_ADDRESS);
}

auto Mpu9255::InitTemperature(void) noexcept -> void {
  temperature_status_ = temperature_->Init(MPU9255_ADDRESS);
}

auto Mpu9255::UpdateAllSensors(void) noexcept -> void {
  gyroscope_status_ = gyroscope_->Update();
  accelerometer_status_ = accelerometer_->Update();
  magnetometer_status_ = magnetometer_->Update();
  temperature_status_ = temperature_->Update();
}

auto Mpu9255::CheckIfAllSensorsAreOK(void) noexcept -> bool {
  if (gyroscope_status_ == types::DriverStatus::OK &&
      accelerometer_status_ == types::DriverStatus::OK &&
      magnetometer_status_ == types::DriverStatus::OK &&
      temperature_status_ == types::DriverStatus::OK) {
    return true;
  } else {
    return false;
  }
}

auto Mpu9255::UnitTestSetGyroscope(std::unique_ptr<imu::GyroscopeInterface> gyroscope) noexcept -> void {
  gyroscope_ = std::move(gyroscope);
}

auto Mpu9255::UnitTestSetAccelerometer(std::unique_ptr<imu::AccelerometerInterface> accelerometer) noexcept -> void {
  accelerometer_ = std::move(accelerometer);
}

auto Mpu9255::UnitTestSetMagnetometer(std::unique_ptr<imu::MagnetometerInterface> magnetometer) noexcept -> void {
  magnetometer_ = std::move(magnetometer);
}

auto Mpu9255::UnitTestSetTemperature(std::unique_ptr<imu::TemperatureInterface> temperature) noexcept -> void {
  temperature_ = std::move(temperature);
}

}  // namespace imu