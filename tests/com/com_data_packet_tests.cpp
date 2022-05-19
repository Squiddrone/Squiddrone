#include <algorithm>
#include "com_types.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::ElementsAre;
using ::testing::NiceMock;
using ::testing::Return;
namespace {
class ComDataPacketTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    packet.type = types::ComDataPacketType::TELEMETRY_PACKET;
    packet.partner_id = types::ComPartnerId::GROUND_CONTROL;
    std::vector<std::uint8_t> mock_data(30, 0xAA);
    packet.data = mock_data;
    frame.resize(32);
    std::fill(frame.begin(), frame.end(), 0xaa);
    frame.at(0) = static_cast<std::uint8_t>(types::ComDataPacketType::TELEMETRY_PACKET);
    frame.at(1) = static_cast<std::uint8_t>(types::ComPartnerId::GROUND_CONTROL);
  }
  types::ComDataPacket packet;
  types::com_frame frame;
};

TEST_F(ComDataPacketTests, serialize_packet) {
  auto return_value = packet.Serialize();

  ASSERT_EQ(return_value, frame);
}

TEST_F(ComDataPacketTests, deserialize_packet) {
  types::ComDataPacket test_packet;
  test_packet.Deserialize(frame);

  ASSERT_EQ(test_packet.type, packet.type);
  ASSERT_EQ(test_packet.partner_id, packet.partner_id);
  ASSERT_EQ(test_packet.data, packet.data);
}

}  // namespace