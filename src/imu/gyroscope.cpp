#include "gyroscope.hpp"

namespace imu {

auto Gyroscope::Init(std::uint8_t i2c_address) noexcept -> types::DriverStatus {
  SetI2CAdress(i2c_address);
  initialized_ = false;

  if (!Mpu9255Detected()) {
    return types::DriverStatus::HAL_ERROR;
  }

  SetSensorValues(0, 0, 0);

  SendSensitivityRegisterData(sensitivity_);
  if (ImuConnectionFailed()) {
    return types::DriverStatus::HAL_ERROR;
  }

  initialized_ = true;
  return types::DriverStatus::OK;
}

auto Gyroscope::Update(void) noexcept -> types::DriverStatus {
  if (!IsInitialized()) {
    return types::DriverStatus::HAL_ERROR;
  }

  std::vector<uint8_t> measurement_values;
  measurement_values = ReadDataBytes(SENSOR_DATA_REGISTER, 6);

  if (ImuConnectionSuccessful()) {
    SetSensorValues(
        ConvertUint8BytesIntoInt16SensorValue(measurement_values.at(0), measurement_values.at(1)),
        ConvertUint8BytesIntoInt16SensorValue(measurement_values.at(2), measurement_values.at(3)),
        ConvertUint8BytesIntoInt16SensorValue(measurement_values.at(4), measurement_values.at(5)));
  }

  return types::DriverStatus::OK;
}

auto Gyroscope::SetSensitivity(types::ImuSensitivity sensitivity) noexcept -> types::DriverStatus {
  if (!IsInitialized()) {
    return types::DriverStatus::HAL_ERROR;
  }

  SendSensitivityRegisterData(sensitivity);

  if (ImuConnectionSuccessful()) {
    SaveNewGyroscopeSensitivity(sensitivity);
  }

  return imu_status_;
}

auto Gyroscope::SaveNewGyroscopeSensitivity(types::ImuSensitivity sensitivity) noexcept -> void {
  sensitivity_ = sensitivity;
}

auto Gyroscope::SendSensitivityRegisterData(types::ImuSensitivity sensitivity) noexcept -> void {
  std::uint8_t new_config = GetGyroscopeConfigRegisterDataForSensitivity(sensitivity);
  Write({CONFIG_REGISTER, new_config});
}

auto Gyroscope::GetGyroscopeConfigRegisterDataForSensitivity(types::ImuSensitivity sensitivity) noexcept -> std::uint8_t {
  std::uint8_t fs_sel = 0;

  if (sensitivity == types::ImuSensitivity::FINEST) {
    fs_sel = imu::ImuSensitivityFSSelect::IMU_FS_FINEST;
  } else if (sensitivity == types::ImuSensitivity::FINER) {
    fs_sel = imu::ImuSensitivityFSSelect::IMU_FS_FINER;
  } else if (sensitivity == types::ImuSensitivity::ROUGHER) {
    fs_sel = imu::ImuSensitivityFSSelect::IMU_FS_ROUGHER;
  } else if (sensitivity == types::ImuSensitivity::ROUGHEST) {
    fs_sel = imu::ImuSensitivityFSSelect::IMU_FS_ROUGHEST;
  }

  std::vector<uint8_t> config_data;
  config_data = ReadDataBytes(CONFIG_REGISTER, 1);

  return static_cast<std::uint8_t>(config_data.at(0) | fs_sel << 3);
}

auto Gyroscope::GetSensitivity(void) noexcept -> types::ImuSensitivity {
  return sensitivity_;
}

}  // namespace imu