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
  std::uint8_t full_scale_select = 0;

  if (sensitivity == types::ImuSensitivity::FINEST) {
    full_scale_select = imu::ImuSensitivityFSSelect::IMU_FS_FINEST;
  } else if (sensitivity == types::ImuSensitivity::FINER) {
    full_scale_select = imu::ImuSensitivityFSSelect::IMU_FS_FINER;
  } else if (sensitivity == types::ImuSensitivity::ROUGHER) {
    full_scale_select = imu::ImuSensitivityFSSelect::IMU_FS_ROUGHER;
  } else if (sensitivity == types::ImuSensitivity::ROUGHEST) {
    full_scale_select = imu::ImuSensitivityFSSelect::IMU_FS_ROUGHEST;
  }

  std::vector<uint8_t> config_data;
  config_data = ReadContentFromRegister(CONFIG_REGISTER, 1);

  return static_cast<std::uint8_t>(config_data.at(0) & (0b11100111 | (full_scale_select << 3)));
}

auto InertialMeasurementSensorWithSensitivity::GetSensitivity(void) noexcept -> types::ImuSensitivity {
  return sensitivity_;
}

}  // namespace imu