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
  explicit I2C(void) : I2CInterface(){};

  auto Read(std::uint8_t address, std::uint16_t byte_size, std::uint32_t timeout = I2C_STANDARD_TIMEOUT_IN_MS) noexcept -> std::tuple<types::DriverStatus, std::vector<std::uint8_t>> override;
  auto Write(std::uint8_t address, const std::vector<std::uint8_t>& data, std::uint32_t timeout = I2C_STANDARD_TIMEOUT_IN_MS) noexcept -> types::DriverStatus override;

 private:
  auto CheckForValidInputRead(std::uint8_t address, std::uint16_t byte_size, std::uint32_t timeout) noexcept -> bool;
  auto CheckForValidInputWrite(std::uint8_t address, const std::vector<std::uint8_t>& data, std::uint32_t timeout) noexcept -> bool;
  auto CheckIfI2CAddressIsValid(std::uint8_t address) noexcept -> bool;
  auto CheckIfI2CAmountOfBytesIsValid(std::uint16_t amount_of_bytes) noexcept -> bool;
  auto CheckIfI2CTimeoutIsValid(std::uint32_t timeout) noexcept -> bool;
  auto ModifyAddressForI2C7Bit(std::uint8_t address) noexcept -> std::uint8_t;
  auto GetI2CStatus(HAL_StatusTypeDef hal_status) noexcept -> types::DriverStatus;
};

}  // namespace i2c

#endif