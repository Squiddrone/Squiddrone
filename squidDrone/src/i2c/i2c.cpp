#include "i2c.hpp"

namespace i2c
{

  auto I2C::read(uint8_t address, std::vector<uint8_t> data, int timeout) noexcept -> std::vector<uint8_t> {
    std::vector<uint8_t> result;
    return result;
  }

  auto write(uint8_t address, std::vector<uint8_t> data, int timeout) noexcept -> I2CStatus {
    return I2CStatus::I2C_TRANSACTION_FAILED;
  }

} // namespace i2c
