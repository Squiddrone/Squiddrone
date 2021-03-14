#ifndef TESTS_SPI_MOCK_LIBRARIES_CSPIN_MOCK_HPP_
#define TESTS_SPI_MOCK_LIBRARIES_CSPIN_MOCK_HPP_

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "stm32g4xx_hal.h"

namespace spi {

class CSPin {
 public:
  CSPin(){};
  CSPin(const CSPin&){};
  MOCK_METHOD((void), SetCSActive, (), (noexcept));
  MOCK_METHOD((void), SetCSInactive, (), (noexcept));
};
}  // namespace spi

#endif
