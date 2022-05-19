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
  test_packet.EncodeAddressConfigPacket(types::ComPartnerId::SELF, {0xaa, 0xaa, 0xaa, 0xaa, 0xaa});

  EXPECT_EQ(types::ComPartnerId::SELF, static_cast<types::ComPartnerId>(test_packet.data.at(types::ota_addr_config::PARTNER_ID_START)));
}

TEST_F(OTAConfigTests, decode_ota_target_successful) {
  types::OtaConfigPacket test_packet;
  test_packet.EncodeAddressConfigPacket(types::ComPartnerId::SELF, {0xaa, 0xaa, 0xaa, 0xaa, 0xaa});

  EXPECT_EQ(types::ComPartnerId::SELF, test_packet.DecodeAddressConfigPacket().first);
}

TEST_F(OTAConfigTests, decode_ota_target_not_successful) {
  types::OtaConfigPacket test_packet;
  test_packet.EncodeAddressConfigPacket(types::ComPartnerId::SELF, {0xaa, 0xaa, 0xaa, 0xaa, 0xaa});
  test_packet.data.at(types::OTA_ID_START) = 1;

  auto rv = test_packet.DecodeAddressConfigPacket();

  EXPECT_EQ(rv.first, types::ComPartnerId::INVALID);
}
}  // namespace