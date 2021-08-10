#include "com_nrf24l01_core.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

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
};

TEST_F(ComNRF24L01CoreTests, enable_data_pipe_read_register_fail_test) {
  std::pair<types::DriverStatus, std::uint8_t> mock_return_value = {types::DriverStatus::HAL_ERROR, 0};
  ON_CALL(*spi_protocol_, ReadRegister(_)).WillByDefault(Return(mock_return_value));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->EnableDataPipe(com::DataPipe::RX_PIPE_0), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, enable_data_pipe_write_register_fail_test) {
  EXPECT_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::uint8_t>(_))).WillRepeatedly(Return(types::DriverStatus::HAL_ERROR));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->EnableDataPipe(com::DataPipe::RX_PIPE_0), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, disable_data_pipe_read_register_fail_test) {
  std::pair<types::DriverStatus, std::uint8_t> mock_return_value = {types::DriverStatus::HAL_ERROR, 0};
  ON_CALL(*spi_protocol_, ReadRegister(_)).WillByDefault(Return(mock_return_value));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->DisableDataPipe(com::DataPipe::RX_PIPE_0), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, disable_data_pipe_write_register_fail_test) {
  EXPECT_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::uint8_t>(_))).WillRepeatedly(Return(types::DriverStatus::HAL_ERROR));
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->DisableDataPipe(com::DataPipe::RX_PIPE_0), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, set_pipe_addr_multibyte_successful) {
  EXPECT_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::vector<std::uint8_t>>(_))).WillRepeatedly(Return(types::DriverStatus::OK));
  com::data_pipe_address test_pipe_address = {0x0, 0x1, 0x2, 0x3, 0x4};
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->SetPipeAddress(com::DataPipe::TX_PIPE, test_pipe_address), types::DriverStatus::OK);
}

TEST_F(ComNRF24L01CoreTests, set_pipe_addr_multibyte_failed) {
  EXPECT_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::vector<std::uint8_t>>(_))).WillRepeatedly(Return(types::DriverStatus::HAL_ERROR));
  com::data_pipe_address test_pipe_address = {0x0, 0x1, 0x2, 0x3, 0x4};
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->SetPipeAddress(com::DataPipe::TX_PIPE, test_pipe_address), types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01CoreTests, set_pipe_addr_singlebyte_successful) {
  EXPECT_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::uint8_t>(_))).WillRepeatedly(Return(types::DriverStatus::OK));
  com::data_pipe_address test_pipe_address = {0x0, 0x1, 0x2, 0x3, 0x4};
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->SetPipeAddress(com::DataPipe::RX_PIPE_2, test_pipe_address), types::DriverStatus::OK);
}

TEST_F(ComNRF24L01CoreTests, set_pipe_addr_singlebyte_failed) {
  EXPECT_CALL(*spi_protocol_, WriteRegister(_, Matcher<std::uint8_t>(_))).WillRepeatedly(Return(types::DriverStatus::HAL_ERROR));
  com::data_pipe_address test_pipe_address = {0x0, 0x1, 0x2, 0x3, 0x4};
  unit_under_test_ = std::make_unique<com::NRF24L01Core>(std::move(spi_protocol_));
  EXPECT_EQ(unit_under_test_->SetPipeAddress(com::DataPipe::RX_PIPE_2, test_pipe_address), types::DriverStatus::HAL_ERROR);
}

}  // namespace