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
  measurement_values = ReadDataBytes(GYRO_XOUT_H, 6);

  if (ImuConnectionSuccessful()) {
    SetSensorValues(
        ConvertUint8BytesIntoInt16SensorValue(measurement_values.at(0), measurement_values.at(1)),
        ConvertUint8BytesIntoInt16SensorValue(measurement_values.at(2), measurement_values.at(3)),
        ConvertUint8BytesIntoInt16SensorValue(measurement_values.at(4), measurement_values.at(5)));
  }

  return types::DriverStatus::OK;
}

auto Gyroscope::SetSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept -> types::DriverStatus {
  if (!IsInitialized()) {
    return types::DriverStatus::HAL_ERROR;
  }

  SendSensitivityRegisterData(gyroscope_sensitivity);

  if (ImuConnectionSuccessful()) {
    SaveNewGyroscopeSensitivity(gyroscope_sensitivity);
  }

  return imu_status_;
}

auto Gyroscope::SaveNewGyroscopeSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept -> void {
  sensitivity_ = gyroscope_sensitivity;
}

auto Gyroscope::SendSensitivityRegisterData(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept -> void {
  std::uint8_t new_gyro_config = GetGyroscopeConfigRegisterDataForSensitivity(gyroscope_sensitivity);
  Write({GYRO_CONFIG, new_gyro_config});
}

auto Gyroscope::GetGyroscopeConfigRegisterDataForSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept -> std::uint8_t {
  std::uint8_t gyro_fs_sel = 0;

  if (gyroscope_sensitivity == types::GyroscopeSensitivity::FINEST) {
    gyro_fs_sel = imu::GyroscopeSensitivityFSSelect::GYROSCOPE_FS_FINEST;
  } else if (gyroscope_sensitivity == types::GyroscopeSensitivity::FINER) {
    gyro_fs_sel = imu::GyroscopeSensitivityFSSelect::GYROSCOPE_FS_FINER;
  } else if (gyroscope_sensitivity == types::GyroscopeSensitivity::ROUGHER) {
    gyro_fs_sel = imu::GyroscopeSensitivityFSSelect::GYROSCOPE_FS_ROUGHER;
  } else if (gyroscope_sensitivity == types::GyroscopeSensitivity::ROUGHEST) {
    gyro_fs_sel = imu::GyroscopeSensitivityFSSelect::GYROSCOPE_FS_ROUGHEST;
  }

  std::vector<uint8_t> gyro_config;
  gyro_config = ReadDataBytes(GYRO_CONFIG, 1);

  return static_cast<std::uint8_t>(gyro_config.at(0) | gyro_fs_sel << 3);
}

auto Gyroscope::GetSensitivity(void) noexcept -> types::GyroscopeSensitivity {
  return sensitivity_;
}

}  // namespace imu