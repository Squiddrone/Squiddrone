#include "i2c.hpp"

namespace i2c
{

  auto I2C::read(uint8_t address, uint16_t byte_size, int timeout) noexcept -> std::tuple<I2CStatus, std::vector<uint8_t>> {
    uint8_t buffer[byte_size];

    HAL_StatusTypeDef ret = HAL_I2C_Master_Receive(&hi2c2, address, buffer, byte_size, timeout);

    std::vector<uint8_t> data(buffer, buffer+byte_size);
    return {I2CStatus::I2C_TRANSACTION_FAILED, data};
  }

  auto I2C::write(uint8_t address, const std::vector<uint8_t>& data, int timeout) noexcept -> I2CStatus {
    HAL_StatusTypeDef ret = HAL_I2C_Master_Transmit(&hi2c2, address, (uint8_t*)data.data(), (uint16_t)data.size(), timeout);
    return I2CStatus::I2C_TRANSACTION_FAILED;
  }

} // namespace i2c
