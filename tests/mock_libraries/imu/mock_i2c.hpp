#include <gmock/gmock.h>
#include <memory>
#include <tuple>
#include "i2c_interface.hpp"

namespace i2c {

class MOCKI2C : public I2CInterface {
 public:
  MOCK_METHOD((std::tuple<i2c::I2CStatus, std::vector<std::uint8_t>>), Read, (std::uint8_t address, std::uint16_t byte_size, std::uint32_t timeout), (noexcept));
  MOCK_METHOD(I2CStatus, Write, (std::uint8_t address, const std::vector<std::uint8_t>& data, std::uint32_t timeout), (noexcept));
};
}  // namespace i2c
