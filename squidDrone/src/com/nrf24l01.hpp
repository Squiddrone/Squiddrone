#ifndef SRC_SPI_NRF24L01_HPP_
#define SRC_SPI_NRF24L01_HPP_

#include "com_interface.hpp"
#include "com_message_buffer.hpp"
#include <spi.hpp>

namespace com {

class NRF24L01 final : public com::ComInterface {
 public:
  NRF24L01() = delete;
  explicit NRF24L01(spi::SPIInterface &spi,
                    std::unique_ptr<com::ComMessageBuffer> msg_buf) : spi_(spi), com::ComInterface(std::move(msg_buf)){};

  auto PutDataPacket(std::uint8_t target_id,
                     types::com_msg_frame &payload) const noexcept -> types::ComError override;

  auto GetDataPacket() noexcept -> types::com_msg_frame override;

 private:
  spi::SPIInterface &spi_;
};
}  // namespace com

#endif