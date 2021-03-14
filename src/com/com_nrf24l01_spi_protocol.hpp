#ifndef SRC_COM_COM_NRF24L01_SPI_PROTOCOL_HPP_
#define SRC_COM_COM_NRF24L01_SPI_PROTOCOL_HPP_

#include <memory>
#include "com_nrf24l01_reg.hpp"
#include "spi.hpp"

namespace com {
/**
 * @brief Implements protocol layer for communication to NRF24L01 based on available opcodes.
 * 
 */
class NRF24L01SpiProtocol final {
 public:
  /**
  * @brief Construct a new NRF24L01SpiProtocol object
  * 
  */
  NRF24L01SpiProtocol() = default;
  auto ReadRegister(std::uint8_t register_address) noexcept -> std::uint8_t;
  auto ReadRegister(std::uint8_t register_address, std::uint8_t length) noexcept -> std::vector<uint8_t>;
  auto WriteRegister(std::uint8_t register_address, std::uint8_t register_content) -> types::DriverStatus;
  auto WriteRegister(std::uint8_t register_address, std::vector<uint8_t> register_content) -> types::DriverStatus;
  auto WritePayloadData(std::vector<uint8_t> &payload) noexcept -> types::DriverStatus;
  auto ReadRxPayloadData(std::vector<uint8_t> &payload) noexcept -> types::DriverStatus;
  auto FlushTxBuffer() noexcept -> types::DriverStatus;
  auto FlushRxBuffer() noexcept -> types::DriverStatus;
  auto ReadAndClearIRQFlags() noexcept -> register_t;

 private:
  spi::CSPin cs_pin_ = {.peripheral = GPIOA, .gpio_pin = CSCOM_Pin, .active_state = spi::CSActiveState::ACTIVE_LOW};
  spi::SPI spi_{cs_pin_};
};

}  // namespace com

#endif