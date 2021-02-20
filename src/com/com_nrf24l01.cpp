#include "com_nrf24l01.hpp"

namespace com {
auto NRF24L01::InitTransceiver(std::uint8_t channel,
                               DataRateSetting data_rate,
                               RFPowerSetting rf_power,
                               CRCEncodingScheme encoding_scheme) noexcept -> types::DriverStatus {
  SetRFChannel(channel);
  SetDataRate(data_rate);
  EnableCRC();
  SetCRCEncodingScheme(encoding_scheme);
  SetRFOutputPower(rf_power);
}

auto NRF24L01::InitTx() noexcept -> types::DriverStatus {
  spi_protocol_.FlushTxBuffer();
  spi_protocol_.FlushRxBuffer();

  SetOperationMode(OperationMode::prim_tx);
  /* needed in final implementation
    SetTxAddress(tx_addr);
    SetRxAddress(DataPipe::data_pipe_0, tx_addr);
  */

  EnableDataPipe(DataPipe::rx_pipe_0);
  EnableAutoAck(DataPipe::rx_pipe_0);
  ConfigAutoRetransmission(AutoRetransmissionDelay::ard500us, AutoRetransmitCount::arc1);

  return types::DriverStatus::OK;
}

auto NRF24L01::SetOperationMode(OperationMode mode) noexcept -> types::DriverStatus {
  utilities::Byte config_register(spi_protocol_.ReadRegister(reg::config::REG_ADDR));

  if (mode == OperationMode::prim_rx) {
    config_register.SetBit(reg::config::PRIM_RX);
  } else {
    config_register.ClearBit(reg::config::PRIM_RX);
  }

  return spi_protocol_.WriteRegister(reg::config::REG_ADDR, config_register.Get());
}

auto NRF24L01::SetRFChannel(std::uint8_t channel) noexcept -> types::DriverStatus {
  return spi_protocol_.WriteRegister(reg::rf_ch::REG_ADDR, channel);
}

auto NRF24L01::SetDataRate(DataRateSetting data_rate) noexcept -> types::DriverStatus {
  utilities::Byte config_register(spi_protocol_.ReadRegister(reg::rf_setup::REG_ADDR));

  if (data_rate == DataRateSetting::rf_dr_1mbps) {
    config_register.ClearBit(reg::rf_setup::RF_DR);
  }
  if (data_rate == DataRateSetting::rf_dr_2mbps) {
    config_register.SetBit(reg::rf_setup::RF_DR);
  }

  return spi_protocol_.WriteRegister(reg::rf_setup::REG_ADDR, config_register.Get());
}

auto NRF24L01::EnableCRC() noexcept -> types::DriverStatus {
  utilities::Byte config_register(spi_protocol_.ReadRegister(reg::config::REG_ADDR));
  config_register.SetBit(reg::config::EN_CRC);

  return spi_protocol_.WriteRegister(reg::config::REG_ADDR, config_register.Get());
}

auto NRF24L01::SetCRCEncodingScheme(CRCEncodingScheme encoding_scheme) noexcept -> types::DriverStatus {
  utilities::Byte config_register(spi_protocol_.ReadRegister(reg::config::REG_ADDR));

  if (encoding_scheme == CRCEncodingScheme::crc_8bit) {
    config_register.ClearBit(reg::config::CRCO);
  }
  if (encoding_scheme == CRCEncodingScheme::crc_16bit) {
    config_register.SetBit(reg::config::CRCO);
  }

  return spi_protocol_.WriteRegister(reg::config::REG_ADDR, config_register.Get());
}

auto NRF24L01::SetRFOutputPower(RFPowerSetting rf_power) noexcept -> types::DriverStatus {
  register_t rf_setup_reg = spi_protocol_.ReadRegister(reg::rf_setup::REG_ADDR);

  rf_setup_reg &= (0b11111001);
  rf_setup_reg |= static_cast<register_t>(static_cast<register_t>(rf_power) << reg::rf_setup::RF_PWR);

  return (spi_protocol_.WriteRegister(reg::rf_setup::REG_ADDR, rf_setup_reg));
}

auto NRF24L01::SetPowerState(State power_state) noexcept -> types::DriverStatus {
  utilities::Byte config_reg(spi_protocol_.ReadRegister(reg::config::REG_ADDR));
  if (power_state == State::enabled) {
    config_reg.SetBit(reg::config::PWR_UP);
  }
  if (power_state == State::disabled) {
    config_reg.ClearBit(reg::config::PWR_UP);
  }

  return (spi_protocol_.WriteRegister(reg::config::REG_ADDR, config_reg.Get()));
}

auto NRF24L01::EnableDataPipe(DataPipe pipe_no) noexcept -> types::DriverStatus {
  utilities::Byte en_rxaddr_reg(spi_protocol_.ReadRegister(reg::en_rxaddr::REG_ADDR));
  en_rxaddr_reg.SetBit(static_cast<uint8_t>(pipe_no));
  return (spi_protocol_.WriteRegister(reg::en_rxaddr::REG_ADDR, en_rxaddr_reg.Get()));
}

auto NRF24L01::EnableAutoAck(DataPipe pipe_no) noexcept -> types::DriverStatus {
  utilities::Byte en_aa_reg(spi_protocol_.ReadRegister(reg::en_aa::REG_ADDR));
  en_aa_reg.SetBit(static_cast<uint8_t>(pipe_no));
  return (spi_protocol_.WriteRegister(reg::en_aa::REG_ADDR, en_aa_reg.Get()));
}

auto NRF24L01::ConfigAutoRetransmission(AutoRetransmissionDelay delay, AutoRetransmitCount count) noexcept -> types::DriverStatus {
  utilities::Byte setup_retr_reg(spi_protocol_.ReadRegister(reg::setup_retr::REG_ADDR));
  setup_retr_reg.SetLowNibble(static_cast<uint8_t>(count));
  setup_retr_reg.SetHighNibble(static_cast<uint8_t>(delay));
  return (spi_protocol_.WriteRegister(reg::setup_retr::REG_ADDR, setup_retr_reg.Get()));
}

auto NRF24L01::SetRxAddress(DataPipe pipe_no, data_pipe_address rx_addr) const noexcept -> types::DriverStatus {
}

auto NRF24L01::GetPipeAddress(DataPipe pipe_no) noexcept -> data_pipe_address {
  std::vector<uint8_t> miso_data;
  uint8_t register_addr = reg::rx_addr_p0::REG_ADDR + static_cast<std::uint8_t>(pipe_no);
  data_pipe_address addr = {0};
  uint8_t counter = 0;

  switch (pipe_no) {
    case DataPipe::tx_pipe:
    case DataPipe::rx_pipe_0:
    case DataPipe::rx_pipe_1:
      miso_data = spi_protocol_.ReadRegister(register_addr, 5);
      for (auto n : miso_data) {
        addr.at(counter) = n;
        counter++;
      }
      break;
    case DataPipe::rx_pipe_2:
    case DataPipe::rx_pipe_3:
    case DataPipe::rx_pipe_4:
    case DataPipe::rx_pipe_5:
      addr.at(0) = spi_protocol_.ReadRegister(register_addr);
      break;
  }
  return addr;
}

auto NRF24L01::GetDataPacket() const noexcept -> types::com_msg_frame {
  types::com_msg_frame rv;
  return rv;
}

auto NRF24L01::PutDataPacket(std::uint8_t target_id, types::com_msg_frame &payload) noexcept -> types::ComError {
  register_t irq_flg = 0;

  SetPowerState(State::enabled);
  HAL_Delay(1);
  InitTx();
  spi_protocol_.WriteRegister(0x1d, 0);

  spi_protocol_.WritePayloadData(payload);
  irq_flg = spi_protocol_.ReadAndClearIRQFlags();

  for (int i = 0; i < 10; i++) {
    irq_flg = spi_protocol_.ReadAndClearIRQFlags();
    if (irq_flg & ((1U << 5) | (1U << 4))) break;
  }
  SetPowerState(State::disabled);

  return types::ComError::COM_OK;
}

}  // namespace com
