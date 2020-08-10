#ifndef SRC_SPI_NRF24L01_HPP_
#define SRC_SPI_NRF24L01_HPP_

#include <spi.hpp>

#include "com_interface.hpp"
#include "com_message_buffer.hpp"

namespace com {

class NRF24L01 final : public ComInterface {
 public:
  NRF24L01() = delete;
  explicit NRF24L01(std::unique_ptr<spi::SPI> spi,
                    std::unique_ptr<ComMessageBuffer> msg_buf) : ComInterface(std::move(msg_buf)), spi_(std::move(spi)){};
  virtual ~NRF24L01() = default;

  auto PutDataPacket(std::uint8_t target_id,
                     types::com_msg_frame &payload) const noexcept -> types::ComError override;

  auto GetDataPacket() const noexcept -> types::com_msg_frame override;

 private:
  std::unique_ptr<spi::SPI> spi_;
};
}  // namespace com

#endif