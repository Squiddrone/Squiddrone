#include "com_nrf24l01_core.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "mcu_settings.h"

using ::testing::_;
using ::testing::ElementsAre;
using ::testing::Matcher;
using ::testing::NiceMock;
using ::testing::Return;

namespace {
class ComNRF24L01CoreTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    spi_protocol_ = std::make_unique<NiceMock<com::NRF24L01SpiProtocol>>();
  }

  std::unique_ptr<com::NRF24L01SpiProtocol> spi_protocol_;
  std::unique_ptr<com::NRF24L01Core> unit_under_test_;
  types::data_pipe_address default_address_{{0xe7, 0xe7, 0xe7, 0xe7, 0xe7}};
};

TEST_F(ComNRF24L01CoreTests, enable_data_pipe_read_register_fail) {
  std::pair<types::DriverStatus, std::uint8_t> mock_return_value = {types::DriverStatus::HAL_ERROR, 0};
  ON_CALL(*spi_protocol_, ReadRegister(_)).WillByDefault(Return(mock_return_value));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->EnableDataPipe(com::DataPipe::RX_PIPE_0), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, enable_data_pipe_write_register_fail) {
  EXPECT_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::uint8_t>(_))).WillRepeatedly(Return(types::DriverStatus::HAL_ERROR));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->EnableDataPipe(com::DataPipe::RX_PIPE_0), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, disable_data_pipe_read_register_fail) {
  std::pair<types::DriverStatus, std::uint8_t> mock_return_value = {types::DriverStatus::HAL_ERROR, 0};
  ON_CALL(*spi_protocol_, ReadRegister(_)).WillByDefault(Return(mock_return_value));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->DisableDataPipe(com::DataPipe::RX_PIPE_0), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, disable_data_pipe_write_register_fail) {
  EXPECT_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::uint8_t>(_))).WillRepeatedly(Return(types::DriverStatus::HAL_ERROR));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->DisableDataPipe(com::DataPipe::RX_PIPE_0), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, set_pipe_addr_multibyte_successful) {
  EXPECT_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::vector<std::uint8_t>>(_))).WillRepeatedly(Return(types::DriverStatus::OK));
  types::data_pipe_address test_pipe_address = {0x0, 0x1, 0x2, 0x3, 0x4};
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->SetPipeAddress(com::DataPipe::TX_PIPE, test_pipe_address), types::DriverStatus::OK);
}

TEST_F(ComNRF24L01CoreTests, set_pipe_addr_multibyte_failed) {
  EXPECT_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::vector<std::uint8_t>>(_))).WillRepeatedly(Return(types::DriverStatus::HAL_ERROR));
  types::data_pipe_address test_pipe_address = {0x0, 0x1, 0x2, 0x3, 0x4};
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->SetPipeAddress(com::DataPipe::TX_PIPE, test_pipe_address), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, set_pipe_addr_singlebyte_successful) {
  EXPECT_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::uint8_t>(_))).WillRepeatedly(Return(types::DriverStatus::OK));
  types::data_pipe_address test_pipe_address = {0x0, 0x1, 0x2, 0x3, 0x4};
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->SetPipeAddress(com::DataPipe::RX_PIPE_2, test_pipe_address), types::DriverStatus::OK);
}

TEST_F(ComNRF24L01CoreTests, set_pipe_addr_singlebyte_failed) {
  EXPECT_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::uint8_t>(_))).WillRepeatedly(Return(types::DriverStatus::HAL_ERROR));
  types::data_pipe_address test_pipe_address = {0x0, 0x1, 0x2, 0x3, 0x4};
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->SetPipeAddress(com::DataPipe::RX_PIPE_2, test_pipe_address), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, get_pipe_addr_multibyte_successful) {
  std::pair<types::DriverStatus, std::vector<uint8_t>> test_return_value = {types::DriverStatus::OK, {0}};
  EXPECT_CALL(*spi_protocol_, ReadRegister(_, _)).WillRepeatedly(Return(test_return_value));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->GetPipeAddress(com::DataPipe::TX_PIPE).first, types::DriverStatus::OK);
}

