#include "i2c.hpp"

namespace i2c {

auto I2C::Read(std::uint8_t address, std::uint16_t byte_size, std::uint32_t timeout) noexcept -> std::tuple<I2CStatus, std::vector<std::uint8_t>> {
  I2CStatus i2c_status = I2CStatus::I2C_PARAMETER_ERROR;
  std::vector<std::uint8_t> data = {0};
  return {i2c_status, data};
}

auto I2C::Write(std::uint8_t address, const std::vector<std::uint8_t>& data, std::uint32_t timeout) noexcept -> I2CStatus {
  return I2CStatus::I2C_PARAMETER_ERROR;
}
}  // namespace i2c
