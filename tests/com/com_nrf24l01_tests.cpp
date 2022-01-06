#include <algorithm>
#include "com_nrf24l01.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "stm32g4xx_hal_gpio.h"

using ::testing::_;
using ::testing::ElementsAre;
using ::testing::NiceMock;
using ::testing::Return;
namespace {
class ComNRF24L01Tests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    default_msg_frame_.resize(32);
    std::fill(default_msg_frame_.begin(), default_msg_frame_.end(), 0xaa);
    default_msg_frame_.at(0) = 0;
    default_data_packet_.Deserialize(default_msg_frame_);
  }
  types::com_msg_frame default_msg_frame_;
  types::ComDataPacket default_data_packet_;
};

TEST_F(ComNRF24L01Tests, get_data_packet_successful) {
  auto com_msg_buffer = std::make_unique<NiceMock<com::ComMessageBuffer>>();
  ON_CALL(*com_msg_buffer, GetData).WillByDefault(Return(default_msg_frame_));
  auto com_nrf_core = std::make_unique<NiceMock<com::NRF24L01Core>>();
  auto unit_under_test = std::make_unique<com::NRF24L01>(std::move(com_msg_buffer), std::move(com_nrf_core));
  auto return_value = unit_under_test->GetDataPacket();
  ASSERT_EQ(return_value.data, default_data_packet_.data);
  ASSERT_EQ(return_value.target, default_data_packet_.target);
  ASSERT_EQ(return_value.type, default_data_packet_.type);
}

TEST_F(ComNRF24L01Tests, frame_length_exceeding_limit) {
  auto com_msg_buffer = std::make_unique<NiceMock<com::ComMessageBuffer>>();
  auto com_nrf_core = std::make_unique<NiceMock<com::NRF24L01Core>>();
  auto unit_under_test = std::make_unique<com::NRF24L01>(std::move(com_msg_buffer), std::move(com_nrf_core));
  std::vector<std::uint8_t> long_data_field(31);
  types::ComDataPacket mock_packet;
  mock_packet.data = long_data_field;
  auto return_value = unit_under_test->PutDataPacket(types::PutDataTarget::TARGET_FRONT, mock_packet);
  ASSERT_EQ(return_value, types::DriverStatus::INPUT_ERROR);
}

TEST_F(ComNRF24L01Tests, put_data_packet_successful) {
  auto com_msg_buffer = std::make_unique<NiceMock<com::ComMessageBuffer>>();
  ON_CALL(*com_msg_buffer, GetData).WillByDefault(Return(default_msg_frame_));

  auto com_nrf_core = std::make_unique<NiceMock<com::NRF24L01Core>>();
  auto unit_under_test = std::make_unique<com::NRF24L01>(std::move(com_msg_buffer), std::move(com_nrf_core));

  auto return_value = unit_under_test->PutDataPacket(types::PutDataTarget::TARGET_FRONT, default_data_packet_);
  ASSERT_EQ(return_value, types::DriverStatus::OK);
}

TEST_F(ComNRF24L01Tests, handle_incoming_telemetry_packet) {
  types::com_msg_frame mock_payload = default_msg_frame_;
  mock_payload.at(0) = static_cast<std::uint8_t>(types::ComPacketType::TELEMETRY_PACKET);
  auto com_msg_buffer = std::make_unique<NiceMock<com::ComMessageBuffer>>();
  EXPECT_CALL(*com_msg_buffer, PutData(_)).WillOnce(Return(com::ComBufferError::COM_BUFFER_OK));

  auto com_nrf_core = std::make_unique<NiceMock<com::NRF24L01Core>>();
  ON_CALL(*com_nrf_core, GetRxPayload(_)).WillByDefault(Return(types::DriverStatus::OK));

  auto unit_under_test = std::make_unique<com::NRF24L01>(std::move(com_msg_buffer), std::move(com_nrf_core));

  unit_under_test->HandleRxIRQ();
}

TEST_F(ComNRF24L01Tests, handle_incoming_addr_config_packet) {
  types::com_msg_frame mock_payload = default_msg_frame_;
  mock_payload.at(0) = static_cast<std::uint8_t>(types::ComPacketType::COM_ADDR_CONFIG_PACKET);
  auto com_msg_buffer = std::make_unique<NiceMock<com::ComMessageBuffer>>();

  auto com_nrf_core = std::make_unique<NiceMock<com::NRF24L01Core>>();
  ON_CALL(*com_nrf_core, GetRxPayload(_)).WillByDefault(Return(types::DriverStatus::OK));
  EXPECT_CALL(*com_nrf_core, SetPipeAddress(_, _)).WillOnce(Return(types::DriverStatus::OK));

  auto unit_under_test = std::make_unique<com::NRF24L01>(std::move(com_msg_buffer), std::move(com_nrf_core));

  unit_under_test->HandleRxIRQ();
}

}  // namespace