TEST_F(ComNRF24L01CoreTests, get_pipe_addr_multibyte_failed) {
  std::pair<types::DriverStatus, std::vector<uint8_t>> test_return_value = {types::DriverStatus::HAL_ERROR, {0}};
  EXPECT_CALL(*spi_protocol_, ReadRegister(_, _)).WillRepeatedly(Return(test_return_value));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->GetPipeAddress(com::DataPipe::TX_PIPE).first, types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, get_pipe_addr_singlebyte_successful) {
  std::pair<types::DriverStatus, std::uint8_t> test_return_value = {types::DriverStatus::OK, 0};
  EXPECT_CALL(*spi_protocol_, ReadRegister(_)).WillRepeatedly(Return(test_return_value));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->GetPipeAddress(com::DataPipe::RX_PIPE_2).first, types::DriverStatus::OK);
}

TEST_F(ComNRF24L01CoreTests, get_pipe_addr_singlebyte_failed) {
  std::pair<types::DriverStatus, std::uint8_t> test_return_value = {types::DriverStatus::HAL_ERROR, 0};
  EXPECT_CALL(*spi_protocol_, ReadRegister(_)).WillRepeatedly(Return(test_return_value));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->GetPipeAddress(com::DataPipe::RX_PIPE_2).first, types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, set_rx_payload_size_successful) {
  EXPECT_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::uint8_t>(_))).WillRepeatedly(Return(types::DriverStatus::OK));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->SetRxPayloadSize(com::DataPipe::RX_PIPE_0, 32), types::DriverStatus::OK);
}

TEST_F(ComNRF24L01CoreTests, set_rx_payload_size_failed) {
  EXPECT_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::uint8_t>(_))).WillRepeatedly(Return(types::DriverStatus::HAL_ERROR));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->SetRxPayloadSize(com::DataPipe::RX_PIPE_0, 32), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, enable_auto_ack_read_register_fail) {
  std::pair<types::DriverStatus, std::uint8_t> mock_return_value = {types::DriverStatus::HAL_ERROR, 0};
  ON_CALL(*spi_protocol_, ReadRegister(_)).WillByDefault(Return(mock_return_value));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->EnableAutoAck(com::DataPipe::RX_PIPE_0), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, enable_auto_ack_write_register_fail) {
  EXPECT_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::uint8_t>(_))).WillRepeatedly(Return(types::DriverStatus::HAL_ERROR));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->EnableAutoAck(com::DataPipe::RX_PIPE_0), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, init_tx_already_configured) {
  std::pair<types::DriverStatus, std::uint8_t> test_single_byte_return_value = {types::DriverStatus::OK, 0};
  std::pair<types::DriverStatus, std::vector<uint8_t>> test_multi_byte_return_value = {types::DriverStatus::OK, {0}};
  types::data_pipe_address mock_address = {0};
  ON_CALL(*spi_protocol_, ReadRegister(_)).WillByDefault(Return(test_single_byte_return_value));
  ON_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::uint8_t>(_))).WillByDefault(Return(types::DriverStatus::OK));
  ON_CALL(*spi_protocol_, ReadRegister(_, _)).WillByDefault(Return(test_multi_byte_return_value));
  ON_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::vector<std::uint8_t>>(_))).WillByDefault(Return(types::DriverStatus::OK));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  auto init_tx_return_value = unit_under_test_->InitTx(mock_address);
  init_tx_return_value = unit_under_test_->InitTx(mock_address);
  EXPECT_EQ(init_tx_return_value, types::DriverStatus::OK);
}

