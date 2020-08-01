#include "inertial_measurement_sensor.hpp"

namespace imu {

auto InertialMeasurementSensor::Get(void) noexcept -> types::EuclideanVector<float> {
  return sensor_values_;
}

auto InertialMeasurementSensor::Update(void) noexcept -> types::HalError {
  return types::HalError::PARAMETER_ERROR;
}

auto InertialMeasurementSensor::Read(std::uint16_t byte_size) noexcept -> std::tuple<types::HalError, std::vector<std::uint8_t>> {
  i2c::I2CStatus i2c_status;
  std::vector<uint8_t> i2c_data;
  std::tie(i2c_status, i2c_data) = i2c_handler_->Read(i2c_address_, byte_size);

  types::HalError imu_status = types::HalError::CONFIG_ERROR;
  if (i2c_status == i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL) {
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

}  // namespace imu