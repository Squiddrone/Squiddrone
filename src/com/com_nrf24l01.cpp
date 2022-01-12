#include "com_nrf24l01.hpp"

namespace com {

auto NRF24L01::PutDataPacket(types::PutDataTarget target_id, types::ComDataPacket &packet) noexcept -> types::DriverStatus {
  auto return_value = types::DriverStatus::HAL_ERROR;

  if (packet.data.size() > types::COM_MAX_DATA_FIELD_LENGTH) {
    return types::DriverStatus::INPUT_ERROR;
  }
  if (packet.target != target_id) {
    return types::DriverStatus::INPUT_ERROR;
  }

  auto target_address = LookupComPartnerAddress(target_id);

  ON_ERROR_RETURN(nrf_->InitTx(target_address));

  auto payload = packet.Serialize();

  ON_ERROR_RETURN(nrf_->SetTxPayload(payload));
  ON_ERROR_RETURN(nrf_->GetIRQFlags().first);
  ON_ERROR_RETURN(nrf_->SetChipEnable(State::ENABLED));

  static constexpr int iterations_until_1ms = 10;

  for (int i = 0; i < iterations_until_1ms; i++) {
    auto get_irq_flg = nrf_->GetIRQFlags();
    ON_ERROR_RETURN(get_irq_flg.first);
    if (get_irq_flg.second & (1U << reg::status::TX_DS)) {
      return_value = types::DriverStatus::OK;
      break;
    }
    if (get_irq_flg.second & (1U << reg::status::MAX_RT)) {
      return_value = types::DriverStatus::TIMEOUT;
      break;
    }
  }

  ON_ERROR_RETURN(nrf_->SetChipEnable(State::DISABLED));
  ON_ERROR_RETURN(nrf_->InitRx(base_address_));

  return return_value;
}

auto NRF24L01::GetDataPacket() const noexcept -> types::ComDataPacket {
  types::ComDataPacket packet;
  if (!(msg_buffer_->BufferIsEmpty())) {
    packet.Deserialize(msg_buffer_->GetData());
  }
  return packet;
}

auto NRF24L01::HandleRxIRQ() noexcept -> void {
  types::com_msg_frame payload(types::COM_MAX_FRAME_LENGTH);

  nrf_->GetIRQFlags();
  nrf_->GetRxPayload(payload);

  auto packet_type = static_cast<types::ComPacketType>(payload.at(types::OFFSET_TYPE));

  if (packet_type == types::ComPacketType::COM_CONFIG_PACKET) {
    HandleConfigPacket(payload);
    return;
  }

  HandleTelemetryPacket(payload);
}

auto NRF24L01::LookupComPartnerAddress(types::PutDataTarget target_id) noexcept -> types::data_pipe_address {
  return partner_drone_address_.at(static_cast<std::size_t>(target_id));
}

auto NRF24L01::HandleTelemetryPacket(types::com_msg_frame &msg_frame) -> types::DriverStatus {
  auto ret_val = msg_buffer_->PutData(msg_frame);
  if (ret_val != ComBufferError::COM_BUFFER_OK) {
    return types::DriverStatus::INPUT_ERROR;
  }
  return types::DriverStatus::OK;
}

auto NRF24L01::HandleConfigPacket(types::com_msg_frame &msg_frame) -> types::DriverStatus {
  nrf_->SetPipeAddress(DataPipe::RX_PIPE_0, {0, 0, 0, 0, 0});
  return types::DriverStatus::OK;
}

auto NRF24L01::NRFInit() noexcept -> types::DriverStatus {
  return nrf_->InitTransceiver(20, com::DataRateSetting::RF_DR_2MBPS, com::RFPowerSetting::RF_PWR_0DBM, com::CRCEncodingScheme::CRC_16BIT, base_address_);
}

}  // namespace com
