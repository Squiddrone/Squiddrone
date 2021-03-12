#include "com_nrf24l01_spi_protocol.hpp"
#include "com_nrf24l01_reg.hpp"

namespace com {

auto NRF24L01SpiProtocol::ReadRegister(const std::uint8_t register_address) noexcept -> std::uint8_t {
  auto position_in_buffer = 1;
  auto spi_transfer_length = 2;
  std::vector<std::uint8_t> mosi_data_buffer;
  std::vector<std::uint8_t> miso_data_buffer(spi_transfer_length);
  mosi_data_buffer.push_back(instruction_word::R_REGISTER | register_address);

  spi_.Transfer(mosi_data_buffer, miso_data_buffer);

  return miso_data_buffer.at(position_in_buffer);
}

auto NRF24L01SpiProtocol::ReadRegister(const std::uint8_t register_address, std::uint8_t length) noexcept -> std::vector<uint8_t> {
  std::vector<std::uint8_t> mosi_data_buffer;
  std::vector<std::uint8_t> miso_data_buffer(length + 1);
  mosi_data_buffer.push_back(instruction_word::R_REGISTER | register_address);

  spi_.Transfer(mosi_data_buffer, miso_data_buffer);
  miso_data_buffer.erase(miso_data_buffer.begin());

  return miso_data_buffer;
}

auto NRF24L01SpiProtocol::WriteRegister(std::uint8_t register_address, std::uint8_t register_content) -> types::DriverStatus {
  std::vector<std::uint8_t> mosi_data_buffer;
  mosi_data_buffer.push_back(instruction_word::W_REGISTER | register_address);
  mosi_data_buffer.push_back(register_content);

  auto spi_ret_val = spi_.Write(mosi_data_buffer);

  return spi_ret_val;
}

auto NRF24L01SpiProtocol::WriteRegister(std::uint8_t register_address, std::vector<uint8_t> &register_content) -> types::DriverStatus {
  std::vector<uint8_t> mosi_data_buffer;
  mosi_data_buffer = register_content;
  mosi_data_buffer.insert(mosi_data_buffer.begin(), (instruction_word::W_REGISTER | register_address));

  auto spi_ret_val = spi_.Write(mosi_data_buffer);

  return spi_ret_val;
}

auto NRF24L01SpiProtocol::WritePayloadData(std::vector<uint8_t> &payload) noexcept -> types::DriverStatus {
  std::vector<uint8_t> mosi_data_buffer;
  mosi_data_buffer = payload;
  mosi_data_buffer.insert(mosi_data_buffer.begin(), instruction_word::W_TX_PAYLOAD);

  auto spi_ret_val = spi_.Write(mosi_data_buffer);

  return spi_ret_val;
}

}  // namespace com