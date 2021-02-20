#ifndef TESTS_COM_MOCK_LIBRARIES_COM_NRF24L01_SPI_PROTOCOL_MOCK_HPP_
#define TESTS_COM_MOCK_LIBRARIES_COM_NRF24L01_SPI_PROTOCOL_MOCK_HPP_

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "spi.hpp"

namespace com {

class NRF24L01SpiProtocol {
 public:
  NRF24L01SpiProtocol(std::unique_ptr<spi::SPI> spi){};
  MOCK_METHOD((std::uint8_t), ReadRegister, (std::uint8_t), (noexcept));
  MOCK_METHOD((std::vector<uint8_t>), ReadRegister, (std::uint8_t, std::uint8_t), (noexcept));
  MOCK_METHOD((types::DriverStatus), WriteRegister, (std::uint8_t, std::uint8_t), (noexcept));
};
}  // namespace com

#endif