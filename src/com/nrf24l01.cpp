#include "nrf24l01.hpp"

namespace com {

auto NRF24L01::GetDataPacket() const noexcept -> types::com_msg_frame {
  return ComInterface::msg_buffer_->GetData();
}

auto NRF24L01::PutDataPacket(std::uint8_t target_id,
                             types::com_msg_frame &payload) const noexcept -> types::ComError {
  std::vector<std::uint8_t> miso_data;
  spi_->Transfer(miso_data, payload);
  return types::ComError::COM_OK;
}

}  // namespace com