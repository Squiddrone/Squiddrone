#ifndef TESTS_MOCK_LIBRARIES_COM_MOCK_SPI_HPP_
#define TESTS_MOCK_LIBRARIES_COM_MOCK_SPI_HPP_

#include "error_types.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "mcu_settings.h"

typedef struct
{
} GPIO_TypeDef;

namespace spi {

enum class CSActiveState : uint8_t {
  ACTIVE_LOW = 0,
  ACTIVE_HIGH
};
typedef struct CSPinDefinition {
  GPIO_TypeDef *peripheral;
  uint16_t gpio_pin;
  CSActiveState active_state;
} CSPin;

class MockSPI {
 public:
  MockSPI(const CSPin chip_select){};
  MOCK_METHOD(types::DriverStatus, Transfer, (std::vector<uint8_t> & mosi_data_buffer, std::vector<uint8_t> &miso_data_buffer), (noexcept));
  MOCK_METHOD(types::DriverStatus, Write, (std::vector<uint8_t> & mosi_data_buffer), (noexcept));
};

using SPI = MockSPI;
}  // namespace spi
#endif