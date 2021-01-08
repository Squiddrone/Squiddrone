#include "com_nrf24l01.hpp"

namespace com {
auto NRF24L01::EnableTxMode() noexcept -> types::DriverStatus {
  utilities::Byte config_register(ReadRegister(reg::config::REG_ADDR));

  config_register.ClearBit(reg::config::PRIM_RX);

  return WriteRegister(reg::config::REG_ADDR, config_register.Get());
}

auto NRF24L01::EnableRxMode() noexcept -> types::DriverStatus {
  utilities::Byte config_register(ReadRegister(reg::config::REG_ADDR));

  config_register.SetBit(reg::config::PRIM_RX);

  return WriteRegister(reg::config::REG_ADDR, config_register.Get());
}

auto NRF24L01::SetRxAddress(DataPipe pipe_no, data_pipe_address rx_addr) const noexcept -> types::DriverStatus {
}

auto NRF24L01::GetDataPacket() const noexcept -> types::com_msg_frame {
  types::com_msg_frame rv;
  return rv;
}

auto NRF24L01::PutDataPacket(std::uint8_t target_id, types::com_msg_frame &payload) noexcept -> types::ComError {
  uint8_t fifo_status = ReadRegister(reg::fifo_status::REG_ADDR);
  auto retval = WriteRegister(reg::en_aa::REG_ADDR, 0x3F);
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
