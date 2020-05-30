#ifndef SRC_I2C_INTERFACE_HPP_
#define SRC_I2C_INTERFACE_HPP_

#include "i2c_status.hpp"
#include <stdint.h>
#include <vector>
#include <tuple>

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
       * @param byte_size Amount of Bytes to read
       * @param timeout Timeout in milliseconds
       * @return std::tuple<I2CStatus, std::vector<uint8_t>> Status of I2C Interface and Data read as std::vector. Each element is a Byte read.
       */
      virtual auto Read(uint8_t address, uint16_t byte_size, uint32_t timeout=I2C_STANDARD_TIMEOUT_IN_MS) noexcept -> std::tuple<I2CStatus, std::vector<uint8_t>> = 0;
      
      /**
       * @brief Writes data to I2C participant
       * 
       * @param address The address of the I2C Bus participant
       * @param data Data to write to I2C participant. std::vector with each element is one Byte.
       * @param timeout Timeout in milliseconds
       * @return I2CStatus Status of I2C Interface
       */
      virtual auto Write(uint8_t address, const std::vector<uint8_t>& data, uint32_t timeout=I2C_STANDARD_TIMEOUT_IN_MS) noexcept -> I2CStatus = 0;
    
    protected:
      /// @brief Standard timeout of I2C Interface in milliseconds
      static constexpr int I2C_STANDARD_TIMEOUT_IN_MS = 200;
  };

} // namespace i2c

#endif