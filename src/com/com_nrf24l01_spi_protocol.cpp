#include "com_nrf24l01_spi_protocol.hpp"
#include "com_nrf24l01_reg.hpp"

namespace com {

auto NRF24L01SpiProtocol::ReadRegister(const std::uint8_t register_address) noexcept -> std::pair<types::DriverStatus, std::uint8_t> {
  constexpr auto position_in_buffer = 1;
  constexpr auto spi_transfer_length = 2;
  std::vector<std::uint8_t> mosi_data_buffer;
  std::vector<std::uint8_t> miso_data_buffer(spi_transfer_length);
  mosi_data_buffer.push_back(instruction_word::R_REGISTER | register_address);

  auto spi_ret_val = spi_->Transfer(mosi_data_buffer, miso_data_buffer);
  auto data = miso_data_buffer.at(position_in_buffer);

  return {spi_ret_val, data};
}

auto NRF24L01SpiProtocol::ReadRegister(const std::uint8_t register_address, std::uint8_t length) noexcept -> std::pair<types::DriverStatus, std::vector<std::uint8_t>> {
  std::vector<std::uint8_t> mosi_data_buffer;
  std::vector<std::uint8_t> miso_data_buffer(length + 1);
  mosi_data_buffer.push_back(instruction_word::R_REGISTER | register_address);

  auto spi_ret_val = spi_->Transfer(mosi_data_buffer, miso_data_buffer);
  miso_data_buffer.erase(miso_data_buffer.begin());

  return {spi_ret_val, miso_data_buffer};
}

auto NRF24L01SpiProtocol::WriteRegister(std::uint8_t register_address, std::uint8_t register_content) noexcept -> types::DriverStatus {
  std::vector<std::uint8_t> mosi_data_buffer;
  mosi_data_buffer.push_back(instruction_word::W_REGISTER | register_address);
  mosi_data_buffer.push_back(register_content);

  auto spi_ret_val = spi_->Write(mosi_data_buffer);

  return spi_ret_val;
}

auto NRF24L01SpiProtocol::WriteRegister(std::uint8_t register_address, std::vector<std::uint8_t> &register_content) noexcept -> types::DriverStatus {
  std::vector<std::uint8_t> mosi_data_buffer;
  mosi_data_buffer = register_content;
  mosi_data_buffer.insert(mosi_data_buffer.begin(), (instruction_word::W_REGISTER | register_address));

  auto spi_ret_val = spi_->Write(mosi_data_buffer);

  return spi_ret_val;
}

auto NRF24L01SpiProtocol::WritePayloadData(std::vector<std::uint8_t> &payload) noexcept -> types::DriverStatus {
  std::vector<std::uint8_t> mosi_data_buffer;
  mosi_data_buffer = payload;
  mosi_data_buffer.insert(mosi_data_buffer.begin(), instruction_word::W_TX_PAYLOAD);

  auto spi_ret_val = spi_->Write(mosi_data_buffer);

  return spi_ret_val;
}

auto NRF24L01SpiProtocol::ReadPayloadData(std::vector<std::uint8_t> &payload) noexcept -> types::DriverStatus {
  std::vector<std::uint8_t> mosi_data_buffer;
  mosi_data_buffer.push_back(instruction_word::R_RX_PAYLOAD);
  payload.push_back(0);  //make room for additional byte. Is sent antiparallel to command byte and contains non-relevant information.

  auto spi_ret_val = spi_->Transfer(mosi_data_buffer, payload);
  payload.erase(payload.begin());

  return spi_ret_val;
}

auto NRF24L01SpiProtocol::FlushTxBuffer() noexcept -> types::DriverStatus {
  std::vector<std::uint8_t> mosi_data_buffer;
  mosi_data_buffer.push_back(instruction_word::FLUSH_TX);

  auto spi_ret_val = spi_->Write(mosi_data_buffer);

  return spi_ret_val;
}

auto NRF24L01SpiProtocol::FlushRxBuffer() noexcept -> types::DriverStatus {
  std::vector<std::uint8_t> mosi_data_buffer;
  mosi_data_buffer.push_back(instruction_word::FLUSH_RX);

  auto spi_ret_val = spi_->Write(mosi_data_buffer);

  return spi_ret_val;
}

auto NRF24L01SpiProtocol::ReadAndClearIRQFlags() noexcept -> std::pair<types::DriverStatus, std::uint8_t> {
  constexpr auto position_in_buffer = 0;
  constexpr auto spi_transfer_length = 2;
  std::vector<std::uint8_t> mosi_data;
  std::vector<std::uint8_t> miso_data(spi_transfer_length);

  utilities::Byte construct_byte(0);

  construct_byte.SetBit(reg::status::MAX_RT);
  construct_byte.SetBit(reg::status::TX_DS);
  construct_byte.SetBit(reg::status::RX_DR);

  mosi_data.push_back(instruction_word::W_REGISTER | reg::status::REG_ADDR);
  mosi_data.push_back(construct_byte.Get());
  auto spi_ret_val = spi_->Transfer(mosi_data, miso_data);

  auto data = miso_data.at(position_in_buffer);
  return {spi_ret_val, data};
}

}  // namespace com
