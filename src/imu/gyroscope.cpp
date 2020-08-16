#include "gyroscope.hpp"

namespace imu {

auto Gyroscope::Init(std::uint8_t i2c_address) noexcept -> types::HalError {
  SetI2CAdress(i2c_address);
  initialized_ = false;

  if (!Mpu9255Detected()) {
    return types::HalError::CONFIG_ERROR;
  }

  SetSensorValues(0, 0, 0);

  SendSensitivityRegisterData(sensitivity_);
  if (ImuConnectionFailed()) {
    return types::HalError::CONFIG_ERROR;
  }

  initialized_ = true;
  return types::HalError::WORKING;
}

auto Gyroscope::Update(void) noexcept -> types::HalError {
  if (!IsInitialized()) {
    return types::HalError::CONFIG_ERROR;
  }

  std::vector<uint8_t> data;
  data = ReadDataBytes(GYRO_XOUT_H, 6);

  if (ImuConnectionSuccessful()) {
    SetSensorValues(
        ConvertUint8BytesIntoInt16SensorValue(data.at(0), data.at(1)),
        ConvertUint8BytesIntoInt16SensorValue(data.at(2), data.at(3)),
        ConvertUint8BytesIntoInt16SensorValue(data.at(4), data.at(5)));
  }

  return types::HalError::WORKING;
}

auto Gyroscope::SetSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept -> types::HalError {
  if (!IsInitialized()) {
    imu_status_ = types::HalError::CONFIG_ERROR;
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
  std::vector<uint8_t> data = {GYRO_CONFIG, new_gyro_config};
  Write(data);
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