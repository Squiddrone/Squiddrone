#ifndef SRC_I2C_HANDLER_HPP_
#define SRC_I2C_HANDLER_HPP_

#include "stm32g4xx_hal.h"
#include "i2c_config.h"
#include "i2c_interface.hpp"

namespace i2c {

  /**
   * @brief The concrete implementation of I2C Interface
   * 
   */
  class I2C final : public I2CInterface {
    public:
      ~I2C() = default;
      explicit I2C(void): I2CInterface(){};

      auto Read(uint8_t address, uint16_t byte_size, uint32_t timeout=I2C_STANDARD_TIMEOUT_IN_MS) noexcept -> std::tuple<I2CStatus, std::vector<uint8_t>> override;
      auto Write(uint8_t address, const std::vector<uint8_t>& data, uint32_t timeout=I2C_STANDARD_TIMEOUT_IN_MS) noexcept -> I2CStatus override;
    private:
      auto CheckForValidInputRead(uint8_t address, uint16_t byte_size, uint32_t timeout) noexcept -> bool;
      auto CheckForValidInputWrite(uint8_t address, const std::vector<uint8_t>& data, uint32_t timeout) noexcept -> bool;
      auto CheckIfI2CAddressIsValid(uint8_t address) noexcept -> bool;
      auto CheckIfI2CAmountOfBytesIsValid(uint16_t amount_of_bytes) noexcept -> bool;
      auto CheckIfI2CTimeoutIsValid(uint32_t timeout) noexcept -> bool;
      auto ModifyAddressForI2C7Bit(uint8_t address) noexcept -> uint8_t;
      auto GetI2CStatus(HAL_StatusTypeDef hal_status) noexcept -> I2CStatus;
  };

} // namespace i2c

#endif