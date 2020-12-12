#include "com_nrf24l01.hpp"

namespace com {
auto NRF24L01::EnableTxMode() const noexcept -> types::DriverStatus {
  return types::DriverStatus::OK;
}

auto NRF24L01::EnableRxMode() const noexcept -> types::DriverStatus {
}

auto NRF24L01::GetDataPacket() const noexcept -> types::com_msg_frame {
  types::com_msg_frame rv;
  return rv;
}

auto NRF24L01::PutDataPacket(std::uint8_t target_id, types::com_msg_frame &payload) const noexcept -> types::ComError {
  return types::ComError::COM_OK;
}
}  // namespace com