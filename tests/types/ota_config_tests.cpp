#include "ota_config.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::ElementsAre;
using ::testing::Invoke;
using ::testing::NiceMock;
using ::testing::Return;
namespace {
class OTAConfigTests : public ::testing::Test {
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

TEST_F(OTAConfigTests, ota_config_type_id_correct) {
  types::OtaConfigPacket test_packet;
  EXPECT_EQ(types::ComDataPacketType::COM_CONFIG_PACKET, test_packet.type);
}

TEST_F(OTAConfigTests, encode_ota_target_successful) {
  types::OtaConfigPacket test_packet;
  test_packet.EncodeAddressConfigPacket(types::PutDataPacketTarget::TARGET_SELF, {0xaa, 0xaa, 0xaa, 0xaa, 0xaa});

  EXPECT_EQ(types::PutDataPacketTarget::TARGET_SELF, static_cast<types::PutDataPacketTarget>(test_packet.data.at(types::START_ADDR_TARGET_CONFIG_DATA)));
}

TEST_F(OTAConfigTests, decode_ota_target_successful) {
  types::OtaConfigPacket test_packet;
  test_packet.EncodeAddressConfigPacket(types::PutDataPacketTarget::TARGET_SELF, {0xaa, 0xaa, 0xaa, 0xaa, 0xaa});

  EXPECT_EQ(types::PutDataPacketTarget::TARGET_SELF, test_packet.DecodeAddressConfigPacket().first);
}

TEST_F(OTAConfigTests, decode_ota_target_not_successful) {
  types::OtaConfigPacket test_packet;
  test_packet.EncodeAddressConfigPacket(types::PutDataPacketTarget::TARGET_SELF, {0xaa, 0xaa, 0xaa, 0xaa, 0xaa});
  test_packet.data.at(types::START_OTA_ID) = 1;

  auto rv = test_packet.DecodeAddressConfigPacket();

  EXPECT_EQ(rv.first, types::PutDataPacketTarget::TARGET_INVALID);
}
}  // namespace