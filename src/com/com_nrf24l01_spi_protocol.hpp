#ifndef SRC_COM_COM_NRF24L01_SPI_PROTOCOL_HPP_
#define SRC_COM_COM_NRF24L01_SPI_PROTOCOL_HPP_

#include "com_nrf24l01_reg.hpp"
#include "spi.hpp"

namespace com {
class NRF24L01SpiProtocol {
 public:
  NRF24L01SpiProtocol(spi::SPI &spi) : spi_(spi){};
  // SPI protocol functions
  auto ReadRegister(std::uint8_t register_address) noexcept -> std::uint8_t;
  auto ReadRegister(std::uint8_t register_address, std::uint8_t length) noexcept -> std::vector<std::uint8_t>;
  auto WriteRegister(std::uint8_t register_address, std::uint8_t register_content) -> types::DriverStatus;
  auto WriteRegister(std::uint8_t register_address, std::vector<std::uint8_t> &register_content) -> types::DriverStatus;
  auto WritePayloadData(std::vector<uint8_t> &payload) noexcept -> types::DriverStatus;

 private:
  spi::SPI &spi_;
};
}  // namespace com

#endif