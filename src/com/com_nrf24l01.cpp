#include "com_nrf24l01.hpp"

namespace com {
auto NRF24L01::SetOperationMode(OperationMode mode) noexcept -> types::DriverStatus {
  utilities::Byte config_register(ReadRegister(reg::config::REG_ADDR));

  if (mode == OperationMode::prim_rx) {
    config_register.SetBit(reg::config::PRIM_RX);
  } else {
    config_register.ClearBit(reg::config::PRIM_RX);
  }

  return WriteRegister(reg::config::REG_ADDR, config_register.Get());
}

auto NRF24L01::InitTx() noexcept -> types::DriverStatus {
  SetRFChannel(rf_config::rf_channel);
  SetDataRate(DataRateSetting::rf_dr_1mbps);
  EnableCRC();
  SetCRCEncodingScheme(CRCEncodingScheme::crc_16bit);
  SetOperationMode(OperationMode::prim_tx);
  /* needed in final implementation
    SetTxAddress(tx_addr);
    SetRxAddress(DataPipe::data_pipe_0, tx_addr);
  */
  SetRFOutputPower(RFPowerSetting::rf_pwr_0dBm);

  // disable retransmission?
  ConfigAutoRetransmission(AutoRetransmissionDelay::ard250us, AutoRetransmitCount::arc0);

  EnableDataPipe(DataPipe::data_pipe_0);
  EnableAutoAck(DataPipe::data_pipe_0);

  return types::DriverStatus::OK;
}

auto NRF24L01::SetRFChannel(std::uint8_t channel) noexcept -> types::DriverStatus {
  return WriteRegister(reg::rf_ch::REG_ADDR, channel);
}

auto NRF24L01::SetDataRate(DataRateSetting data_rate) noexcept -> types::DriverStatus {
  utilities::Byte config_register(ReadRegister(reg::rf_setup::REG_ADDR));

  if (data_rate == DataRateSetting::rf_dr_1mbps) {
    config_register.ClearBit(reg::rf_setup::RF_DR);
  }
  if (data_rate == DataRateSetting::rf_dr_2mbps) {
    config_register.SetBit(reg::rf_setup::RF_DR);
  }

  return WriteRegister(reg::rf_setup::REG_ADDR, config_register.Get());
}

auto NRF24L01::EnableCRC() noexcept -> types::DriverStatus {
  utilities::Byte config_register(ReadRegister(reg::config::REG_ADDR));
  config_register.SetBit(reg::config::EN_CRC);

  return WriteRegister(reg::config::REG_ADDR, config_register.Get());
}

auto NRF24L01::SetCRCEncodingScheme(CRCEncodingScheme encoding_scheme) noexcept -> types::DriverStatus {
  utilities::Byte config_register(ReadRegister(reg::config::REG_ADDR));

  if (encoding_scheme == CRCEncodingScheme::crc_8bit) {
    config_register.ClearBit(reg::config::CRCO);
  }
  if (encoding_scheme == CRCEncodingScheme::crc_16bit) {
    config_register.SetBit(reg::config::CRCO);
  }

  return WriteRegister(reg::config::REG_ADDR, config_register.Get());
}

auto NRF24L01::SetRFOutputPower(RFPowerSetting rf_power) noexcept -> types::DriverStatus {
  register_t rf_setup_reg = ReadRegister(reg::rf_setup::REG_ADDR);

  rf_setup_reg &= (0b11111001);
  rf_setup_reg |= static_cast<register_t>(static_cast<register_t>(rf_power) << reg::rf_setup::RF_PWR);

  return (WriteRegister(reg::rf_setup::REG_ADDR, rf_setup_reg));
}

auto NRF24L01::SetPowerState(State power_state) noexcept -> types::DriverStatus {
  utilities::Byte config_reg(ReadRegister(reg::config::REG_ADDR));
  if (power_state == State::enabled) {
    config_reg.SetBit(reg::config::PWR_UP);
  }
  if (power_state == State::disabled) {
    config_reg.ClearBit(reg::config::PWR_UP);
  }

  return (WriteRegister(reg::config::REG_ADDR, config_reg.Get()));
}

auto NRF24L01::EnableDataPipe(DataPipe pipe_no) noexcept -> types::DriverStatus {
  utilities::Byte en_rxaddr_reg(ReadRegister(reg::en_rxaddr::REG_ADDR));
  en_rxaddr_reg.SetBit(static_cast<uint8_t>(pipe_no));
  return (WriteRegister(reg::en_rxaddr::REG_ADDR, en_rxaddr_reg.Get()));
}

auto NRF24L01::EnableAutoAck(DataPipe pipe_no) noexcept -> types::DriverStatus {
  utilities::Byte en_aa_reg(ReadRegister(reg::en_aa::REG_ADDR));
  en_aa_reg.SetBit(static_cast<uint8_t>(pipe_no));
  return (WriteRegister(reg::en_aa::REG_ADDR, en_aa_reg.Get()));
}

auto NRF24L01::ConfigAutoRetransmission(AutoRetransmissionDelay delay, AutoRetransmitCount count) noexcept -> types::DriverStatus {
  utilities::Byte setup_retr_reg(ReadRegister(reg::setup_retr::REG_ADDR));
  setup_retr_reg.SetLowNibble(static_cast<uint8_t>(count));
  setup_retr_reg.SetHighNibble(static_cast<uint8_t>(delay));
  return (WriteRegister(reg::setup_retr::REG_ADDR, setup_retr_reg.Get()));
}

auto NRF24L01::SetRxAddress(DataPipe pipe_no, data_pipe_address rx_addr) const noexcept -> types::DriverStatus {
}

auto NRF24L01::GetRxAddress(DataPipe pipe_no) noexcept -> data_pipe_address {
  std::vector<uint8_t> miso_data;
  uint8_t register_addr = reg::rx_addr_p0::REG_ADDR + static_cast<uint8_t>(pipe_no);
  data_pipe_address addr = {0};
  uint8_t counter = 0;

  switch (pipe_no) {
    case DataPipe::data_pipe_0:
    case DataPipe::data_pipe_1:
      miso_data = ReadRegister(register_addr, 5);
      // implementiere multibyte read, aber heut nimmer...
      for (auto n : miso_data) {
        addr.at(counter) = n;
        counter++;
      }
      break;
    case DataPipe::data_pipe_2:
    case DataPipe::data_pipe_3:
    case DataPipe::data_pipe_4:
    case DataPipe::data_pipe_5:
      addr.at(0) = ReadRegister(register_addr);
      break;
  }
}

auto NRF24L01::GetDataPacket() const noexcept -> types::com_msg_frame {
  types::com_msg_frame rv;
  return rv;
}

auto NRF24L01::PutDataPacket(std::uint8_t target_id, types::com_msg_frame &payload) noexcept -> types::ComError {
  register_t irq_flg = 0;

  auto rv = SetPowerState(State::enabled);
  rv = FlushTx();
  ReadAndClearIRQFlags();
  rv = InitTx();
  rv = WritePayloadData(payload);
  GetRxAddress(DataPipe::data_pipe_0);

  for (int i = 0; i < 10; i++) {
    irq_flg = ReadAndClearIRQFlags();
    if (irq_flg & ((1U << 5) | (1U << 4))) break;
    HAL_Delay(1);
  }

  return types::ComError::COM_OK;
}

auto NRF24L01::ReadRegister(const std::uint8_t register_address) noexcept -> std::uint8_t {
  std::vector<std::uint8_t> mosi_data_buffer;
  std::vector<std::uint8_t> miso_data_buffer(2);
  mosi_data_buffer.push_back(instruction_word::R_REGISTER | register_address);

  spi_.Transfer(mosi_data_buffer, miso_data_buffer);

  return miso_data_buffer.at(1);
}

auto NRF24L01::ReadRegister(const std::uint8_t register_address, std::uint8_t length) noexcept -> std::vector<uint8_t> {
  std::vector<std::uint8_t> mosi_data_buffer;
  std::vector<std::uint8_t> miso_data_buffer(length + 1);
  mosi_data_buffer.push_back(instruction_word::R_REGISTER | register_address);

  spi_.Transfer(mosi_data_buffer, miso_data_buffer);
  miso_data_buffer.erase(miso_data_buffer.begin());

  return miso_data_buffer;
}

auto NRF24L01::WriteRegister(std::uint8_t register_address, std::uint8_t register_content) -> types::DriverStatus {
  std::vector<std::uint8_t> mosi_data_buffer;
  mosi_data_buffer.push_back(instruction_word::W_REGISTER | register_address);
  mosi_data_buffer.push_back(register_content);

  auto spi_ret_val = spi_.Write(mosi_data_buffer);

  return spi_ret_val;
}

auto NRF24L01::WritePayloadData(types::com_msg_frame &payload) noexcept -> types::DriverStatus {
  types::com_msg_frame mosi_data_buffer;
  mosi_data_buffer = payload;
  mosi_data_buffer.insert(mosi_data_buffer.begin(), instruction_word::W_TX_PAYLOAD);

  auto spi_ret_val = spi_.Write(mosi_data_buffer);

  return spi_ret_val;
}

auto NRF24L01::FlushTx() noexcept -> types::DriverStatus {
  std::vector<std::uint8_t> mosi_data_buffer;
  mosi_data_buffer.push_back(instruction_word::FLUSH_TX);

  auto spi_ret_val = spi_.Write(mosi_data_buffer);

  return spi_ret_val;
}

auto NRF24L01::FlushRx() noexcept -> types::DriverStatus {
  std::vector<std::uint8_t> mosi_data_buffer;
  mosi_data_buffer.push_back(instruction_word::FLUSH_RX);

  auto spi_ret_val = spi_.Write(mosi_data_buffer);

  return spi_ret_val;
}

auto NRF24L01::ReadAndClearIRQFlags() -> register_t {
  std::vector<std::uint8_t> mosi_data;
  std::vector<std::uint8_t> miso_data(2);

  utilities::Byte construct_byte(0);

  construct_byte.SetBit(reg::status::MAX_RT);
  construct_byte.SetBit(reg::status::TX_DS);
  construct_byte.SetBit(reg::status::RX_DR);

  mosi_data.push_back(instruction_word::W_REGISTER | reg::status::REG_ADDR);
  mosi_data.push_back(construct_byte.Get());
  spi_.Transfer(mosi_data, miso_data);

  return miso_data.at(0);
}

}  // namespace com
