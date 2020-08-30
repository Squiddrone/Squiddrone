#include "imu_sensor_with_sensitivity.hpp"

namespace imu {

auto InertialMeasurementSensorWithSensitivity::Init(std::uint8_t i2c_address) noexcept -> types::DriverStatus {
  SetI2CAdress(i2c_address);
  initialized_ = false;

  if (!Mpu9255Detected())
    return types::DriverStatus::HAL_ERROR;

  SetSensorValues(0, 0, 0);

  SendSensitivityRegisterData(sensitivity_);
  if (ImuConnectionFailed())
    return types::DriverStatus::HAL_ERROR;

  initialized_ = true;
  return types::DriverStatus::OK;
}

auto InertialMeasurementSensorWithSensitivity::SetSensitivity(types::ImuSensitivity sensitivity) noexcept -> types::DriverStatus {
  if (!IsInitialized()) {
    return types::DriverStatus::HAL_ERROR;
  }

  SendSensitivityRegisterData(sensitivity);

  if (ImuConnectionSuccessful()) {
    SaveNewSensitivity(sensitivity);
  }

  return imu_status_;
}

auto InertialMeasurementSensorWithSensitivity::SaveNewSensitivity(types::ImuSensitivity sensitivity) noexcept -> void {
  sensitivity_ = sensitivity;
}

auto InertialMeasurementSensorWithSensitivity::SendSensitivityRegisterData(types::ImuSensitivity sensitivity) noexcept -> void {
  std::uint8_t new_config = GetConfigRegisterDataForSensitivity(sensitivity);
  Write({CONFIG_REGISTER, new_config});
}

auto InertialMeasurementSensorWithSensitivity::GetConfigRegisterDataForSensitivity(types::ImuSensitivity sensitivity) noexcept -> std::uint8_t {
  std::uint8_t config_data = ReadContentFromRegister(CONFIG_REGISTER, 1).at(0);

  if (sensitivity == types::ImuSensitivity::FINEST) {
    config_data = ClearBit(config_data, 3);
    config_data = ClearBit(config_data, 4);
  } else if (sensitivity == types::ImuSensitivity::FINER) {
    config_data = SetBit(config_data, 3);
    config_data = ClearBit(config_data, 4);
  } else if (sensitivity == types::ImuSensitivity::ROUGHER) {
    config_data = ClearBit(config_data, 3);
    config_data = SetBit(config_data, 4);
  } else if (sensitivity == types::ImuSensitivity::ROUGHEST) {
    config_data = SetBit(config_data, 3);
    config_data = SetBit(config_data, 4);
  }

  return config_data;
}

auto InertialMeasurementSensorWithSensitivity::GetSensitivity(void) noexcept -> types::ImuSensitivity {
  return sensitivity_;
}

}  // namespace imu