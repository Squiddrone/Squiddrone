#ifndef SRC_TYPES_OTA_CONFIG_TYPES_HPP_
#define SRC_TYPES_OTA_CONFIG_TYPES_HPP_

#include <array>
#include <cstdint>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "com_types.hpp"

namespace types {

using ota_config_data = std::vector<std::uint8_t>;

// Data structure

/// Position for config data id.
static constexpr std::uint8_t START_CONFIG_DATA_ID = 0;
/// Begin of address data.
static constexpr std::uint8_t START_ADDR_CONFIG_DATA = 1;
/// End of address data.
static constexpr std::uint8_t END_ADDR_CONFIG_DATA = 6;
/// Begin of address target information.
static constexpr std::uint8_t START_ADDR_TARGET_CONFIG_DATA = 7;

/// ID for address configuration data.
static constexpr std::uint8_t ID_CONFIG_ADDRESS = 0;

/**
 * @brief Data packet for over the air configuration.
 *
 */
struct OtaConfigPacket : public ComDataPacket {
  MOCK_METHOD((ota_config_data), EncodeAddressConfigPacket, (types::PutDataPacketTarget, types::data_pipe_address), (noexcept));
  auto DecodeAddressConfigPacket(ota_config_data) -> std::pair<types::PutDataPacketTarget, types::data_pipe_address> {
    return {types::PutDataPacketTarget::TARGET_SELF, {0, 0, 0, 0, 0}};
  }
  explicit OtaConfigPacket(ota_config_data config_data) {
    type = types::ComDataPacketType::COM_CONFIG_PACKET;
  };

  OtaConfigPacket() : ComDataPacket(){};
  ~OtaConfigPacket() = default;
};

}  // namespace types

#endif