TEST_F(ComNRF24L01CoreTests, init_tx_not_successful) {
  types::data_pipe_address mock_address = {0};
  EXPECT_CALL(*spi_protocol_, FlushTxBuffer()).WillRepeatedly(Return(types::DriverStatus::HAL_ERROR));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->InitTx(mock_address), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, init_rx_already_configured) {
  std::pair<types::DriverStatus, std::uint8_t> test_single_byte_return_value = {types::DriverStatus::OK, 0};
  std::pair<types::DriverStatus, std::vector<uint8_t>> test_multi_byte_return_value = {types::DriverStatus::OK, {0}};
  ON_CALL(*spi_protocol_, ReadRegister(_)).WillByDefault(Return(test_single_byte_return_value));
  ON_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::uint8_t>(_))).WillByDefault(Return(types::DriverStatus::OK));
  ON_CALL(*spi_protocol_, ReadRegister(_, _)).WillByDefault(Return(test_multi_byte_return_value));
  ON_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::vector<std::uint8_t>>(_))).WillByDefault(Return(types::DriverStatus::OK));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  auto init_tx_return_value = unit_under_test_->InitRx(default_address_);
  init_tx_return_value = unit_under_test_->InitRx(default_address_);
  EXPECT_EQ(init_tx_return_value, types::DriverStatus::OK);
}

TEST_F(ComNRF24L01CoreTests, init_rx_not_successful) {
  EXPECT_CALL(*spi_protocol_, FlushTxBuffer()).WillRepeatedly(Return(types::DriverStatus::HAL_ERROR));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->InitRx(default_address_), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, init_transceiver_already_configured) {
  std::pair<types::DriverStatus, std::uint8_t> test_single_byte_return_value = {types::DriverStatus::OK, 0};
  std::pair<types::DriverStatus, std::vector<uint8_t>> test_multi_byte_return_value = {types::DriverStatus::OK, {0}};
  ON_CALL(*spi_protocol_, ReadRegister(_)).WillByDefault(Return(test_single_byte_return_value));
  ON_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::uint8_t>(_))).WillByDefault(Return(types::DriverStatus::OK));
  ON_CALL(*spi_protocol_, ReadRegister(_, _)).WillByDefault(Return(test_multi_byte_return_value));
  ON_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::vector<std::uint8_t>>(_))).WillByDefault(Return(types::DriverStatus::OK));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  auto init_tx_return_value = unit_under_test_->InitTransceiver(30, com::DataRateSetting::RF_DR_2MBPS, com::RFPowerSetting::RF_PWR_0DBM, com::CRCEncodingScheme::CRC_16BIT, default_address_);
  init_tx_return_value = unit_under_test_->InitTransceiver(30, com::DataRateSetting::RF_DR_2MBPS, com::RFPowerSetting::RF_PWR_0DBM, com::CRCEncodingScheme::CRC_16BIT, default_address_);
  EXPECT_EQ(init_tx_return_value, types::DriverStatus::OK);
}

TEST_F(ComNRF24L01CoreTests, init_transceiver_not_successful) {
  std::pair<types::DriverStatus, std::uint8_t> test_single_byte_return_value = {types::DriverStatus::HAL_ERROR, 0};
  std::pair<types::DriverStatus, std::vector<uint8_t>> test_multi_byte_return_value = {types::DriverStatus::HAL_ERROR, {0}};
  ON_CALL(*spi_protocol_, ReadRegister(_)).WillByDefault(Return(test_single_byte_return_value));
  ON_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::uint8_t>(_))).WillByDefault(Return(types::DriverStatus::HAL_ERROR));
  ON_CALL(*spi_protocol_, ReadRegister(_, _)).WillByDefault(Return(test_multi_byte_return_value));
  ON_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::vector<std::uint8_t>>(_))).WillByDefault(Return(types::DriverStatus::HAL_ERROR));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  auto init_tx_return_value = unit_under_test_->InitTransceiver(30, com::DataRateSetting::RF_DR_2MBPS, com::RFPowerSetting::RF_PWR_0DBM, com::CRCEncodingScheme::CRC_16BIT, default_address_);
  EXPECT_EQ(init_tx_return_value, types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, set_operation_mode_successful) {
  std::pair<types::DriverStatus, std::uint8_t> mock_return_value = {types::DriverStatus::OK, 0};
  ON_CALL(*spi_protocol_, ReadRegister(_)).WillByDefault(Return(mock_return_value));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->SetOperationMode(com::OperationMode::UNDEFINED), types::DriverStatus::OK);
}

