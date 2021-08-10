#include "com_nrf24l01_core.hpp"

namespace com {

auto NRF24L01Core::InitTransceiver(std::uint8_t channel,
                                   DataRateSetting data_rate,
                                   RFPowerSetting rf_power,
                                   CRCEncodingScheme encoding_scheme) noexcept -> types::DriverStatus {
  if (is_initialized_) {
    return types::DriverStatus::OK;
  }
  SetPowerState(State::ENABLED);
  SetRFChannel(channel);
  SetDataRate(data_rate);
  EnableCRC();
  SetCRCEncodingScheme(encoding_scheme);
  SetRFOutputPower(rf_power);
  MaskInterruptOnIntPin(MaskeableInterrupts::MAX_NR_OF_RETRIES_REACHED);
  MaskInterruptOnIntPin(MaskeableInterrupts::TX_DATA_SENT);
  is_initialized_ = true;
  return types::DriverStatus::OK;
}

auto NRF24L01Core::InitTx() noexcept -> types::DriverStatus {
  ON_ERROR_RETURN(spi_protocol_->FlushTxBuffer());
  ON_ERROR_RETURN(spi_protocol_->FlushRxBuffer());
  ON_ERROR_RETURN(spi_protocol_->ReadAndClearIRQFlags().first);

  if (current_operation_mode_ == OperationMode::PRIM_TX) {
    return types::DriverStatus::OK;
  }

  ON_ERROR_RETURN(SetOperationMode(OperationMode::PRIM_TX));
  /* needed in final implementation
    SetTxAddress(tx_addr);
    SetRxAddress(DataPipe::data_pipe_0, tx_addr);
  */

  ON_ERROR_RETURN(EnableDataPipe(DataPipe::RX_PIPE_0));
  //EnableAutoAck(DataPipe::RX_PIPE_0);
  ON_ERROR_RETURN(ConfigAutoRetransmission(AutoRetransmissionDelay::ARD500US, AutoRetransmitCount::ARC0));

  return types::DriverStatus::OK;
}

auto NRF24L01Core::InitRx() noexcept -> types::DriverStatus {
  ON_ERROR_RETURN(spi_protocol_->FlushTxBuffer());
  ON_ERROR_RETURN(spi_protocol_->FlushRxBuffer());

  if (current_operation_mode_ == OperationMode::PRIM_RX) {
    return types::DriverStatus::OK;
  }

  ON_ERROR_RETURN(SetOperationMode(OperationMode::PRIM_RX));

  ON_ERROR_RETURN(EnableDataPipe(DataPipe::RX_PIPE_0));
  ON_ERROR_RETURN(EnableAutoAck(DataPipe::RX_PIPE_0));
  ON_ERROR_RETURN(SetRxPayloadSize(DataPipe::RX_PIPE_0, types::COM_MAX_FRAME_LENGTH));

  return types::DriverStatus::OK;
}

auto NRF24L01Core::SetRxPayloadSize(DataPipe pipe_no, std::size_t payload_size) const noexcept -> types::DriverStatus {
  return spi_protocol_->WriteRegister(reg::rx_pw_p0::REG_ADDR + static_cast<std::uint8_t>(pipe_no),
                                      static_cast<uint8_t>(payload_size));
}

auto NRF24L01Core::SetOperationMode(OperationMode mode) noexcept -> types::DriverStatus {
  auto get_config_register = spi_protocol_->ReadRegister(reg::config::REG_ADDR);
  if (get_config_register.first != types::DriverStatus::OK) {
    return get_config_register.first;
  }
  utilities::Byte config_register(get_config_register.second);

  if (mode == OperationMode::PRIM_TX) {
    config_register.ClearBit(reg::config::PRIM_RX);
    current_operation_mode_ = OperationMode::PRIM_TX;
  } else {
    config_register.SetBit(reg::config::PRIM_RX);
    current_operation_mode_ = OperationMode::PRIM_RX;
  }

  return spi_protocol_->WriteRegister(reg::config::REG_ADDR, config_register.Get());
}

auto NRF24L01Core::SetRFChannel(std::uint8_t channel) noexcept -> types::DriverStatus {
  return spi_protocol_->WriteRegister(reg::rf_ch::REG_ADDR, channel);
}

auto NRF24L01Core::SetDataRate(DataRateSetting data_rate) noexcept -> types::DriverStatus {
  auto get_config_register = spi_protocol_->ReadRegister(reg::rf_setup::REG_ADDR);
  if (get_config_register.first != types::DriverStatus::OK) {
    return get_config_register.first;
  }
  utilities::Byte config_register(get_config_register.second);

  if (data_rate == DataRateSetting::RF_DR_1MBPS) {
    config_register.ClearBit(reg::rf_setup::RF_DR);
  }
  if (data_rate == DataRateSetting::RF_DR_2MPBS) {
    config_register.SetBit(reg::rf_setup::RF_DR);
  }

  return spi_protocol_->WriteRegister(reg::rf_setup::REG_ADDR, config_register.Get());
}

auto NRF24L01Core::EnableCRC() noexcept -> types::DriverStatus {
  auto get_config_register = spi_protocol_->ReadRegister(reg::rf_setup::REG_ADDR);
  if (get_config_register.first != types::DriverStatus::OK) {
    return get_config_register.first;
  }
  utilities::Byte config_register(get_config_register.second);
  config_register.SetBit(reg::config::EN_CRC);

  return spi_protocol_->WriteRegister(reg::config::REG_ADDR, config_register.Get());
}

auto NRF24L01Core::SetCRCEncodingScheme(CRCEncodingScheme encoding_scheme) noexcept -> types::DriverStatus {
  auto get_config_register = spi_protocol_->ReadRegister(reg::rf_setup::REG_ADDR);
  if (get_config_register.first != types::DriverStatus::OK) {
    return get_config_register.first;
  }
  utilities::Byte config_register(get_config_register.second);

  if (encoding_scheme == CRCEncodingScheme::CRC_8BIT) {
    config_register.ClearBit(reg::config::CRCO);
  }

  if (encoding_scheme == CRCEncodingScheme::CRC_16BIT) {
    config_register.SetBit(reg::config::CRCO);
  }

  return spi_protocol_->WriteRegister(reg::config::REG_ADDR, config_register.Get());
}

auto NRF24L01Core::SetRFOutputPower(RFPowerSetting rf_power) noexcept -> types::DriverStatus {
  auto get_rf_setup_reg = spi_protocol_->ReadRegister(reg::rf_setup::REG_ADDR);
  if (get_rf_setup_reg.first != types::DriverStatus::OK) {
    return get_rf_setup_reg.first;
  }

  auto rf_setup_reg = get_rf_setup_reg.second;

  rf_setup_reg &= (0b11111001);
  rf_setup_reg |= static_cast<register_t>(static_cast<register_t>(rf_power) << reg::rf_setup::RF_PWR);

  return (spi_protocol_->WriteRegister(reg::rf_setup::REG_ADDR, rf_setup_reg));
}

auto NRF24L01Core::SetPowerState(State power_state) noexcept -> types::DriverStatus {
  auto get_config_register = spi_protocol_->ReadRegister(reg::rf_setup::REG_ADDR);
  if (get_config_register.first != types::DriverStatus::OK) {
    return get_config_register.first;
  }
  utilities::Byte config_register(get_config_register.second);
  if (power_state == State::ENABLED) {
    config_register.SetBit(reg::config::PWR_UP);
  }
  if (power_state == State::DISABLED) {
    config_register.ClearBit(reg::config::PWR_UP);
  }

  return (spi_protocol_->WriteRegister(reg::config::REG_ADDR, config_register.Get()));
}

auto NRF24L01Core::EnableDataPipe(DataPipe pipe_no) noexcept -> types::DriverStatus {
  auto get_en_rxaddr_reg = spi_protocol_->ReadRegister(reg::rf_setup::REG_ADDR);
  if (get_en_rxaddr_reg.first != types::DriverStatus::OK) {
    return get_en_rxaddr_reg.first;
  }
  utilities::Byte en_rxaddr_reg(get_en_rxaddr_reg.second);
  en_rxaddr_reg.SetBit(static_cast<uint8_t>(pipe_no));
  return (spi_protocol_->WriteRegister(reg::en_rxaddr::REG_ADDR, en_rxaddr_reg.Get()));
}

auto NRF24L01Core::DisableDataPipe(DataPipe pipe_no) noexcept -> types::DriverStatus {
  auto get_en_rxaddr_reg = spi_protocol_->ReadRegister(reg::rf_setup::REG_ADDR);
  if (get_en_rxaddr_reg.first != types::DriverStatus::OK) {
    return get_en_rxaddr_reg.first;
  }
  utilities::Byte en_rxaddr_reg(get_en_rxaddr_reg.second);
  en_rxaddr_reg.ClearBit(static_cast<uint8_t>(pipe_no));
  return (spi_protocol_->WriteRegister(reg::en_rxaddr::REG_ADDR, en_rxaddr_reg.Get()));
}

auto NRF24L01Core::EnableAutoAck(DataPipe pipe_no) noexcept -> types::DriverStatus {
  auto get_en_aa_reg = spi_protocol_->ReadRegister(reg::rf_setup::REG_ADDR);
  if (get_en_aa_reg.first != types::DriverStatus::OK) {
    return get_en_aa_reg.first;
  }
  utilities::Byte en_aa_reg(get_en_aa_reg.second);
  en_aa_reg.SetBit(static_cast<uint8_t>(pipe_no));
  return (spi_protocol_->WriteRegister(reg::en_aa::REG_ADDR, en_aa_reg.Get()));
}

auto NRF24L01Core::ConfigAutoRetransmission(AutoRetransmissionDelay delay, AutoRetransmitCount count) noexcept -> types::DriverStatus {
  auto get_setup_retr_reg = spi_protocol_->ReadRegister(reg::rf_setup::REG_ADDR);
  if (get_setup_retr_reg.first != types::DriverStatus::OK) {
    return get_setup_retr_reg.first;
  }
  utilities::Byte setup_retr_reg(get_setup_retr_reg.second);
  setup_retr_reg.SetLowNibble(static_cast<uint8_t>(count));
  setup_retr_reg.SetHighNibble(static_cast<uint8_t>(delay));
  return (spi_protocol_->WriteRegister(reg::setup_retr::REG_ADDR, setup_retr_reg.Get()));
}

auto NRF24L01Core::MaskInterruptOnIntPin(MaskeableInterrupts interrupt) -> types::DriverStatus {
  auto get_config_register = spi_protocol_->ReadRegister(reg::rf_setup::REG_ADDR);

  ON_ERROR_RETURN(get_config_register.first);

  utilities::Byte config_register(get_config_register.second);
  if (interrupt == MaskeableInterrupts::MAX_NR_OF_RETRIES_REACHED) {
    config_register.SetBit(reg::config::MASK_MAX_RT);
  }
  if (interrupt == MaskeableInterrupts::RX_DATA_READY) {
    config_register.SetBit(reg::config::MASK_RX_DR);
  }
  if (interrupt == MaskeableInterrupts::TX_DATA_SENT) {
    config_register.SetBit(reg::config::MASK_TX_DS);
  }
  return (spi_protocol_->WriteRegister(reg::config::REG_ADDR, config_register.Get()));
}

auto NRF24L01Core::SetPipeAddress(DataPipe pipe_no, data_pipe_address pipe_addr) noexcept -> types::DriverStatus {
  uint8_t register_addr = reg::rx_addr_p0::REG_ADDR + static_cast<std::uint8_t>(pipe_no);
  std::vector<std::uint8_t> multibyte_addr;
  std::uint8_t singlebyte_addr = 0;
  auto return_value = types::DriverStatus::INPUT_ERROR;

  switch (pipe_no) {
    case DataPipe::TX_PIPE:
    case DataPipe::RX_PIPE_0:
    case DataPipe::RX_PIPE_1:
      multibyte_addr.resize(addr_config::ADDR_WIDTH);
      std::copy(pipe_addr.begin(),
                pipe_addr.end(),
                multibyte_addr.begin());
      return_value = spi_protocol_->WriteRegister(register_addr, multibyte_addr);
      break;
    case DataPipe::RX_PIPE_2:
    case DataPipe::RX_PIPE_3:
    case DataPipe::RX_PIPE_4:
    case DataPipe::RX_PIPE_5:
      singlebyte_addr = pipe_addr[0];
      return_value = spi_protocol_->WriteRegister(register_addr, singlebyte_addr);
      break;
  }
  return return_value;
}

/*auto NRF24L01Core::GetPipeAddress(DataPipe pipe_no) noexcept -> data_pipe_address {
  uint8_t register_addr = reg::rx_addr_p0::REG_ADDR + static_cast<std::uint8_t>(pipe_no);
  data_pipe_address addr = {0};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> multibyte_addr;
  std::pair<types::DriverStatus, std::uint8_t> singlebyte_addr;

  switch (pipe_no) {
    case DataPipe::TX_PIPE:
    case DataPipe::RX_PIPE_0:
    case DataPipe::RX_PIPE_1:
      multibyte_addr = spi_protocol_->ReadRegister(register_addr, com::addr_config::ADDR_WIDTH);
      std::copy(multibyte_addr.second.begin(),
                multibyte_addr.second.end(),
                addr.begin());
      break;
    case DataPipe::RX_PIPE_2:
    case DataPipe::RX_PIPE_3:
    case DataPipe::RX_PIPE_4:
    case DataPipe::RX_PIPE_5:
      singlebyte_addr = spi_protocol_->ReadRegister(register_addr);
      addr.at(0) = singlebyte_addr.second;
      break;
  }
  return addr;
}*/

auto NRF24L01Core::SetTxPayload(std::vector<std::uint8_t> &payload) noexcept -> types::DriverStatus {
  return spi_protocol_->WritePayloadData(payload);
}

auto NRF24L01Core::GetRxPayload(std::vector<std::uint8_t> &payload) -> types::DriverStatus {
  return spi_protocol_->ReadPayloadData(payload);
}

auto NRF24L01Core::GetIRQFlags() noexcept -> std::pair<types::DriverStatus, std::uint8_t> {
  return spi_protocol_->ReadAndClearIRQFlags();
}

}  // namespace com