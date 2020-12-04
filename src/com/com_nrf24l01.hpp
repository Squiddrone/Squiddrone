#ifndef SRC_COM_COM_NRF24L01_HPP_
#define SRC_COM_COM_NRF24L01_HPP_

#include "com_interface.hpp"
#include "com_nrf24l01_reg.hpp"

namespace com {

/**
 * @brief Driver for the NRF24L01 transceiver. 
 * 
 */
class NRF24L01 final : public ComInterface {
 public:
  virtual auto GetDataPacket() const noexcept -> types::com_msg_frame override;
  virtual auto PutDataPacket(std::uint8_t target_id, types::com_msg_frame &payload) const noexcept
      -> types::ComError override;

  explicit NRF24L01(std::unique_ptr<com::ComMessageBuffer> msg_buf) : ComInterface(std::move(msg_buf)){};
  NRF24L01() = delete;
  ~NRF24L01() = default;

 private:
  auto SetConfiguration(std::uint8_t register_addr, std::uint8_t byte_offset, std::uint8_t value) noexcept -> types::DriverStatus;
  auto GetConfiguration(std::uint8_t register_addr) noexcept -> std::uint8_t;
  auto SetRXAddress(std::uint8_t data_pipe, std::uint_fast64_t address) noexcept -> types::DriverStatus;
  auto SetTXAddress(std::uint_fast64_t address) noexcept -> types::DriverStatus;

  ComMessageBuffer msg_buffer;
};
}  // namespace com

#endif
