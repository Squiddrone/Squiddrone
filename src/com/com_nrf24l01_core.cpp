#include "com_nrf24l01_core.hpp"

namespace com {

auto NRF24L01Core::InitTransceiver(std::uint8_t channel,
                                   DataRateSetting data_rate,
                                   RFPowerSetting rf_power,
                                   CRCEncodingScheme encoding_scheme,
                                   types::data_pipe_address base_address) noexcept -> types::DriverStatus {
  if (is_initialized_) {
    return types::DriverStatus::OK;
  }
  ON_ERROR_RETURN(SetChipEnable(State::DISABLED));
  ON_ERROR_RETURN(SetPowerState(State::DISABLED));
  utilities::Sleep(1);
  ON_ERROR_RETURN(SetPowerState(State::ENABLED));
  ON_ERROR_RETURN(SetChipEnable(State::ENABLED));
  utilities::Sleep(2);
  ON_ERROR_RETURN(SetRFChannel(channel));
  ON_ERROR_RETURN(SetDataRate(data_rate));
  ON_ERROR_RETURN(EnableCRC());
  ON_ERROR_RETURN(SetCRCEncodingScheme(encoding_scheme));
  ON_ERROR_RETURN(SetRFOutputPower(rf_power));
  ON_ERROR_RETURN(MaskInterruptOnIntPin(MaskeableInterrupts::MAX_NR_OF_RETRIES_REACHED));
  ON_ERROR_RETURN(MaskInterruptOnIntPin(MaskeableInterrupts::TX_DATA_SENT));
  ON_ERROR_RETURN(InitRx(base_address));
  is_initialized_ = true;

  return types::DriverStatus::OK;
}

auto NRF24L01Core::InitTx(types::data_pipe_address tx_target_address) noexcept -> types::DriverStatus {
  ON_ERROR_RETURN(SetChipEnable(State::DISABLED));

  ON_ERROR_RETURN(spi_protocol_->FlushTxBuffer());
  ON_ERROR_RETURN(spi_protocol_->FlushRxBuffer());

  ON_ERROR_RETURN(SetPipeAddress(DataPipe::TX_PIPE, tx_target_address));
  ON_ERROR_RETURN(SetPipeAddress(DataPipe::RX_PIPE_0, tx_target_address));

  if (current_operation_mode_ == OperationMode::PRIM_TX) {
    return types::DriverStatus::OK;
  }

  ON_ERROR_RETURN(SetOperationMode(OperationMode::PRIM_TX));

  ON_ERROR_RETURN(EnableDataPipe(DataPipe::RX_PIPE_0));
  ON_ERROR_RETURN(EnableAutoAck(DataPipe::RX_PIPE_0));

  ON_ERROR_RETURN(ConfigAutoRetransmission(AutoRetransmissionDelay::ARD500US, AutoRetransmitCount::ARC5));

  return types::DriverStatus::OK;
}

auto NRF24L01Core::InitRx(types::data_pipe_address base_address) noexcept -> types::DriverStatus {
  ON_ERROR_RETURN(spi_protocol_->FlushTxBuffer());
  ON_ERROR_RETURN(spi_protocol_->FlushRxBuffer());

  if (current_operation_mode_ == OperationMode::PRIM_RX) {
    return types::DriverStatus::OK;
  }

  ON_ERROR_RETURN(SetOperationMode(OperationMode::PRIM_RX));

  ON_ERROR_RETURN(SetPipeAddress(DataPipe::RX_PIPE_0, base_address));
  ON_ERROR_RETURN(EnableDataPipe(DataPipe::RX_PIPE_0));
  ON_ERROR_RETURN(EnableAutoAck(DataPipe::RX_PIPE_0));
  ON_ERROR_RETURN(SetRxPayloadSize(DataPipe::RX_PIPE_0, types::COM_MAX_FRAME_LENGTH));

  ON_ERROR_RETURN(SetChipEnable(State::ENABLED));

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
  if (data_rate == DataRateSetting::RF_DR_2MBPS) {
    config_register.SetBit(reg::rf_setup::RF_DR);
  }

  return spi_protocol_->WriteRegister(reg::rf_setup::REG_ADDR, config_register.Get());
}

auto NRF24L01Core::EnableCRC() noexcept -> types::DriverStatus {
  auto get_config_register = spi_protocol_->ReadRegister(reg::config::REG_ADDR);
  if (get_config_register.first != types::DriverStatus::OK) {
    return get_config_register.first;
  }
  utilities::Byte config_register(get_config_register.second);
  config_register.SetBit(reg::config::EN_CRC);

  return spi_protocol_->WriteRegister(reg::config::REG_ADDR, config_register.Get());
}

auto NRF24L01Core::SetCRCEncodingScheme(CRCEncodingScheme encoding_scheme) noexcept -> types::DriverStatus {
  auto get_config_register = spi_protocol_->ReadRegister(reg::config::REG_ADDR);
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

  static constexpr std::uint8_t reset_rf_setup_bits = 0b11111001;

  rf_setup_reg &= (reset_rf_setup_bits);
  rf_setup_reg |= static_cast<register_t>(static_cast<register_t>(rf_power) << reg::rf_setup::RF_PWR);

  return (spi_protocol_->WriteRegister(reg::rf_setup::REG_ADDR, rf_setup_reg));
}

auto NRF24L01Core::SetPowerState(State power_state) noexcept -> types::DriverStatus {
  auto get_config_register = spi_protocol_->ReadRegister(reg::config::REG_ADDR);
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
  auto get_en_rxaddr_reg = spi_protocol_->ReadRegister(reg::en_rxaddr::REG_ADDR);
  if (get_en_rxaddr_reg.first != types::DriverStatus::OK) {
    return get_en_rxaddr_reg.first;
  }
  utilities::Byte en_rxaddr_reg(get_en_rxaddr_reg.second);
  en_rxaddr_reg.SetBit(static_cast<uint8_t>(pipe_no));
  return (spi_protocol_->WriteRegister(reg::en_rxaddr::REG_ADDR, en_rxaddr_reg.Get()));
}

auto NRF24L01Core::DisableDataPipe(DataPipe pipe_no) noexcept -> types::DriverStatus {
  auto get_en_rxaddr_reg = spi_protocol_->ReadRegister(reg::en_rxaddr::REG_ADDR);
  if (get_en_rxaddr_reg.first != types::DriverStatus::OK) {
    return get_en_rxaddr_reg.first;
  }
  utilities::Byte en_rxaddr_reg(get_en_rxaddr_reg.second);
  en_rxaddr_reg.ClearBit(static_cast<uint8_t>(pipe_no));
  return (spi_protocol_->WriteRegister(reg::en_rxaddr::REG_ADDR, en_rxaddr_reg.Get()));
}

auto NRF24L01Core::EnableAutoAck(DataPipe pipe_no) noexcept -> types::DriverStatus {
  auto get_en_aa_reg = spi_protocol_->ReadRegister(reg::en_aa::REG_ADDR);
  if (get_en_aa_reg.first != types::DriverStatus::OK) {
    return get_en_aa_reg.first;
  }
  utilities::Byte en_aa_reg(get_en_aa_reg.second);
  en_aa_reg.SetBit(static_cast<uint8_t>(pipe_no));
  return (spi_protocol_->WriteRegister(reg::en_aa::REG_ADDR, en_aa_reg.Get()));
}

auto NRF24L01Core::ConfigAutoRetransmission(AutoRetransmissionDelay delay, AutoRetransmitCount count) noexcept -> types::DriverStatus {
  auto get_setup_retr_reg = spi_protocol_->ReadRegister(reg::setup_retr::REG_ADDR);
  if (get_setup_retr_reg.first != types::DriverStatus::OK) {
    return get_setup_retr_reg.first;
  }
  utilities::Byte setup_retr_reg(get_setup_retr_reg.second);
  setup_retr_reg.SetLowNibble(static_cast<uint8_t>(count));
  setup_retr_reg.SetHighNibble(static_cast<uint8_t>(delay));
  return (spi_protocol_->WriteRegister(reg::setup_retr::REG_ADDR, setup_retr_reg.Get()));
}

auto NRF24L01Core::MaskInterruptOnIntPin(MaskeableInterrupts interrupt) -> types::DriverStatus {
  auto get_config_register = spi_protocol_->ReadRegister(reg::config::REG_ADDR);

  ON_ERROR_RETURN(get_config_register.first);

  utilities::Byte config_register(get_config_register.second);
  config_register.SetBit(static_cast<std::uint8_t>(interrupt));

  return (spi_protocol_->WriteRegister(reg::config::REG_ADDR, config_register.Get()));
}

auto NRF24L01Core::SetPipeAddress(DataPipe pipe_no, types::data_pipe_address pipe_addr) noexcept -> types::DriverStatus {
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

auto NRF24L01Core::GetPipeAddress(DataPipe pipe_no) noexcept -> std::pair<types::DriverStatus, types::data_pipe_address> {
  uint8_t register_addr = reg::rx_addr_p0::REG_ADDR + static_cast<std::uint8_t>(pipe_no);
  types::data_pipe_address addr = {0};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> multibyte_addr;
  std::pair<types::DriverStatus, std::uint8_t> singlebyte_addr;
  types::DriverStatus return_value;

  switch (pipe_no) {
    case DataPipe::TX_PIPE:
    case DataPipe::RX_PIPE_0:
    case DataPipe::RX_PIPE_1:
      multibyte_addr = spi_protocol_->ReadRegister(register_addr, com::addr_config::ADDR_WIDTH);
      std::copy(multibyte_addr.second.begin(),
                multibyte_addr.second.end(),
                addr.begin());
      return_value = multibyte_addr.first;
      break;
    case DataPipe::RX_PIPE_2:
    case DataPipe::RX_PIPE_3:
    case DataPipe::RX_PIPE_4:
    case DataPipe::RX_PIPE_5:
      singlebyte_addr = spi_protocol_->ReadRegister(register_addr);
      addr.at(0) = singlebyte_addr.second;
      return_value = singlebyte_addr.first;
      break;
  }
  return {return_value, addr};
}

auto NRF24L01Core::SetTxPayload(std::vector<std::uint8_t>& payload) noexcept -> types::DriverStatus {
  return spi_protocol_->WritePayloadData(payload);
}

auto NRF24L01Core::GetRxPayload(std::vector<std::uint8_t>& payload) noexcept -> types::DriverStatus {
  return spi_protocol_->ReadPayloadData(payload);
}

auto NRF24L01Core::GetIRQFlags() noexcept -> std::pair<types::DriverStatus, std::uint8_t> {
  return spi_protocol_->ReadAndClearIRQFlags();
}

auto NRF24L01Core::SetAddressWidth(DataPipeAddressWidth addr_width) noexcept -> types::DriverStatus {
  return (spi_protocol_->WriteRegister(reg::setup_aw::REG_ADDR, static_cast<std::uint8_t>(addr_width)));
}

auto NRF24L01Core::SetChipEnable(State power_state) noexcept -> types::DriverStatus {
  GPIO_PinState gpio_state = GPIO_PIN_RESET;

  if (power_state == State::ENABLED) {
    gpio_state = GPIO_PIN_SET;
  }

  HAL_GPIO_WritePin(ENCOM_GPIO_Port, ENCOM_Pin, gpio_state);
  return types::DriverStatus::OK;
}

}  // namespace com
