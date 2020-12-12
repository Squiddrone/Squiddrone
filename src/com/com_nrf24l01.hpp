#ifndef SRC_COM_COM_NRF24L01_HPP_
#define SRC_COM_COM_NRF24L01_HPP_

#include "com_interface.hpp"
#include "com_nrf24l01_reg.hpp"
#include "spi.hpp"

namespace com {

/**
 * @brief Driver for the NRF24L01 transceiver. 
 * 
 */
class NRF24L01 final : public ComInterface {
 public:
  auto GetDataPacket() const noexcept -> types::com_msg_frame override;
  auto PutDataPacket(std::uint8_t target_id, types::com_msg_frame &payload) const noexcept
      -> types::ComError override;

  explicit NRF24L01(std::unique_ptr<com::ComMessageBuffer> msg_buf, spi::CSPinDefinition &cs_pin) : ComInterface(std::move(msg_buf)),
                                                                                                    cs_pin_(cs_pin){};
  NRF24L01() = delete;
  ~NRF24L01() = default;

 private:
  spi::CSPin cs_pin_;
  spi::SPI spi_{cs_pin_};
  auto SetConfigBit(std::uint8_t register_addr, std::uint8_t bit_value) noexcept -> void;
  auto EnableTxMode() const noexcept -> types::DriverStatus;
  auto EnableRxMode() const noexcept -> types::DriverStatus;
  auto SetTxAddress(std::uint64_t tx_addr) const noexcept -> types::DriverStatus;
  auto SetPayloadData() const noexcept -> types::DriverStatus;
  auto SetRxAddress(std::uint8_t pipe_no, std::uint64_t rx_addr) const noexcept -> types::DriverStatus;
};
}  // namespace com

#endif
