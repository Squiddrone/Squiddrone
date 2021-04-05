#include "sensor_with_sensitivity.hpp"
#include "byte.hpp"

namespace imu {

auto SensorWithSensitivity::Init(const std::uint8_t i2c_address) noexcept -> types::DriverStatus {
  if (GeneralSensor::Init(i2c_address) != types::DriverStatus::OK)
    return types::DriverStatus::HAL_ERROR;

  SetSensorValues(0, 0, 0);

  SendSensitivityRegisterData(sensitivity_);
  if (ImuConnectionFailed())
    return types::DriverStatus::HAL_ERROR;

  initialized_ = true;
  return types::DriverStatus::OK;
}

auto SensorWithSensitivity::SetSensitivity(const types::ImuSensitivity sensitivity) noexcept -> types::DriverStatus {
  if (!IsInitialized())
    return types::DriverStatus::HAL_ERROR;

  SendSensitivityRegisterData(sensitivity);

  if (ImuConnectionSuccessful())
    SaveNewSensitivity(sensitivity);

  return imu_status_;
}

auto SensorWithSensitivity::SaveNewSensitivity(const types::ImuSensitivity sensitivity) noexcept -> void {
  sensitivity_ = sensitivity;
}

auto SensorWithSensitivity::SendSensitivityRegisterData(const types::ImuSensitivity sensitivity) noexcept -> void {
  std::uint8_t new_config = GetConfigRegisterDataForSensitivity(sensitivity);
  WriteContentIntoRegister(CONFIG_REGISTER, new_config);
}

auto SensorWithSensitivity::GetConfigRegisterDataForSensitivity(const types::ImuSensitivity sensitivity) noexcept -> std::uint8_t {
  utilities::Byte config_data(ReadContentFromRegister(CONFIG_REGISTER, 1).at(0));

  if (sensitivity == types::ImuSensitivity::FINEST) {
    config_data.ClearBit(3);
    config_data.ClearBit(4);
  } else if (sensitivity == types::ImuSensitivity::FINER) {
    config_data.SetBit(3);
    config_data.ClearBit(4);
  } else if (sensitivity == types::ImuSensitivity::ROUGHER) {
    config_data.ClearBit(3);
    config_data.SetBit(4);
  } else if (sensitivity == types::ImuSensitivity::ROUGHEST) {
    config_data.SetBit(3);
    config_data.SetBit(4);
  }

  return config_data.Get();
}

auto SensorWithSensitivity::GetSensitivity(void) noexcept -> types::ImuSensitivity {
  return sensitivity_;
}

}  // namespace imu