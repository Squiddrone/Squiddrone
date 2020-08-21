#include "inertial_measurement_sensor.hpp"

namespace imu {

auto InertialMeasurementSensor::Get(void) noexcept -> types::EuclideanVector<int16_t> {
  return sensor_values_;
}

auto InertialMeasurementSensor::Mpu9255Detected(void) noexcept -> bool {
  Write({WHO_AM_I_MPU9255_REGISTER});

  bool who_i_am_correct = false;
  if (ImuConnectionSuccessful()) {
    std::vector<uint8_t> who_am_i_register_value = Read(1);
    if (ImuConnectionSuccessful()) {
      if (who_am_i_register_value.at(0) == WHO_AM_I_MPU9255_VALUE) {
        who_i_am_correct = true;
      }
    }
  }
  return who_i_am_correct;
}

auto InertialMeasurementSensor::ReadDataBytes(std::uint8_t read_from_register, std::uint16_t byte_size) noexcept -> std::vector<std::uint8_t> {
  Write({read_from_register});

  std::vector<uint8_t> content_of_register = {0};
  if (ImuConnectionSuccessful()) {
    content_of_register = Read(byte_size);
  }
  return content_of_register;
}

auto InertialMeasurementSensor::Read(std::uint16_t byte_size) noexcept -> std::vector<std::uint8_t> {
  types::DriverStatus i2c_status;
  std::vector<uint8_t> i2c_data;
  std::tie(i2c_status, i2c_data) = i2c_handler_->Read(i2c_address_, byte_size);

  if (i2c_status == types::DriverStatus::OK && i2c_data.size() == byte_size) {
    imu_status_ = types::DriverStatus::OK;
  } else {
    imu_status_ = types::DriverStatus::HAL_ERROR;
  }

  return i2c_data;
}

auto InertialMeasurementSensor::Write(const std::vector<std::uint8_t>& data) noexcept -> void {
  types::DriverStatus i2c_status = i2c_handler_->Write(i2c_address_, data);

  if (i2c_status == types::DriverStatus::OK) {
    imu_status_ = types::DriverStatus::OK;
  } else {
    imu_status_ = types::DriverStatus::HAL_ERROR;
  }
}

auto InertialMeasurementSensor::ImuConnectionSuccessful(void) noexcept -> bool {
  return imu_status_ == types::DriverStatus::OK;
}

auto InertialMeasurementSensor::ImuConnectionFailed(void) noexcept -> bool {
  return imu_status_ != types::DriverStatus::OK;
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