#include "com_nrf24l01_spi_protocol.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::ElementsAre;
using ::testing::Invoke;
using ::testing::Return;

namespace {
class ComNRF24L01SpiProtocolTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }
  spi::CSPin cs_pin_;
  spi::SPI spi_{cs_pin_};
  std::unique_ptr<com::NRF24L01SpiProtocol> unit_under_test_;
};

}  // namespace

types::DriverStatus ConstructTestVector(std::vector<std::uint8_t> &mosi, std::vector<std::uint8_t> &miso) noexcept {
  miso.at(0) = 0xaa;
  return types::DriverStatus::OK;
}

TEST_F(ComNRF24L01SpiProtocolTests, read_register) {
  std::uint8_t test_reg_addr = 0xfa;
  unit_under_test_ = std::make_unique<com::NRF24L01SpiProtocol>(spi_);
  EXPECT_CALL(spi_, Transfer(ElementsAre(com::instruction_word::R_REGISTER | test_reg_addr), ElementsAre(_, _)));
  unit_under_test_->ReadRegister(test_reg_addr);
}

TEST_F(ComNRF24L01SpiProtocolTests, write_register_spi_tx_ok) {
  std::uint8_t test_reg_addr = 0xfa;
  std::uint8_t test_reg_content = 0xaf;
  unit_under_test_ = std::make_unique<com::NRF24L01SpiProtocol>(spi_);
  EXPECT_CALL(spi_, Write(ElementsAre(com::instruction_word::W_REGISTER | test_reg_addr, test_reg_content)));
  auto retval = unit_under_test_->WriteRegister(test_reg_addr, test_reg_content);
  EXPECT_EQ(retval, types::DriverStatus::OK);
}

TEST_F(ComNRF24L01SpiProtocolTests, write_register_spi_tx_not_ok) {
  std::uint8_t test_reg_addr = 0xfa;
  std::uint8_t test_reg_content = 0xaf;
  unit_under_test_ = std::make_unique<com::NRF24L01SpiProtocol>(spi_);
  EXPECT_CALL(spi_, Write(_)).WillOnce(Return(types::DriverStatus::HAL_ERROR));
  auto retval = unit_under_test_->WriteRegister(test_reg_addr, test_reg_content);
  EXPECT_EQ(retval, types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01SpiProtocolTests, read_register_multibyte) {
  std::uint8_t test_reg_addr = 0xfa;
  std::uint8_t length = 3;
  unit_under_test_ = std::make_unique<com::NRF24L01SpiProtocol>(spi_);
  EXPECT_CALL(spi_, Transfer(ElementsAre(com::instruction_word::R_REGISTER | test_reg_addr), ElementsAre(_, _, _, _)));
  unit_under_test_->ReadRegister(test_reg_addr, length);
}

TEST_F(ComNRF24L01SpiProtocolTests, write_register_multibyte_spi_tx_ok) {
  std::uint8_t test_reg_addr = 0x0a;
  std::vector<std::uint8_t> test_reg_content{0xaf, 0xaf, 0xaf};
  unit_under_test_ = std::make_unique<com::NRF24L01SpiProtocol>(spi_);
  EXPECT_CALL(spi_, Write(ElementsAre(com::instruction_word::W_REGISTER | test_reg_addr, 0xaf, 0xaf, 0xaf)));
  auto retval = unit_under_test_->WriteRegister(test_reg_addr, test_reg_content);
  EXPECT_EQ(retval, types::DriverStatus::OK);
}

TEST_F(ComNRF24L01SpiProtocolTests, write_payload_spi_tx_ok) {
  std::vector<std::uint8_t> test_reg_content{0xaf, 0xaf, 0xaf};
  unit_under_test_ = std::make_unique<com::NRF24L01SpiProtocol>(spi_);
  EXPECT_CALL(spi_, Write(ElementsAre(com::instruction_word::W_TX_PAYLOAD, 0xaf, 0xaf, 0xaf)));
  auto retval = unit_under_test_->WritePayloadData(test_reg_content);
  EXPECT_EQ(retval, types::DriverStatus::OK);
}

TEST_F(ComNRF24L01SpiProtocolTests, read_payload_spi_tx_ok) {
  std::vector<std::uint8_t> test_payload;
  test_payload.resize(4);
  unit_under_test_ = std::make_unique<com::NRF24L01SpiProtocol>(spi_);
  EXPECT_CALL(spi_, Transfer(ElementsAre(com::instruction_word::R_RX_PAYLOAD), _));
  auto retval = unit_under_test_->ReadPayloadData(test_payload);
  EXPECT_THAT(test_payload, ElementsAre(_, _, _));
  EXPECT_EQ(retval, types::DriverStatus::OK);
}

TEST_F(ComNRF24L01SpiProtocolTests, flush_tx_buffer) {
  unit_under_test_ = std::make_unique<com::NRF24L01SpiProtocol>(spi_);
  EXPECT_CALL(spi_, Write(ElementsAre(com::instruction_word::FLUSH_TX)));
  unit_under_test_->FlushTxBuffer();
}

TEST_F(ComNRF24L01SpiProtocolTests, flush_rx_buffer) {
  unit_under_test_ = std::make_unique<com::NRF24L01SpiProtocol>(spi_);
  EXPECT_CALL(spi_, Write(ElementsAre(com::instruction_word::FLUSH_RX)));
  unit_under_test_->FlushRxBuffer();
}

TEST_F(ComNRF24L01SpiProtocolTests, read_and_clear_irq_flags) {
  std::uint8_t test_reg_addr = com::reg::status::REG_ADDR;
  std::uint8_t clear_irq_bit_sequence = 0x70;
  unit_under_test_ = std::make_unique<com::NRF24L01SpiProtocol>(spi_);
  EXPECT_CALL(spi_, Transfer(ElementsAre(com::instruction_word::W_REGISTER | test_reg_addr, _), _)).WillOnce(Invoke(&ConstructTestVector));
  auto rv = unit_under_test_->ReadAndClearIRQFlags();
  EXPECT_EQ(rv, 0xaa);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}