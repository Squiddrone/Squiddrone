#include "imu_sensor.hpp"

namespace imu {

auto InertialMeasurementSensor::Update(void) noexcept -> types::DriverStatus {
  if (!IsInitialized())
    return types::DriverStatus::HAL_ERROR;

  const std::uint16_t REGISTER_DATA_LENGTH = 6;
  std::vector<uint8_t> measurement_values = ReadContentFromRegister(SENSOR_DATA_REGISTER, REGISTER_DATA_LENGTH);

  if (ImuConnectionSuccessful()) {
    SetSensorValues(
        ConvertUint8BytesIntoInt16SensorValue(measurement_values.at(0), measurement_values.at(1)),
        ConvertUint8BytesIntoInt16SensorValue(measurement_values.at(2), measurement_values.at(3)),
        ConvertUint8BytesIntoInt16SensorValue(measurement_values.at(4), measurement_values.at(5)));
  }

  return types::DriverStatus::OK;
}

auto InertialMeasurementSensor::Get(void) noexcept -> types::EuclideanVector<int16_t> {
  return sensor_values_;
}

auto InertialMeasurementSensor::Mpu9255Detected(void) noexcept -> bool {
  bool who_i_am_correct = false;

  std::vector<uint8_t> who_am_i_register_value = ReadContentFromRegister(WHO_AM_I_MPU9255_REGISTER, 1);
  if (ImuConnectionSuccessful()) {
    if (who_am_i_register_value.at(0) == WHO_AM_I_MPU9255_VALUE) {
      who_i_am_correct = true;
    }
  }

  return who_i_am_correct;
}

auto InertialMeasurementSensor::ReadContentFromRegister(std::uint8_t read_from_register, std::uint16_t byte_size) noexcept -> std::vector<std::uint8_t> {
  types::DriverStatus i2c_status;
  std::vector<uint8_t> content_of_register;

  std::tie(i2c_status, content_of_register) = i2c_handler_->ReadContentFromRegister(i2c_address_, read_from_register, byte_size);
  if (i2c_status == types::DriverStatus::OK && content_of_register.size() == byte_size) {
    imu_status_ = types::DriverStatus::OK;
  } else {
    imu_status_ = types::DriverStatus::HAL_ERROR;
  }

  return content_of_register;
}

auto InertialMeasurementSensor::Write(const std::vector<std::uint8_t>& data) noexcept -> void {
  imu_status_ = i2c_handler_->Write(i2c_address_, data);
}

auto InertialMeasurementSensor::ImuConnectionSuccessful(void) noexcept -> bool {
  return imu_status_ == types::DriverStatus::OK;
}

auto InertialMeasurementSensor::ImuConnectionFailed(void) noexcept -> bool {
  return !ImuConnectionSuccessful();
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