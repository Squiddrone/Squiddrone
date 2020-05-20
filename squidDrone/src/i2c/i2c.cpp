#include "i2c.hpp"

namespace i2c
{

  std::vector<uint8_t> I2C::read(uint8_t address, std::vector<uint8_t> data, int timeout) noexcept {
    std::vector<uint8_t> result;
    return result;
  }

  I2CStatus write(uint8_t address, std::vector<uint8_t> data, int timeout) noexcept {
    return I2CStatus::I2C_TRANSACTION_FAILED;
  }

} // namespace i2c
