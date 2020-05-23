#ifndef SRC_I2C_INTERFACE_HPP_
#define SRC_I2C_INTERFACE_HPP_

#include "i2c_status.hpp"
#include <stdint.h>
#include <vector>

constexpr int I2C_STANDARD_TIMEOUT = 0xFFFFFFFFU; //taken from HAL_MAX_DELAY

namespace i2c {

  class I2CInterface {
    public:
      virtual ~I2CInterface() = default;
      explicit I2CInterface(void){};

      virtual auto read(uint8_t address, const std::vector<uint8_t> data, int timeout=I2C_STANDARD_TIMEOUT) noexcept -> std::vector<uint8_t> = 0;
      virtual auto write(uint8_t address, const std::vector<uint8_t> data, int timeout=I2C_STANDARD_TIMEOUT) noexcept -> I2CStatus = 0;
  };

} // namespace i2c

#endif