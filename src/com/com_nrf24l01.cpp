#include "com_nrf24l01.hpp"
#include "sleep.hpp"

namespace com {
auto NRF24L01::InitTransceiver(std::uint8_t channel,
                               DataRateSetting data_rate,
                               RFPowerSetting rf_power,
                               CRCEncodingScheme encoding_scheme) noexcept -> types::DriverStatus {
  if (is_initialized_) {
    return types::DriverStatus::OK;
  }
  SetPowerState(State::enabled);
  SetRFChannel(channel);
  SetDataRate(data_rate);
  EnableCRC();
  SetCRCEncodingScheme(encoding_scheme);
  SetRFOutputPower(rf_power);
  MaskInterruptOnIntPin(MaskeableInterrupts::max_nr_of_retries_reached);
  MaskInterruptOnIntPin(MaskeableInterrupts::tx_data_sent);
  is_initialized_ = true;
  return types::DriverStatus::OK;
}

auto NRF24L01::InitTx() noexcept -> types::DriverStatus {
  spi_protocol_->FlushTxBuffer();
  spi_protocol_->FlushRxBuffer();
  spi_protocol_->ReadAndClearIRQFlags();

  if (current_operation_mode_ == OperationMode::prim_tx) {
    return types::DriverStatus::OK;
  }

  SetOperationMode(OperationMode::prim_tx);
  /* needed in final implementation
    SetTxAddress(tx_addr);
    SetRxAddress(DataPipe::data_pipe_0, tx_addr);
  */

  EnableDataPipe(DataPipe::rx_pipe_0);
  //EnableAutoAck(DataPipe::rx_pipe_0);
  ConfigAutoRetransmission(AutoRetransmissionDelay::ard500us, AutoRetransmitCount::arc0);

  return types::DriverStatus::OK;
}

auto NRF24L01::SetRxPayloadSize(DataPipe pipe_no, std::size_t payload_size) const noexcept -> types::DriverStatus {
  return spi_protocol_->WriteRegister(reg::rx_pw_p0::REG_ADDR + static_cast<std::uint8_t>(pipe_no),
                                      static_cast<uint8_t>(payload_size));
}

auto NRF24L01::InitRx() noexcept -> types::DriverStatus {
  spi_protocol_->FlushTxBuffer();
  spi_protocol_->FlushRxBuffer();

  if (current_operation_mode_ == OperationMode::prim_rx) {
    return types::DriverStatus::OK;
  }

  SetOperationMode(OperationMode::prim_rx);

  EnableDataPipe(DataPipe::rx_pipe_0);
  EnableAutoAck(DataPipe::rx_pipe_0);
  SetRxPayloadSize(DataPipe::rx_pipe_0, 32);

  return types::DriverStatus::OK;
}

auto NRF24L01::SetOperationMode(OperationMode mode) noexcept -> types::DriverStatus {
  auto get_config_register = spi_protocol_->ReadRegister(reg::config::REG_ADDR);
  if (get_config_register.first != types::DriverStatus::OK) {
    return get_config_register.first;
  }
  utilities::Byte config_register(get_config_register.second);

  if (mode == OperationMode::prim_tx) {
    config_register.ClearBit(reg::config::PRIM_RX);
    current_operation_mode_ = OperationMode::prim_tx;
  } else {
    config_register.SetBit(reg::config::PRIM_RX);
    current_operation_mode_ = OperationMode::prim_rx;
  }

  return spi_protocol_->WriteRegister(reg::config::REG_ADDR, config_register.Get());
}

auto NRF24L01::SetRFChannel(std::uint8_t channel) noexcept -> types::DriverStatus {
  return spi_protocol_->WriteRegister(reg::rf_ch::REG_ADDR, channel);
}

auto NRF24L01::SetDataRate(DataRateSetting data_rate) noexcept -> types::DriverStatus {
  auto get_config_register = spi_protocol_->ReadRegister(reg::rf_setup::REG_ADDR);
  if (get_config_register.first != types::DriverStatus::OK) {
    return get_config_register.first;
  }
  utilities::Byte config_register(get_config_register.second);

  if (data_rate == DataRateSetting::rf_dr_1mbps) {
    config_register.ClearBit(reg::rf_setup::RF_DR);
  }
  if (data_rate == DataRateSetting::rf_dr_2mbps) {
    config_register.SetBit(reg::rf_setup::RF_DR);
  }

  return spi_protocol_->WriteRegister(reg::rf_setup::REG_ADDR, config_register.Get());
}

auto NRF24L01::EnableCRC() noexcept -> types::DriverStatus {
  auto get_config_register = spi_protocol_->ReadRegister(reg::rf_setup::REG_ADDR);
  if (get_config_register.first != types::DriverStatus::OK) {
    return get_config_register.first;
  }
  utilities::Byte config_register(get_config_register.second);
  config_register.SetBit(reg::config::EN_CRC);

  return spi_protocol_->WriteRegister(reg::config::REG_ADDR, config_register.Get());
}

auto NRF24L01::SetCRCEncodingScheme(CRCEncodingScheme encoding_scheme) noexcept -> types::DriverStatus {
  auto get_config_register = spi_protocol_->ReadRegister(reg::rf_setup::REG_ADDR);
  if (get_config_register.first != types::DriverStatus::OK) {
    return get_config_register.first;
  }
  utilities::Byte config_register(get_config_register.second);
  ;

  if (encoding_scheme == CRCEncodingScheme::crc_8bit) {
    config_register.ClearBit(reg::config::CRCO);
  }
  if (encoding_scheme == CRCEncodingScheme::crc_16bit) {
    config_register.SetBit(reg::config::CRCO);
  }

  return spi_protocol_->WriteRegister(reg::config::REG_ADDR, config_register.Get());
}

auto NRF24L01::SetRFOutputPower(RFPowerSetting rf_power) noexcept -> types::DriverStatus {
  auto get_rf_setup_reg = spi_protocol_->ReadRegister(reg::rf_setup::REG_ADDR);
  if (get_rf_setup_reg.first != types::DriverStatus::OK) {
    return get_rf_setup_reg.first;
  }

  auto rf_setup_reg = get_rf_setup_reg.second;

  rf_setup_reg &= (0b11111001);
  rf_setup_reg |= static_cast<register_t>(static_cast<register_t>(rf_power) << reg::rf_setup::RF_PWR);

  return (spi_protocol_->WriteRegister(reg::rf_setup::REG_ADDR, rf_setup_reg));
}

auto NRF24L01::SetPowerState(State power_state) noexcept -> types::DriverStatus {
  auto get_config_register = spi_protocol_->ReadRegister(reg::rf_setup::REG_ADDR);
  if (get_config_register.first != types::DriverStatus::OK) {
    return get_config_register.first;
  }
  utilities::Byte config_register(get_config_register.second);
  if (power_state == State::enabled) {
    config_register.SetBit(reg::config::PWR_UP);
  }
  if (power_state == State::disabled) {
    config_register.ClearBit(reg::config::PWR_UP);
  }

  return (spi_protocol_->WriteRegister(reg::config::REG_ADDR, config_register.Get()));
}

auto NRF24L01::EnableDataPipe(DataPipe pipe_no) noexcept -> types::DriverStatus {
  auto get_en_rxaddr_reg = spi_protocol_->ReadRegister(reg::rf_setup::REG_ADDR);
  if (get_en_rxaddr_reg.first != types::DriverStatus::OK) {
    return get_en_rxaddr_reg.first;
  }
  utilities::Byte en_rxaddr_reg(get_en_rxaddr_reg.second);
  en_rxaddr_reg.SetBit(static_cast<uint8_t>(pipe_no));
  return (spi_protocol_->WriteRegister(reg::en_rxaddr::REG_ADDR, en_rxaddr_reg.Get()));
}

auto NRF24L01::EnableAutoAck(DataPipe pipe_no) noexcept -> types::DriverStatus {
  auto get_en_aa_reg = spi_protocol_->ReadRegister(reg::rf_setup::REG_ADDR);
  if (get_en_aa_reg.first != types::DriverStatus::OK) {
    return get_en_aa_reg.first;
  }
  utilities::Byte en_aa_reg(get_en_aa_reg.second);
  en_aa_reg.SetBit(static_cast<uint8_t>(pipe_no));
  return (spi_protocol_->WriteRegister(reg::en_aa::REG_ADDR, en_aa_reg.Get()));
}

auto NRF24L01::ConfigAutoRetransmission(AutoRetransmissionDelay delay, AutoRetransmitCount count) noexcept -> types::DriverStatus {
  auto get_setup_retr_reg = spi_protocol_->ReadRegister(reg::rf_setup::REG_ADDR);
  if (get_setup_retr_reg.first != types::DriverStatus::OK) {
    return get_setup_retr_reg.first;
  }
  utilities::Byte setup_retr_reg(get_setup_retr_reg.second);
  setup_retr_reg.SetLowNibble(static_cast<uint8_t>(count));
  setup_retr_reg.SetHighNibble(static_cast<uint8_t>(delay));
  return (spi_protocol_->WriteRegister(reg::setup_retr::REG_ADDR, setup_retr_reg.Get()));
}

auto NRF24L01::SetRxAddress(DataPipe pipe_no, data_pipe_address rx_addr) const noexcept -> types::DriverStatus {
  return types::DriverStatus::OK;
}

auto NRF24L01::MaskInterruptOnIntPin(MaskeableInterrupts interrupt) -> types::DriverStatus {
  auto get_config_register = spi_protocol_->ReadRegister(reg::rf_setup::REG_ADDR);
  if (get_config_register.first != types::DriverStatus::OK) {
    return get_config_register.first;
  }
  utilities::Byte config_register(get_config_register.second);
  if (interrupt == MaskeableInterrupts::max_nr_of_retries_reached) {
    config_register.SetBit(reg::config::MASK_MAX_RT);
  }
  if (interrupt == MaskeableInterrupts::rx_data_ready) {
    config_register.SetBit(reg::config::MASK_RX_DR);
  }
  if (interrupt == MaskeableInterrupts::tx_data_sent) {
    config_register.SetBit(reg::config::MASK_TX_DS);
  }
  return (spi_protocol_->WriteRegister(reg::config::REG_ADDR, config_register.Get()));
}

auto NRF24L01::GetPipeAddress(DataPipe pipe_no) noexcept -> data_pipe_address {
  uint8_t register_addr = reg::rx_addr_p0::REG_ADDR + static_cast<std::uint8_t>(pipe_no);
  data_pipe_address addr = {0};
  uint8_t counter = 0;
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> get_miso_data;

  switch (pipe_no) {
    case DataPipe::tx_pipe:
    case DataPipe::rx_pipe_0:
    case DataPipe::rx_pipe_1:
      get_miso_data = spi_protocol_->ReadRegister(register_addr, 5);
      for (auto miso_data_byte : get_miso_data.second) {
        addr.at(counter) = miso_data_byte;
        counter++;
      }
      break;
    case DataPipe::rx_pipe_2:
    case DataPipe::rx_pipe_3:
    case DataPipe::rx_pipe_4:
    case DataPipe::rx_pipe_5:
      //addr.at(0) = spi_protocol_->ReadRegister(register_addr);
      break;
  }
  return addr;
}

auto NRF24L01::GetDataPacket() const noexcept -> types::com_msg_frame {
  types::com_msg_frame rv;
  return rv;
}

auto NRF24L01::PutDataPacket(std::uint8_t target_id, types::com_msg_frame &payload) noexcept -> types::ComError {
  InitTransceiver(20, DataRateSetting::rf_dr_1mbps, RFPowerSetting::rf_pwr_0dBm, CRCEncodingScheme::crc_16bit);
  InitTx();
  spi_protocol_->WriteRegister(0x1d, 0);

  spi_protocol_->WritePayloadData(payload);

  for (int i = 0; i < 10; i++) {
    auto get_irq_flg = spi_protocol_->ReadAndClearIRQFlags();
    if (get_irq_flg.second & ((1U << 5) | (1U << 4))) break;
    utilities::Sleep(1);
  }

  return types::ComError::COM_OK;
}

auto NRF24L01::HandleRxIRQ() -> void {
  spi_protocol_->ReadAndClearIRQFlags();
}

}  // namespace com
