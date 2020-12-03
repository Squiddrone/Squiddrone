#ifndef SRC_COM_COM_NRF24L01_HPP_
#define SRC_COM_COM_NRF24L01_HPP_

#include "com_interface.hpp"

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
};
}  // namespace com

#endif