TEST_F(ComNRF24L01CoreTests, set_operation_mode_read_register_fail) {
  std::pair<types::DriverStatus, std::uint8_t> mock_return_value = {types::DriverStatus::HAL_ERROR, 0};
  ON_CALL(*spi_protocol_, ReadRegister(_)).WillByDefault(Return(mock_return_value));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->SetOperationMode(com::OperationMode::UNDEFINED), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, set_operation_mode_write_register_fail) {
  EXPECT_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::uint8_t>(_))).WillRepeatedly(Return(types::DriverStatus::HAL_ERROR));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->SetOperationMode(com::OperationMode::UNDEFINED), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, set_power_state_successful) {
  std::pair<types::DriverStatus, std::uint8_t> mock_return_value = {types::DriverStatus::OK, 0};
  ON_CALL(*spi_protocol_, ReadRegister(_)).WillByDefault(Return(mock_return_value));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->SetPowerState(com::State::ENABLED), types::DriverStatus::OK);
  EXPECT_EQ(unit_under_test_->SetPowerState(com::State::DISABLED), types::DriverStatus::OK);
}

TEST_F(ComNRF24L01CoreTests, set_power_state_read_register_fail) {
  std::pair<types::DriverStatus, std::uint8_t> mock_return_value = {types::DriverStatus::HAL_ERROR, 0};
  ON_CALL(*spi_protocol_, ReadRegister(_)).WillByDefault(Return(mock_return_value));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->SetPowerState(com::State::ENABLED), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, set_power_state_write_register_fail) {
  EXPECT_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::uint8_t>(_))).WillRepeatedly(Return(types::DriverStatus::HAL_ERROR));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->SetPowerState(com::State::ENABLED), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, set_rf_channel_successful) {
  std::pair<types::DriverStatus, std::uint8_t> mock_return_value = {types::DriverStatus::OK, 0};
  ON_CALL(*spi_protocol_, ReadRegister(_)).WillByDefault(Return(mock_return_value));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->SetRFChannel(0), types::DriverStatus::OK);
}

TEST_F(ComNRF24L01CoreTests, set_rf_channel_write_register_fail) {
  EXPECT_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::uint8_t>(_))).WillRepeatedly(Return(types::DriverStatus::HAL_ERROR));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->SetRFChannel(0), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, set_data_rate_successful) {
  std::pair<types::DriverStatus, std::uint8_t> mock_return_value = {types::DriverStatus::OK, 0};
  ON_CALL(*spi_protocol_, ReadRegister(_)).WillByDefault(Return(mock_return_value));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->SetDataRate(com::DataRateSetting::RF_DR_1MBPS), types::DriverStatus::OK);
  EXPECT_EQ(unit_under_test_->SetDataRate(com::DataRateSetting::RF_DR_2MBPS), types::DriverStatus::OK);
}

TEST_F(ComNRF24L01CoreTests, set_data_rate_read_register_fail) {
  std::pair<types::DriverStatus, std::uint8_t> mock_return_value = {types::DriverStatus::HAL_ERROR, 0};
  ON_CALL(*spi_protocol_, ReadRegister(_)).WillByDefault(Return(mock_return_value));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->SetDataRate(com::DataRateSetting::RF_DR_2MBPS), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, set_data_rate_write_register_fail) {
  EXPECT_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::uint8_t>(_))).WillRepeatedly(Return(types::DriverStatus::HAL_ERROR));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->SetDataRate(com::DataRateSetting::RF_DR_2MBPS), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, set_rf_output_power_successful) {
  std::pair<types::DriverStatus, std::uint8_t> mock_return_value = {types::DriverStatus::OK, 0};
  ON_CALL(*spi_protocol_, ReadRegister(_)).WillByDefault(Return(mock_return_value));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->SetRFOutputPower(com::RFPowerSetting::RF_PWR_0DBM), types::DriverStatus::OK);
}

