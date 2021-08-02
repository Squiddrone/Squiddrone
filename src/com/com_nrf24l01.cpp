#include "com_nrf24l01.hpp"

namespace com {

auto NRF24L01::PutDataPacket(std::uint8_t target_id, types::com_msg_frame &payload) noexcept -> types::DriverStatus {
  if (payload.size() > types::COM_MAX_FRAME_LENGTH) {
    return types::DriverStatus::INPUT_ERROR;
  }

  ON_ERROR_RETURN(nrf_->InitTx());

  ON_ERROR_RETURN(nrf_->SetTxPayload(payload));

  for (int i = 0; i < 10; i++) {
    auto get_irq_flg = nrf_->GetIRQFlags();
    ON_ERROR_RETURN(get_irq_flg.first);
    if (get_irq_flg.second & ((1U << 5) | (1U << 4))) {
      break;
    }
  }
  ON_ERROR_RETURN(nrf_->InitRx());

  return types::DriverStatus::OK;
}

auto NRF24L01::GetDataPacket() const noexcept -> types::com_msg_frame {
  types::com_msg_frame rv;
  if (!(msg_buffer_->BufferIsEmpty())) {
    rv = msg_buffer_->GetData();
  }
  return rv;
}

auto NRF24L01::HandleRxIRQ() noexcept -> void {
  types::com_msg_frame payload(types::COM_MAX_FRAME_LENGTH);

  nrf_->GetIRQFlags();
  nrf_->GetRxPayload(payload);

  msg_buffer_->PutData(payload);
  // TODO: Error counter, falls was nicht klappt?
}

}  // namespace com
