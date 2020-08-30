#ifndef MOCK_i2C_HPP_
#define MOCK_i2C_HPP_

#include <gmock/gmock.h>
#include <memory>
#include "i2c_interface.hpp"

namespace i2c {

class MOCKI2C : public I2CInterface {
 public:
  MOCK_METHOD((std::pair<types::DriverStatus, std::vector<std::uint8_t>>), Read, (std::uint8_t address, std::uint16_t byte_size, std::uint32_t timeout), (noexcept));
  MOCK_METHOD((std::pair<types::DriverStatus, std::vector<std::uint8_t>>), ReadContentFromRegister, (std::uint8_t address, std::uint8_t register_, std::uint16_t byte_size, std::uint32_t timeout), (noexcept));
  MOCK_METHOD(types::DriverStatus, Write, (std::uint8_t address, const std::vector<std::uint8_t>& data, std::uint32_t timeout), (noexcept));
};
}  // namespace i2c

#endif