#include "imu_general.hpp"

namespace imu {

auto GeneralSensor::Init(const std::uint8_t i2c_address) noexcept -> types::DriverStatus {
  SetI2CAdress(i2c_address);
  initialized_ = false;

  if (!IsHardwareConnected())
    return types::DriverStatus::HAL_ERROR;

  return types::DriverStatus::OK;
}

auto GeneralSensor::IsHardwareConnected(void) -> bool {
  if (i2c_address_ == imu::MPU9255_ADDRESS)
    return Mpu9255Detected();

  if (i2c_address_ == imu::AK8963_ADDRESS)
    return AK8963Detected();

  return false;
}

auto GeneralSensor::GetRawValues(void) noexcept -> types::DriverStatus {
  if (!IsInitialized())
    return types::DriverStatus::HAL_ERROR;

  raw_values_ = ReadContentFromRegister(sensor_data_register, register_data_length_in_bytes);

  if (ImuConnectionSuccessful())
    return types::DriverStatus::OK;

  return types::DriverStatus::HAL_ERROR;
}

auto GeneralSensor::Mpu9255Detected(void) noexcept -> bool {
  return CheckI2CDevice(WHO_AM_I_MPU9255_REGISTER, WHO_AM_I_MPU9255_VALUE);
}

auto GeneralSensor::AK8963Detected(void) noexcept -> bool {
  return CheckI2CDevice(WHO_AM_I_AK8963_REGISTER, WHO_AM_I_AK8963_VALUE);
}

auto GeneralSensor::CheckI2CDevice(const std::uint8_t register_, const std::uint8_t value) noexcept -> bool {
  bool value_is_correct = false;

  std::vector<uint8_t> register_value = ReadContentFromRegister(register_, 1);
  if (ImuConnectionSuccessful()) {
    if (register_value.at(0) == value) {
      value_is_correct = true;
    }
  }

  return value_is_correct;
}

auto GeneralSensor::ReadContentFromRegister(const std::uint8_t read_from_register, const std::uint16_t byte_size) noexcept -> std::vector<std::uint8_t> {
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

auto GeneralSensor::WriteContentIntoRegister(const std::uint8_t write_into_register, const std::uint8_t register_content) noexcept -> void {
  imu_status_ = i2c_handler_->Write(i2c_address_, {write_into_register, register_content});
}

auto GeneralSensor::ImuConnectionSuccessful(void) noexcept -> bool {
  return imu_status_ == types::DriverStatus::OK;
}

auto GeneralSensor::ImuConnectionFailed(void) noexcept -> bool {
  return !ImuConnectionSuccessful();
}

auto GeneralSensor::SetI2CAdress(std::uint8_t i2c_address) noexcept -> void {
  i2c_address_ = i2c_address;
}

auto GeneralSensor::ConvertUint8BytesIntoInt16SensorValue(const std::uint8_t first_byte, const std::uint8_t second_byte) noexcept -> std::int16_t {
  return static_cast<std::int16_t>(first_byte << 8 | second_byte);
}

auto GeneralSensor::IsInitialized(void) noexcept -> bool {
  return initialized_;
}

}  // namespace imu