#include "imu_sensor_general.hpp"

namespace imu {

auto InertialMeasurementSensor::Init(const std::uint8_t i2c_address) noexcept -> types::DriverStatus {
  SetI2CAdress(i2c_address);
  initialized_ = false;

  if (!Mpu9255Detected() || !AK8963Detected())
    return types::DriverStatus::HAL_ERROR;

  return types::DriverStatus::OK;
}

auto InertialMeasurementSensor::GetRawValues(void) noexcept -> types::DriverStatus {
  if (!IsInitialized())
    return types::DriverStatus::HAL_ERROR;

  raw_values_ = ReadContentFromRegister(SENSOR_DATA_REGISTER, REGISTER_DATA_LENGTH_IN_BYTES);

  if (ImuConnectionSuccessful()) {
    return types::DriverStatus::OK;
  }

  return types::DriverStatus::HAL_ERROR;
}

auto InertialMeasurementSensor::Mpu9255Detected(void) noexcept -> bool {
  bool who_am_i_correct = false;

  std::vector<uint8_t> who_am_i_register_value = ReadContentFromRegister(WHO_AM_I_MPU9255_REGISTER, 1);
  if (ImuConnectionSuccessful()) {
    if (who_am_i_register_value.at(0) == WHO_AM_I_MPU9255_VALUE) {
      who_am_i_correct = true;
    }
  }

  return who_am_i_correct;
}

auto InertialMeasurementSensor::AK8963Detected(void) noexcept -> bool {
  bool who_am_i_correct = false;

  std::vector<uint8_t> who_am_i_register_value = ReadContentFromRegister(WHO_AM_I_AK8963_REGISTER, 1);
  if (ImuConnectionSuccessful()) {
    if (who_am_i_register_value.at(0) == WHO_AM_I_AK8963_VALUE) {
      who_am_i_correct = true;
    }
  }

  return who_am_i_correct;
}

auto InertialMeasurementSensor::ReadContentFromRegister(const std::uint8_t read_from_register, const std::uint16_t byte_size) noexcept -> std::vector<std::uint8_t> {
  types::DriverStatus i2c_status;
  std::vector<uint8_t> content_of_register;

  std::tie(i2c_status, content_of_register) = i2c_handler_->ReadContentFromRegister(i2c_address_, read_from_register, byte_size);
  if (i2c_status == types::DriverStatus::OK && content_of_register.size() == byte_size) {
    imu_status_ = types::DriverStatus::OK;
  } else {
    imu_status_ = types::DriverStatus::HAL_ERROR;
  }

  return content_of_register;
}

auto InertialMeasurementSensor::WriteContentIntoRegister(const std::uint8_t write_into_register, const std::uint8_t register_content) noexcept -> void {
  imu_status_ = i2c_handler_->Write(i2c_address_, {write_into_register, register_content});
}

auto InertialMeasurementSensor::ImuConnectionSuccessful(void) noexcept -> bool {
  return imu_status_ == types::DriverStatus::OK;
}

auto InertialMeasurementSensor::ImuConnectionFailed(void) noexcept -> bool {
  return !ImuConnectionSuccessful();
}

auto InertialMeasurementSensor::SetI2CAdress(std::uint8_t i2c_address) noexcept -> void {
  i2c_address_ = i2c_address;
}

auto InertialMeasurementSensor::ConvertUint8BytesIntoInt16SensorValue(const std::uint8_t first_byte, const std::uint8_t second_byte) noexcept -> std::int16_t {
  return static_cast<std::int16_t>(first_byte << 8 | second_byte);
}

auto InertialMeasurementSensor::IsInitialized(void) noexcept -> bool {
  return initialized_;
}

}  // namespace imu