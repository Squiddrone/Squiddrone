#include "inertial_measurement_sensor.hpp"

namespace imu {

auto InertialMeasurementSensor::Get(void) noexcept -> types::EuclideanVector<int16_t> {
  return sensor_values_;
}

auto InertialMeasurementSensor::Mpu9255Detected(void) noexcept -> bool {
  std::vector<uint8_t> data = {WHO_AM_I_MPU9255_REGISTER};
  Write(data);

  bool who_i_am_correct = false;
  if (ImuConnectionSuccessful()) {
    data = Read(1);
    if (ImuConnectionSuccessful()) {
      if (data.at(0) == WHO_AM_I_MPU9255_VALUE) {
        who_i_am_correct = true;
      }
    }
  }
  return who_i_am_correct;
}

auto InertialMeasurementSensor::ReadDataBytes(std::uint8_t read_from_register, std::uint16_t byte_size) noexcept -> std::vector<std::uint8_t> {
  std::vector<uint8_t> data = {read_from_register};
  Write(data);

  if (ImuConnectionSuccessful()) {
    data = Read(byte_size);
  }
  return data;
}

auto InertialMeasurementSensor::Read(std::uint16_t byte_size) noexcept -> std::vector<std::uint8_t> {
  i2c::I2CStatus i2c_status;
  std::vector<uint8_t> i2c_data;
  std::tie(i2c_status, i2c_data) = i2c_handler_->Read(i2c_address_, byte_size);

  if (i2c_status == i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL && i2c_data.size() == byte_size) {
    imu_status_ = types::HalError::WORKING;
  } else {
    imu_status_ = types::HalError::CONFIG_ERROR;
  }

  return i2c_data;
}

auto InertialMeasurementSensor::Write(const std::vector<std::uint8_t>& data) noexcept -> void {
  i2c::I2CStatus i2c_status = i2c_handler_->Write(i2c_address_, data);

  if (i2c_status == i2c::I2CStatus::I2C_TRANSACTION_SUCCESSFUL) {
    imu_status_ = types::HalError::WORKING;
  } else {
    imu_status_ = types::HalError::CONFIG_ERROR;
  }
}

auto InertialMeasurementSensor::ImuConnectionSuccessful(void) noexcept -> bool {
  return imu_status_ == types::HalError::WORKING;
}

auto InertialMeasurementSensor::SetI2CAdress(std::uint8_t i2c_address) noexcept -> void {
  i2c_address_ = i2c_address;
}

auto InertialMeasurementSensor::ConvertUint8BytesIntoInt16SensorValue(std::uint8_t first_byte, std::uint8_t second_byte) noexcept -> std::int16_t {
  return static_cast<std::int16_t>(first_byte << 8 | second_byte);
}

auto InertialMeasurementSensor::IsInitialized(void) noexcept -> bool {
  return initialized_;
}

auto InertialMeasurementSensor::SetSensorValues(std::int16_t x, std::int16_t y, std::int16_t z) noexcept -> void {
  sensor_values_.x = x;
  sensor_values_.y = y;
  sensor_values_.z = z;
}

}  // namespace imu