TEST_F(ComNRF24L01CoreTests, set_rf_output_power_read_register_fail) {
  std::pair<types::DriverStatus, std::uint8_t> mock_return_value = {types::DriverStatus::HAL_ERROR, 0};
  ON_CALL(*spi_protocol_, ReadRegister(_)).WillByDefault(Return(mock_return_value));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->SetRFOutputPower(com::RFPowerSetting::RF_PWR_0DBM), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, set_rf_output_power_write_register_fail) {
  EXPECT_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::uint8_t>(_))).WillRepeatedly(Return(types::DriverStatus::HAL_ERROR));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->SetRFOutputPower(com::RFPowerSetting::RF_PWR_0DBM), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, mask_interrupt_on_pin_successful) {
  std::pair<types::DriverStatus, std::uint8_t> mock_return_value = {types::DriverStatus::OK, 0};
  ON_CALL(*spi_protocol_, ReadRegister(_)).WillByDefault(Return(mock_return_value));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->MaskInterruptOnIntPin(com::MaskeableInterrupts::TX_DATA_SENT), types::DriverStatus::OK);
}

TEST_F(ComNRF24L01CoreTests, mask_interrupt_on_pin_read_register_fail) {
  std::pair<types::DriverStatus, std::uint8_t> mock_return_value = {types::DriverStatus::HAL_ERROR, 0};
  ON_CALL(*spi_protocol_, ReadRegister(_)).WillByDefault(Return(mock_return_value));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->MaskInterruptOnIntPin(com::MaskeableInterrupts::TX_DATA_SENT), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, mask_interrupt_on_pin_write_register_fail) {
  EXPECT_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::uint8_t>(_))).WillRepeatedly(Return(types::DriverStatus::HAL_ERROR));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->MaskInterruptOnIntPin(com::MaskeableInterrupts::TX_DATA_SENT), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, set_address_width_successful) {
  std::pair<types::DriverStatus, std::uint8_t> mock_return_value = {types::DriverStatus::OK, 0};
  ON_CALL(*spi_protocol_, ReadRegister(_)).WillByDefault(Return(mock_return_value));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->SetAddressWidth(com::DataPipeAddressWidth::AW_5BYTES), types::DriverStatus::OK);
}

TEST_F(ComNRF24L01CoreTests, set_address_width_write_register_fail) {
  EXPECT_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::uint8_t>(_))).WillRepeatedly(Return(types::DriverStatus::HAL_ERROR));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->SetAddressWidth(com::DataPipeAddressWidth::AW_5BYTES), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, enable_crc_successful) {
  std::pair<types::DriverStatus, std::uint8_t> mock_return_value = {types::DriverStatus::OK, 0};
  ON_CALL(*spi_protocol_, ReadRegister(_)).WillByDefault(Return(mock_return_value));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->EnableCRC(), types::DriverStatus::OK);
}

TEST_F(ComNRF24L01CoreTests, enable_crc_read_register_fail) {
  std::pair<types::DriverStatus, std::uint8_t> mock_return_value = {types::DriverStatus::HAL_ERROR, 0};
  ON_CALL(*spi_protocol_, ReadRegister(_)).WillByDefault(Return(mock_return_value));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->EnableCRC(), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, enable_crc_write_register_fail) {
  EXPECT_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::uint8_t>(_))).WillRepeatedly(Return(types::DriverStatus::HAL_ERROR));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->EnableCRC(), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, set_crc_encoding_scheme_successful) {
  std::pair<types::DriverStatus, std::uint8_t> mock_return_value = {types::DriverStatus::OK, 0};
  ON_CALL(*spi_protocol_, ReadRegister(_)).WillByDefault(Return(mock_return_value));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->SetCRCEncodingScheme(com::CRCEncodingScheme::CRC_8BIT), types::DriverStatus::OK);
  EXPECT_EQ(unit_under_test_->SetCRCEncodingScheme(com::CRCEncodingScheme::CRC_16BIT), types::DriverStatus::OK);
}

