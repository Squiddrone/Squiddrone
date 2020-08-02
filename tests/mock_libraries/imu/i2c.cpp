#include "i2c.hpp"
#include "mpu9255_data.hpp"

namespace i2c {

std::uint8_t unit_test_address;
std::vector<std::uint8_t> unit_test_data;

auto I2C::Read(std::uint8_t address, std::uint16_t byte_size, std::uint32_t timeout) noexcept -> std::tuple<I2CStatus, std::vector<std::uint8_t>> {
  I2CStatus i2c_status = I2CStatus::I2C_PARAMETER_ERROR;
  std::vector<std::uint8_t> data = {0};

  if (unit_test_address == 0x68) {
    if (unit_test_data.at(0) == imu::WHO_AM_I_MPU9255_REGISTER) {
      i2c_status = I2CStatus::I2C_TRANSACTION_SUCCESSFUL;
      data = {imu::WHO_AM_I_MPU9255_VALUE};
    }
  }

  return {i2c_status, data};
}

auto I2C::Write(std::uint8_t address, const std::vector<std::uint8_t>& data, std::uint32_t timeout) noexcept -> I2CStatus {
  unit_test_address = address;
  unit_test_data = data;

  I2CStatus return_value = I2CStatus::I2C_TRANSACTION_FAILED;
  if (address == 0x68) {
    return_value = I2CStatus::I2C_TRANSACTION_SUCCESSFUL;
  }
  return return_value;
}
}  // namespace i2c
