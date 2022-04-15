#ifndef SRC_TYPES_OTA_CONFIG_TYPES_HPP_
#define SRC_TYPES_OTA_CONFIG_TYPES_HPP_

#include <array>
#include <cstdint>
#include <vector>

#include "com_types.hpp"

namespace types {

using ota_config_data = std::vector<std::uint8_t>;

/**
 * @brief Data structure is as follows:
 *  __________________________________
 * | ID     | Address | PutDataTarget |
 * |________|_________|_______________|
 * | 1 byte | 5 bytes | 1 byte        |
 * |________|_________|_______________|
 */

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
  auto EncodeAddressConfigPacket(PutDataTarget target, data_pipe_address address) noexcept -> ota_config_data;
  auto DecodeAddressConfigPacket(ota_config_data config_data) noexcept -> std::pair<PutDataTarget, data_pipe_address>;

  explicit OtaConfigPacket(ota_config_data config_data) {
    type = types::ComPacketType::COM_CONFIG_PACKET;
  };

  OtaConfigPacket() : ComDataPacket(){};
  ~OtaConfigPacket() = default;
};

}  // namespace types

#endif
