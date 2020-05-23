#include "i2c.hpp"

namespace i2c
{

  auto I2C::read(uint8_t address, const std::vector<uint8_t> data, int timeout) noexcept -> std::vector<uint8_t> {
    auto result = std::vector<uint8_t>{0, 0, 0};
    return result;

    uint8_t buf[12];
    HAL_StatusTypeDef ret = HAL_I2C_Master_Transmit(&hi2c2, address, buf, 1, 0);
  }

  auto I2C::write(uint8_t address, const std::vector<uint8_t> data, int timeout) noexcept -> I2CStatus {
    return I2CStatus::I2C_TRANSACTION_FAILED;
  }

} // namespace i2c
