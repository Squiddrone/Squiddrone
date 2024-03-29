#include <algorithm>
#include "com_nrf24l01.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "stm32g4xx_hal_gpio.h"

using ::testing::_;
using ::testing::ElementsAre;
using ::testing::Invoke;
using ::testing::NiceMock;
using ::testing::Return;
namespace {
class ComNRF24L01Tests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    default_msg_frame_.resize(32);
    std::fill(default_msg_frame_.begin(), default_msg_frame_.end(), 0xaa);
    default_msg_frame_.at(0) = 0;
    default_msg_frame_.at(1) = 0;
    default_data_packet_.Deserialize(default_msg_frame_);
  }
  types::com_frame default_msg_frame_;
  types::ComDataPacket default_data_packet_;
};

TEST_F(ComNRF24L01Tests, get_data_packet_successful) {
  auto com_msg_buffer = std::make_unique<NiceMock<com::ComMessageBuffer>>();
  ON_CALL(*com_msg_buffer, GetData).WillByDefault(Return(default_msg_frame_));
  auto com_nrf_core = std::make_unique<NiceMock<com::NRF24L01Core>>();
  auto unit_under_test = std::make_unique<com::NRF24L01>(std::move(com_msg_buffer), std::move(com_nrf_core));
  auto return_value = unit_under_test->GetDataPacket();
  ASSERT_EQ(return_value.data, default_data_packet_.data);
  ASSERT_EQ(return_value.partner_id, default_data_packet_.partner_id);
  ASSERT_EQ(return_value.type, default_data_packet_.type);
}

TEST_F(ComNRF24L01Tests, frame_length_exceeding_limit) {
  auto com_msg_buffer = std::make_unique<NiceMock<com::ComMessageBuffer>>();
  auto com_nrf_core = std::make_unique<NiceMock<com::NRF24L01Core>>();
  auto unit_under_test = std::make_unique<com::NRF24L01>(std::move(com_msg_buffer), std::move(com_nrf_core));
  std::vector<std::uint8_t> long_data_field(31);
  types::ComDataPacket mock_packet;
  mock_packet.data = long_data_field;
  auto return_value = unit_under_test->PutDataPacket(types::ComPartnerId::PARTNER_ID_0, mock_packet);
  ASSERT_EQ(return_value, types::DriverStatus::INPUT_ERROR);
}

TEST_F(ComNRF24L01Tests, put_data_packet_successful) {
  auto com_msg_buffer = std::make_unique<NiceMock<com::ComMessageBuffer>>();
  ON_CALL(*com_msg_buffer, GetData).WillByDefault(Return(default_msg_frame_));

  auto com_nrf_core = std::make_unique<NiceMock<com::NRF24L01Core>>();

  std::pair<types::DriverStatus, std::uint8_t> irq_flags = {types::DriverStatus::OK, 0xff};
  ON_CALL(*com_nrf_core, GetIRQFlags()).WillByDefault(Return(irq_flags));

  auto unit_under_test = std::make_unique<com::NRF24L01>(std::move(com_msg_buffer), std::move(com_nrf_core));

  auto return_value = unit_under_test->PutDataPacket(types::ComPartnerId::PARTNER_ID_0, default_data_packet_);
  ASSERT_EQ(return_value, types::DriverStatus::OK);
}

TEST_F(ComNRF24L01Tests, put_data_packet_failed_tx_timeout) {
  auto com_msg_buffer = std::make_unique<NiceMock<com::ComMessageBuffer>>();
  ON_CALL(*com_msg_buffer, GetData).WillByDefault(Return(default_msg_frame_));

  auto com_nrf_core = std::make_unique<NiceMock<com::NRF24L01Core>>();

  std::pair<types::DriverStatus, std::uint8_t> irq_flags = {types::DriverStatus::OK, (1U << com::reg::status::MAX_RT)};
  ON_CALL(*com_nrf_core, GetIRQFlags()).WillByDefault(Return(irq_flags));

  auto unit_under_test = std::make_unique<com::NRF24L01>(std::move(com_msg_buffer), std::move(com_nrf_core));

  auto return_value = unit_under_test->PutDataPacket(types::ComPartnerId::PARTNER_ID_0, default_data_packet_);
  ASSERT_EQ(return_value, types::DriverStatus::TIMEOUT);
}

TEST_F(ComNRF24L01Tests, put_data_packet_failed_inconsistent_target) {
  auto com_msg_buffer = std::make_unique<NiceMock<com::ComMessageBuffer>>();
  auto com_nrf_core = std::make_unique<NiceMock<com::NRF24L01Core>>();
  types::ComDataPacket mock_packet;
  mock_packet.type = types::ComDataPacketType::TELEMETRY_PACKET;
  mock_packet.partner_id = types::ComPartnerId::PARTNER_ID_0;

  auto unit_under_test = std::make_unique<com::NRF24L01>(std::move(com_msg_buffer), std::move(com_nrf_core));

  auto return_value = unit_under_test->PutDataPacket(types::ComPartnerId::PARTNER_ID_1, mock_packet);
  ASSERT_EQ(return_value, types::DriverStatus::INPUT_ERROR);
}

TEST_F(ComNRF24L01Tests, put_data_packet_failed_invalid_target) {
  auto com_msg_buffer = std::make_unique<NiceMock<com::ComMessageBuffer>>();
  auto com_nrf_core = std::make_unique<NiceMock<com::NRF24L01Core>>();
  types::ComDataPacket mock_packet;
  mock_packet.type = types::ComDataPacketType::TELEMETRY_PACKET;
  mock_packet.partner_id = types::ComPartnerId::SELF;

  auto unit_under_test = std::make_unique<com::NRF24L01>(std::move(com_msg_buffer), std::move(com_nrf_core));

  auto return_value = unit_under_test->PutDataPacket(types::ComPartnerId::SELF, mock_packet);
  ASSERT_EQ(return_value, types::DriverStatus::INPUT_ERROR);
}

