#ifndef TESTS_COM_MOCK_LIBRARIES_COM_NRF24L01_SPI_PROTOCOL_MOCK_HPP_
#define TESTS_COM_MOCK_LIBRARIES_COM_NRF24L01_SPI_PROTOCOL_MOCK_HPP_

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "spi.hpp"

namespace com {

class NRF24L01SpiProtocol {
 public:
  NRF24L01SpiProtocol() = default;
  MOCK_METHOD((std::uint8_t), ReadRegister, (std::uint8_t), (noexcept));
  MOCK_METHOD((std::vector<uint8_t>), ReadRegister, (std::uint8_t, std::uint8_t), (noexcept));
  MOCK_METHOD((types::DriverStatus), WriteRegister, (std::uint8_t, std::uint8_t), (noexcept));
  MOCK_METHOD((types::DriverStatus), FlushTxBuffer, (), (noexcept));
  MOCK_METHOD((types::DriverStatus), FlushRxBuffer, (), (noexcept));
  MOCK_METHOD((std::uint8_t), ReadAndClearIRQFlags, (), (noexcept));
  MOCK_METHOD((types::DriverStatus), WritePayloadData, (std::vector<uint8_t>));
};
}  // namespace com

#endif