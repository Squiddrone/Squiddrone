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
    packet.type = types::ComPacketType::TELEMETRY_PACKET;
    packet.target = types::PutDataTarget::TARGET_GROUND_CONTROL;
    std::vector<std::uint8_t> mock_data(30, 0xAA);
    packet.data = mock_data;
  }
  types::ComDataPacket packet;
};

TEST_F(ComDataPacketTests, serialize_packet) {
    ASSERT_EQ(return_value, msg_frame);
}

TEST_F(ComDataPacketTests, deserialize_packet) {
}

}  // namespace