TEST_F(ComNRF24L01Tests, handle_incoming_telemetry_packet) {
  types::com_frame mock_payload = default_msg_frame_;
  mock_payload.at(0) = static_cast<std::uint8_t>(types::ComDataPacketType::TELEMETRY_PACKET);
  auto com_msg_buffer = std::make_unique<NiceMock<com::ComMessageBuffer>>();
  EXPECT_CALL(*com_msg_buffer, PutData(_)).WillOnce(Return(com::ComBufferError::COM_BUFFER_OK));

  auto com_nrf_core = std::make_unique<NiceMock<com::NRF24L01Core>>();
  ON_CALL(*com_nrf_core, GetRxPayload(_))
      .WillByDefault(Invoke(
          [=](types::com_frame &frame) {
            frame = mock_payload;
            return types::DriverStatus::OK;
          }));
  auto unit_under_test = std::make_unique<com::NRF24L01>(std::move(com_msg_buffer), std::move(com_nrf_core));

  unit_under_test->HandleRxIRQ();
}

TEST_F(ComNRF24L01Tests, handle_incoming_telemetry_packet_buffer_error) {
  types::com_frame mock_payload = default_msg_frame_;
  mock_payload.at(0) = static_cast<std::uint8_t>(types::ComDataPacketType::TELEMETRY_PACKET);
  auto com_msg_buffer = std::make_unique<NiceMock<com::ComMessageBuffer>>();
  EXPECT_CALL(*com_msg_buffer, PutData(_)).WillOnce(Return(com::ComBufferError::COM_BUFFER_IO_ERROR));

  auto com_nrf_core = std::make_unique<NiceMock<com::NRF24L01Core>>();

  auto unit_under_test = std::make_unique<com::NRF24L01>(std::move(com_msg_buffer), std::move(com_nrf_core));

  unit_under_test->HandleRxIRQ();
}

TEST_F(ComNRF24L01Tests, handle_incoming_addr_config_packet_partner_addr) {
  auto com_msg_buffer = std::make_unique<NiceMock<com::ComMessageBuffer>>();

  auto com_nrf_core = std::make_unique<NiceMock<com::NRF24L01Core>>();
  ON_CALL(*com_nrf_core, GetRxPayload(_))
      .WillByDefault(Invoke(
          [=](types::com_frame &frame) {
            types::OtaConfigPacket mock_ota_packet;
            mock_ota_packet.type = types::ComDataPacketType::COM_CONFIG_PACKET;
            mock_ota_packet.EncodeAddressConfigPacket(types::ComPartnerId::PARTNER_ID_0, {0xaa, 0xaa, 0xaa, 0xaa, 0xaa});
            frame = mock_ota_packet.Serialize();
            return types::DriverStatus::OK;
          }));

  auto unit_under_test = std::make_unique<com::NRF24L01>(std::move(com_msg_buffer), std::move(com_nrf_core));

  unit_under_test->HandleRxIRQ();
}

TEST_F(ComNRF24L01Tests, handle_incoming_addr_config_packet_base_addr) {
  auto com_msg_buffer = std::make_unique<NiceMock<com::ComMessageBuffer>>();

  auto com_nrf_core = std::make_unique<NiceMock<com::NRF24L01Core>>();
  ON_CALL(*com_nrf_core, GetRxPayload(_))
      .WillByDefault(Invoke(
          [=](types::com_frame &frame) {
            types::OtaConfigPacket mock_ota_packet;
            mock_ota_packet.type = types::ComDataPacketType::COM_CONFIG_PACKET;
            mock_ota_packet.EncodeAddressConfigPacket(types::ComPartnerId::SELF, {0xaa, 0xaa, 0xaa, 0xaa, 0xaa});
            frame = mock_ota_packet.Serialize();
            return types::DriverStatus::OK;
          }));
  EXPECT_CALL(*com_nrf_core, SetPipeAddress(_, _)).WillOnce(Return(types::DriverStatus::OK));

  auto unit_under_test = std::make_unique<com::NRF24L01>(std::move(com_msg_buffer), std::move(com_nrf_core));

  unit_under_test->HandleRxIRQ();
}

TEST_F(ComNRF24L01Tests, nrfinit_successful) {
  auto com_msg_buffer = std::make_unique<NiceMock<com::ComMessageBuffer>>();

  auto com_nrf_core = std::make_unique<NiceMock<com::NRF24L01Core>>();
  ON_CALL(*com_nrf_core, InitTransceiver(_, _, _, _, _)).WillByDefault(Return(types::DriverStatus::OK));

  auto unit_under_test = std::make_unique<com::NRF24L01>(std::move(com_msg_buffer), std::move(com_nrf_core));
  ASSERT_EQ(unit_under_test->NRFInit(), types::DriverStatus::OK);
}

TEST_F(ComNRF24L01Tests, nrfinit_not_successful) {
  auto com_msg_buffer = std::make_unique<NiceMock<com::ComMessageBuffer>>();

  auto com_nrf_core = std::make_unique<NiceMock<com::NRF24L01Core>>();
  ON_CALL(*com_nrf_core, InitTransceiver(_, _, _, _, _)).WillByDefault(Return(types::DriverStatus::HAL_ERROR));

  auto unit_under_test = std::make_unique<com::NRF24L01>(std::move(com_msg_buffer), std::move(com_nrf_core));
  ASSERT_EQ(unit_under_test->NRFInit(), types::DriverStatus::HAL_ERROR);
}

}  // namespace