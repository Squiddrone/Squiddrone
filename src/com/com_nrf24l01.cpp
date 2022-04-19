#include "com_nrf24l01.hpp"

namespace com {

auto NRF24L01::PutDataPacket(types::PutDataPacketTarget target_id, types::ComDataPacket &packet) noexcept -> types::DriverStatus {
  auto return_value = types::DriverStatus::HAL_ERROR;

  if (packet.data.size() > types::COM_MAX_DATA_FIELD_LENGTH) {
    return types::DriverStatus::INPUT_ERROR;
  }
  if (packet.target != target_id) {
    return types::DriverStatus::INPUT_ERROR;
  }
  if (target_id > types::PutDataPacketTarget::TARGET_FALLBACK or target_id < types::PutDataPacketTarget::TARGET_FRONT) {
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
  types::com_frame payload(types::COM_MAX_FRAME_LENGTH);

  nrf_->GetIRQFlags();
  nrf_->GetRxPayload(payload);

  auto packet_type = static_cast<types::ComDataPacketType>(payload.at(types::OFFSET_TYPE));

  if (packet_type == types::ComDataPacketType::COM_CONFIG_PACKET) {
    HandleConfigPacket(payload);
    return;
  }

  HandleTelemetryPacket(payload);
}

auto NRF24L01::LookupComPartnerAddress(types::PutDataPacketTarget target_id) noexcept -> types::data_pipe_address {
  return partner_drone_address_.at(static_cast<std::size_t>(target_id));
}

auto NRF24L01::HandleTelemetryPacket(types::com_frame &msg_frame) -> types::DriverStatus {
  auto ret_val = msg_buffer_->PutData(msg_frame);
  if (ret_val != ComBufferError::COM_BUFFER_OK) {
    return types::DriverStatus::INPUT_ERROR;
  }
  return types::DriverStatus::OK;
}

auto NRF24L01::HandleConfigPacket(types::com_frame &msg_frame) -> types::DriverStatus {
  types::OtaConfigPacket config_packet;
  config_packet.Deserialize(msg_frame);

  if (config_packet.data.at(types::START_CONFIG_DATA_ID) == types::ID_CONFIG_ADDRESS) {
    auto new_address_data = config_packet.DecodeAddressConfigPacket(config_packet.data);
    if (new_address_data.first == types::PutDataPacketTarget::TARGET_SELF) {
      base_address_ = new_address_data.second;
      UpdateAddress();
    }
  }
  return types::DriverStatus::OK;
}

auto NRF24L01::NRFInit() noexcept -> types::DriverStatus {
  return nrf_->InitTransceiver(20, com::DataRateSetting::RF_DR_2MBPS, com::RFPowerSetting::RF_PWR_0DBM, com::CRCEncodingScheme::CRC_16BIT, base_address_);
}

auto NRF24L01::UpdateAddress() noexcept -> types::DriverStatus {
  ON_ERROR_RETURN(nrf_->SetPipeAddress(DataPipe::RX_PIPE_0, base_address_));
  return types::DriverStatus::OK;
}

}  // namespace com