TEST_F(ComNRF24L01CoreTests, set_crc_encoding_scheme_read_register_fail) {
  std::pair<types::DriverStatus, std::uint8_t> mock_return_value = {types::DriverStatus::HAL_ERROR, 0};
  ON_CALL(*spi_protocol_, ReadRegister(_)).WillByDefault(Return(mock_return_value));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->SetCRCEncodingScheme(com::CRCEncodingScheme::CRC_16BIT), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, set_crc_encoding_scheme_write_register_fail) {
  EXPECT_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::uint8_t>(_))).WillRepeatedly(Return(types::DriverStatus::HAL_ERROR));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->SetCRCEncodingScheme(com::CRCEncodingScheme::CRC_16BIT), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, config_auto_retransmission_successful) {
  std::pair<types::DriverStatus, std::uint8_t> mock_return_value = {types::DriverStatus::OK, 0};
  ON_CALL(*spi_protocol_, ReadRegister(_)).WillByDefault(Return(mock_return_value));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->ConfigAutoRetransmission(com::AutoRetransmissionDelay::ARD250US, com::AutoRetransmitCount::ARC0), types::DriverStatus::OK);
}

TEST_F(ComNRF24L01CoreTests, config_auto_retransmission_read_register_fail) {
  std::pair<types::DriverStatus, std::uint8_t> mock_return_value = {types::DriverStatus::HAL_ERROR, 0};
  ON_CALL(*spi_protocol_, ReadRegister(_)).WillByDefault(Return(mock_return_value));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->ConfigAutoRetransmission(com::AutoRetransmissionDelay::ARD250US, com ::AutoRetransmitCount::ARC0), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, config_auto_retransmission_write_register_fail) {
  EXPECT_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::uint8_t>(_))).WillRepeatedly(Return(types::DriverStatus::HAL_ERROR));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->ConfigAutoRetransmission(com::AutoRetransmissionDelay::ARD250US, com ::AutoRetransmitCount::ARC0), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, get_irq_flags_successful) {
  std::pair<types::DriverStatus, std::uint8_t> mock_return_value = {types::DriverStatus::OK, 0};
  ON_CALL(*spi_protocol_, ReadAndClearIRQFlags()).WillByDefault(Return(mock_return_value));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->GetIRQFlags().first, types::DriverStatus::OK);
}

TEST_F(ComNRF24L01CoreTests, get_irq_flags_read_register_fail) {
  std::pair<types::DriverStatus, std::uint8_t> mock_return_value = {types::DriverStatus::HAL_ERROR, 0};
  ON_CALL(*spi_protocol_, ReadAndClearIRQFlags()).WillByDefault(Return(mock_return_value));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->GetIRQFlags().first, types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, set_tx_payload_successful) {
  std::vector<std::uint8_t> mock_payload;
  ON_CALL(*spi_protocol_, WritePayloadData(_)).WillByDefault(Return(types::DriverStatus::OK));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->SetTxPayload(mock_payload), types::DriverStatus::OK);
}

TEST_F(ComNRF24L01CoreTests, set_tx_payload_read_register_fail) {
  std::vector<std::uint8_t> mock_payload;
  ON_CALL(*spi_protocol_, WritePayloadData(_)).WillByDefault(Return(types::DriverStatus::HAL_ERROR));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->SetTxPayload(mock_payload), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, get_rx_payload_successful) {
  std::vector<std::uint8_t> mock_payload;
  ON_CALL(*spi_protocol_, ReadPayloadData(_)).WillByDefault(Return(types::DriverStatus::OK));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->GetRxPayload(mock_payload), types::DriverStatus::OK);
}

TEST_F(ComNRF24L01CoreTests, get_rx_payload_read_register_fail) {
  std::vector<std::uint8_t> mock_payload;
  ON_CALL(*spi_protocol_, ReadPayloadData(_)).WillByDefault(Return(types::DriverStatus::HAL_ERROR));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->GetRxPayload(mock_payload), types::DriverStatus::HAL_ERROR);
}

}  // namespace