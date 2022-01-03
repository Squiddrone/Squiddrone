#ifndef SRC_TYPES_COM_TYPES_HPP_
#define SRC_TYPES_COM_TYPES_HPP_

#include <cstdint>
#include <vector>

namespace types {

/// Max length for com message frames.
static constexpr std::uint8_t COM_MAX_FRAME_LENGTH = 32;
static constexpr std::uint8_t COM_MAX_DATA_FIELD_LENGTH = 30;

/// Type alias for com message frame datatype
using com_msg_frame = std::vector<std::uint8_t>;

enum class PutDataTarget : std::uint8_t {
  TARGET_FRONT = 0x00,
  TARGET_BACK = 0xff,
  TARGET_LEFT = 0b00000001,
  TARGET_RIGHT = 0b11111110,
  TARGET_ABOVE = 0b00000010,
  TARGET_BELOW = 0b11111101,
  TARGET_GROUND_CONTROL = 0xaa
};

enum class ComPacketType : std::uint8_t {
  TELEMETRY_PACKET = 0,
  COM_ADDR_CONFIG_PACKET
};

/// Packet setup
static constexpr std::uint8_t OFFSET_TYPE = 0U;
static constexpr std::uint8_t OFFSET_TARGET = 1U;
static constexpr std::uint8_t OFFSET_DATA = 2U;

struct ComDataPacket {
  ComPacketType type;
  types::PutDataTarget target;
  std::vector<std::uint8_t> data;

  com_msg_frame Serialize() {
    std::vector<std::uint8_t> serialized_data;

    serialized_data.push_back(static_cast<std::uint8_t>(type));
    serialized_data.push_back(static_cast<std::uint8_t>(target));
    serialized_data.insert(serialized_data.end(), data.begin(), data.end());

    return serialized_data;
  }

  void Deserialize(com_msg_frame msg_frame) {
    type = static_cast<ComPacketType>(msg_frame.at(OFFSET_TYPE));
    target = static_cast<types::PutDataTarget>(msg_frame.at(OFFSET_TARGET));
    data.insert(data.begin(), msg_frame.begin() + OFFSET_DATA, msg_frame.end());
  }
};

}  // namespace types

#endif
