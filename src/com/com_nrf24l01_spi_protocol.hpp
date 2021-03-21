#ifndef SRC_COM_COM_NRF24L01_SPI_PROTOCOL_HPP_
#define SRC_COM_COM_NRF24L01_SPI_PROTOCOL_HPP_

#include "com_nrf24l01_reg.hpp"
#include "spi.hpp"

namespace com {
/**
 * @brief Collection of basic operations offered by the NRF24L01 communication device.
 * 
 */
class NRF24L01SpiProtocol final {
 public:
  /**
  * @brief Simple single byte register read action.
  * 
  * @param register_address Addess of the target register as hex.
  * @return std::uint8_t Register content as byte.
  */

  auto ReadRegister(std::uint8_t register_address) noexcept -> std::uint8_t;
  /**
   * @brief Read multiple byte register.
   * 
   * @param register_address Address of the target register as hex.
   * @param length Number of bytes to read.
   * @return std::vector<std::uint8_t> Register content as vector of bytes.
   */
  auto ReadRegister(std::uint8_t register_address, std::uint8_t length) noexcept -> std::vector<std::uint8_t>;
  /**
   * @brief Simple single byte write action.
   * 
   * @param register_address Address of the target register as hex.
   * @param register_content Register content as byte. The current content will be overwritten.
   * @return types::DriverStatus 
   */
  auto WriteRegister(std::uint8_t register_address, std::uint8_t register_content) noexcept -> types::DriverStatus;
  /**
   * @brief Write multiple bytes to register.
   * 
   * @param register_address Address of the target register as hex.
   * @param register_content Register content as byte. The current content will be overwritten.
   * @return types::DriverStatus 
   */
  auto WriteRegister(std::uint8_t register_address, std::vector<std::uint8_t> &register_content) noexcept -> types::DriverStatus;
  /**
   * @brief Write to transmission payload buffer.
   * 
   * @param payload Reference to the vector holding payload data that must be transmitted.
   * @return types::DriverStatus 
   */
  auto WritePayloadData(std::vector<std::uint8_t> &payload) noexcept -> types::DriverStatus;
  /**
   * @brief Get first level of the rx fifo buffer.
   * 
   * @param payload Reference to a vector to which the received payload will be written.
   * @return types::DriverStatus 
   */
  auto ReadPayloadData(std::vector<std::uint8_t> &payload) noexcept -> types::DriverStatus;
  /**
   * @brief Flush the transmission buffer on the NRF24L01 device.
   * 
   * @return types::DriverStatus 
   */
  auto FlushTxBuffer() noexcept -> types::DriverStatus;
  /**
   * @brief Flush the receive buffer on the NRF24L01 device.
   * 
   * @return types::DriverStatus 
   */
  auto FlushRxBuffer() noexcept -> types::DriverStatus;
  /**
   * @brief Get the current content of the status register and clear IRQ related flags.
   * 
   * @return register_t Status register content.
   */
  auto ReadAndClearIRQFlags() noexcept -> register_t;
  /**
   * @brief Construct a new NRF24L01SpiProtocol object
   * 
   * @param spi 
   */
  explicit NRF24L01SpiProtocol(spi::SPI &spi) : spi_(spi){};
  NRF24L01SpiProtocol() = delete;
  /**
   * @brief Destroy the NRF24L01SpiProtocol object
   * 
   */
  ~NRF24L01SpiProtocol() = default;

 private:
  spi::SPI &spi_;
};
}  // namespace com

#endif