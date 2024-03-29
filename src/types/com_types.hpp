#ifndef SRC_TYPES_COM_TYPES_HPP_
#define SRC_TYPES_COM_TYPES_HPP_

#include <array>
#include <cstdint>
#include <vector>

namespace types {

/// Max length for com message frames.
static constexpr std::uint8_t COM_MAX_FRAME_LENGTH = 32;
/// Max length for the data field of a data packet.
static constexpr std::uint8_t COM_MAX_DATA_FIELD_LENGTH = 30;

/// Type alias for com frame datatype
using com_frame = std::vector<std::uint8_t>;

/// Type alias for data pipe address definition.
using data_pipe_address = std::array<std::uint8_t, 5>;

/// Target directions during formation flight
enum class ComPartnerId : std::int8_t {
  INVALID = -1,
  PARTNER_ID_0 = 0,
  PARTNER_ID_1,
  PARTNER_ID_2,
  PARTNER_ID_3,
  PARTNER_ID_4,
  PARTNER_ID_5,
  GROUND_CONTROL,
  FALLBACK,
  SELF,
};

/// Packet types
enum class ComDataPacketType : std::uint8_t {
  /// Flight telemetry data
  TELEMETRY_PACKET = 0,
  /// Application level information (i.e. flight trajectory)
  APPDATA_PACKET,
  /// Packet to configure the target.
  COM_CONFIG_PACKET
};

// Packet structure
/// Packet type position in data frame.
static constexpr std::uint8_t OFFSET_TYPE = 0U;
/// Packet target position in data frame.
static constexpr std::uint8_t OFFSET_TARGET = 1U;
/// Packet data position in data frame.
static constexpr std::uint8_t OFFSET_DATA = 2U;

/// Data packet definition. Also defines Serializer and Deserializer.
struct ComDataPacket {
  ComDataPacketType type;
  types::ComPartnerId partner_id;
  std::vector<std::uint8_t> data;

  /**
   * @brief Serialize entire package content.
   *
   * @return com_frame
   */
  com_frame Serialize() {
    std::vector<std::uint8_t> serialized_data;

    serialized_data.push_back(static_cast<std::uint8_t>(type));
    serialized_data.push_back(static_cast<std::uint8_t>(partner_id));
    serialized_data.insert(serialized_data.end(), data.begin(), data.end());

    return serialized_data;
  }

  /**
   * @brief Deserialize data frame and populate package struct.
   *
   * @param msg_frame
   */
  void Deserialize(com_frame msg_frame) {
    type = static_cast<ComDataPacketType>(msg_frame.at(OFFSET_TYPE));
    partner_id = static_cast<types::ComPartnerId>(msg_frame.at(OFFSET_TARGET));
    data.insert(data.begin(), msg_frame.begin() + OFFSET_DATA, msg_frame.end());
  }
};

}  // namespace types

#endif
