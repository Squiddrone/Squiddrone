#ifndef SRC_I2C_INTERFACE_HPP_
#define SRC_I2C_INTERFACE_HPP_

#include <cstdint>
#include <tuple>
#include <vector>
#include "error_types.hpp"

namespace i2c {

/**
 * @brief Interface of I2C package
 * 
 */
class I2CInterface {
 public:
  virtual ~I2CInterface() = default;
  explicit I2CInterface(void){};

  /**
   * @brief Reads data from I2C Bus
   * 
   * @param address The address of the I2C Bus participant
   * @param byte_size Amount of Bytes to read \n
   *                  Allowed range of Bytes is between 1 and 32.
   * @param timeout Timeout in milliseconds \n
   *                Allowed range of Timeout is between 1 and HAL_MAX_DELAY (0xFFFFFFFF, see stm32g4xx_hal_def.h).
   * @return std::tuple<#types::DriverStatus, std::vector<uint8_t>> Status of I2C Interface and Data read as std::vector. Each element is a Byte read.
   */
  virtual auto Read(std::uint8_t address, std::uint16_t byte_size, std::uint32_t timeout = I2C_STANDARD_TIMEOUT_IN_MS) noexcept -> std::tuple<types::DriverStatus, std::vector<std::uint8_t>> = 0;

  /**
   * @brief Writes data to I2C participant
   * 
   * @param address The address of the I2C Bus participant
   * @param data Data to write to I2C participant. std::vector with each element is one Byte. \n
   *             Allowed range of Bytes is between 1 and 32.
   * @param timeout Timeout in milliseconds \n
   *                Allowed range of Timeout is between 1 and HAL_MAX_DELAY (0xFFFFFFFF, see stm32g4xx_hal_def.h).
   * @return #types::DriverStatus Status of I2C Interface
   */
  virtual auto Write(std::uint8_t address, const std::vector<std::uint8_t>& data, std::uint32_t timeout = I2C_STANDARD_TIMEOUT_IN_MS) noexcept -> types::DriverStatus = 0;

 protected:
  /// @brief Standard timeout of I2C Interface in milliseconds
  static constexpr int I2C_STANDARD_TIMEOUT_IN_MS = 200;
};

}  // namespace i2c

#endif