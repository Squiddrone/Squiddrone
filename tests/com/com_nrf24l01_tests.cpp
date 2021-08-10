#include "com_nrf24l01.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::ElementsAre;
using ::testing::NiceMock;
using ::testing::Return;
namespace {
class ComNRF24L01Tests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    com_msg_buffer_ = std::make_unique<NiceMock<com::ComMessageBuffer>>();
    com_nrf_core_ = std::make_unique<NiceMock<com::NRF24L01Core>>();

    ON_CALL(*com_msg_buffer_, GetData).WillByDefault(Return(default_msg_frame_));
  }

  std::unique_ptr<com::ComMessageBuffer> com_msg_buffer_;
  std::unique_ptr<com::NRF24L01Core> com_nrf_core_;

  types::com_msg_frame default_msg_frame_ = {0xAA};
};

TEST_F(ComNRF24L01Tests, com_get_data_packet_successful) {
  auto unit_under_test_ = std::make_unique<com::NRF24L01>(std::move(com_msg_buffer_), std::move(com_nrf_core_));
  types::com_msg_frame msg_frame_ = {0xAA};

  auto return_value = unit_under_test_->GetDataPacket();
  ASSERT_EQ(return_value, msg_frame_);
}

TEST_F(ComNRF24L01Tests, com_frame_length_exceeding_limit) {
  auto unit_under_test_ = std::make_unique<com::NRF24L01>(std::move(com_msg_buffer_), std::move(com_nrf_core_));
  types::com_msg_frame long_msg_frame(33);

  auto return_value = unit_under_test_->PutDataPacket(0, long_msg_frame);
  ASSERT_EQ(return_value, types::DriverStatus::INPUT_ERROR);
}

TEST_F(ComNRF24L01Tests, com_put_data_packet_successful) {
  auto unit_under_test_ = std::make_unique<com::NRF24L01>(std::move(com_msg_buffer_), std::move(com_nrf_core_));

  auto return_value = unit_under_test_->PutDataPacket(0, default_msg_frame_);
  ASSERT_EQ(return_value, types::DriverStatus::OK);
}

/* TEST_F(ComNRF24L01Tests, com_put_data_packet_hal_reg_access_not_successful) {
  com::ReadRegSinglebyteReturn mock_ret_val = {types::DriverStatus::HAL_ERROR, 0};
  //ON_CALL(*com_spi_protocol_, ReadRegister(com::reg::config::REG_ADDR)).WillByDefault(Return(mock_ret_val));

  auto unit_under_test_ = std::make_unique<com::NRF24L01>(std::move(com_msg_buffer_), std::move(com_spi_protocol_));

  auto return_value_1 = unit_under_test_->PutDataPacket(0, default_msg_frame_);
  ASSERT_EQ(return_value_1, types::DriverStatus::HAL_ERROR);
}*/

}  // namespace