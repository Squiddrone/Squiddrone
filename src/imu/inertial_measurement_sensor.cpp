#include "inertial_measurement_sensor.hpp"

namespace imu {

auto InertialMeasurementSensor::Get(void) noexcept -> types::EuclideanVector<float> {
  return sensor_values_;
}

auto InertialMeasurementSensor::Mpu9255Detected(void) noexcept -> bool {
  std::vector<uint8_t> data = {WHO_AM_I_MPU9255_REGISTER};
  types::HalError imu_status = Write(data);

  bool who_i_am_correct = false;
  if (ImuConnectionSuccessful(imu_status)) {
    std::tie(imu_status, data) = Read(1);
    if (ImuConnectionSuccessful(imu_status)) {
      if (data.at(0) == WHO_AM_I_MPU9255_VALUE) {
        who_i_am_correct = true;
      }
    }
  }
  return who_i_am_correct;
}

auto InertialMeasurementSensor::ReadDataBytes(std::uint8_t read_from_register, std::uint16_t byte_size) noexcept -> std::pair<types::HalError, std::vector<std::uint8_t>> {
  std::vector<uint8_t> data = {read_from_register};
  types::HalError imu_status = Write(data);

  if (ImuConnectionSuccessful(imu_status)) {
    std::tie(imu_status, data) = Read(byte_size);
  }
  return {imu_status, data};
}

auto InertialMeasurementSensor::Read(std::uint16_t byte_size) noexcept -> std::pair<types::HalError, std::vector<std::uint8_t>> {
  i2c::I2CStatus i2c_status;
  std::vector<uint8_t> i2c_data;
  std::tie(i2c_status, i2c_data) = i2c_handler_->Read(i2c_address_, byte_size);

  types::HalError imu_status = types::HalError::CONFIG_ERROR;
  if (i2c_status == i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL && i2c_data.size() == byte_size) {
    imu_status = types::HalError::WORKING;
  }

  return {imu_status, i2c_data};
}

auto InertialMeasurementSensor::Write(const std::vector<std::uint8_t>& data) noexcept -> types::HalError {
  i2c::I2CStatus i2c_status = i2c_handler_->Write(i2c_address_, data);

  types::HalError imu_status;
  if (i2c_status == i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL) {
    imu_status = types::HalError::WORKING;
  }
  return imu_status;
}

auto InertialMeasurementSensor::ImuConnectionSuccessful(types::HalError imu_status) noexcept -> bool {
  return imu_status == types::HalError::WORKING;
}

}  // namespace imu