#ifndef SRC_I2C_HANDLER_HPP_
#define SRC_I2C_HANDLER_HPP_

#include "i2c_interface.hpp"

namespace i2c {

  class I2C final : public I2CInterface {
    public:
      ~I2C() = default;
      explicit I2C(void): I2CInterface(){};

      auto read(uint8_t address, std::vector<uint8_t> data, int timeout=I2C_STANDARD_TIMEOUT) noexcept -> std::vector<uint8_t> override;
      auto write(uint8_t address, std::vector<uint8_t> data, int timeout=I2C_STANDARD_TIMEOUT) noexcept -> I2CStatus override;
  };

} // namespace i2c

#endif