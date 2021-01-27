#include "com_nrf24l01.hpp"

namespace com {
auto NRF24L01::SetOperationMode(OperationMode mode) noexcept -> types::DriverStatus {
  utilities::Byte config_register(ReadRegister(reg::config::REG_ADDR));

  if (mode == OperationMode::prim_rx) {
    config_register.ClearBit(reg::config::PRIM_RX);
  } else {
    config_register.SetBit(reg::config::PRIM_RX);
  }

  return WriteRegister(reg::config::REG_ADDR, config_register.Get());
}

auto NRF24L01::InitTx() noexcept -> types::DriverStatus {
  SetRFChannel(rf_config::rf_channel);
  SetDataRate(DataRateSetting::rf_dr_1mbps);
  SetCRCEncodingScheme(CRCEncodingScheme::crc_16bit);

  SetOperationMode(OperationMode::prim_tx);
  SetRFOutputPower(RFPowerSetting::rf_pwr_0dBm);

  /* needed in final implementation
    SetTxAddress(tx_addr);
    SetRxAddress(DataPipe::data_pipe_0, tx_addr);
  */

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

auto NRF24L01::SetRxAddress(DataPipe pipe_no, data_pipe_address rx_addr) const noexcept -> types::DriverStatus {
}

auto NRF24L01::GetDataPacket() const noexcept -> types::com_msg_frame {
  types::com_msg_frame rv;
  return rv;
}

auto NRF24L01::PutDataPacket(std::uint8_t target_id, types::com_msg_frame &payload) noexcept -> types::ComError {
  uint8_t fifo_status = ReadRegister(reg::fifo_status::REG_ADDR);

  InitTx();
  //SetPayloadData(payload);

  return types::ComError::COM_OK;
}

auto NRF24L01::ReadRegister(const std::uint8_t register_address) noexcept -> std::uint8_t {
  types::com_msg_frame mosi_data_buffer;
  types::com_msg_frame miso_data_buffer(2);
  mosi_data_buffer.push_back(instruction_word::R_REGISTER | register_address);

  spi_.Transfer(mosi_data_buffer, miso_data_buffer);

  return miso_data_buffer.at(1);
}

auto NRF24L01::WriteRegister(std::uint8_t register_address, std::uint8_t register_content) -> types::DriverStatus {
  types::com_msg_frame mosi_data_buffer;
  mosi_data_buffer.push_back(instruction_word::W_REGISTER | register_address);
  mosi_data_buffer.push_back(register_content);

  auto spi_ret_val = spi_.Write(mosi_data_buffer);

  return spi_ret_val;
}

auto NRF24L01::FlushTx() noexcept -> types::DriverStatus {
  types::com_msg_frame mosi_data_buffer;
  mosi_data_buffer.push_back(instruction_word::FLUSH_TX);

  auto spi_ret_val = spi_.Write(mosi_data_buffer);

  return spi_ret_val;
}

auto NRF24L01::FlushRx() noexcept -> types::DriverStatus {
  types::com_msg_frame mosi_data_buffer;
  mosi_data_buffer.push_back(instruction_word::FLUSH_RX);

  auto spi_ret_val = spi_.Write(mosi_data_buffer);

  return spi_ret_val;
}

}  // namespace com
