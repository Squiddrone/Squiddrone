#ifndef SRC_TYPES_OTA_CONFIG_TYPES_HPP_
#define SRC_TYPES_OTA_CONFIG_TYPES_HPP_

#include <array>
#include <cstdint>
#include <vector>

#include "com_types.hpp"

namespace types {

using ota_config_data = std::vector<std::uint8_t>;

/**
 * @brief Data structure for address configuration data is as follows:
 *  ________________________________________
 * | ID     | Address | PutDataPacketTarget |
 * |________|_________|_____________________|
 * | 1 byte | 5 bytes | 1 byte              |
 * |________|_________|_____________________|
 */

/// Position for config data id.
static constexpr std::uint8_t START_OTA_ID = 0;
/// Begin of address data.
static constexpr std::uint8_t START_OTA_ADDR_DATA = 1;
/// End of address data.
static constexpr std::uint8_t END_ADDR_CONFIG_DATA = 6;
/// Begin of address target information.
static constexpr std::uint8_t START_ADDR_TARGET_CONFIG_DATA = 7;

/// ID for address configuration data.
enum class OtaConfigTypeId : std::uint8_t {
  CONFIGURE_ADDRESS
};

/**
 * @brief Data packet for over the air configuration.
 *
 */
struct OtaConfigPacket : public ComDataPacket {
  auto GetConfigTypeId() noexcept -> OtaConfigTypeId {
    return static_cast<OtaConfigTypeId>(data.at(START_OTA_ID));
  }

  auto EncodeAddressConfigPacket(PutDataPacketTarget target, data_pipe_address address) noexcept -> void {
    ota_config_data return_value(32, 0);
    return_value.at(START_OTA_ID) = static_cast<std::uint8_t>(OtaConfigTypeId::CONFIGURE_ADDRESS);
    return_value.at(START_ADDR_TARGET_CONFIG_DATA) = static_cast<std::uint8_t>(target);
    std::copy(address.begin(), address.end(), return_value.begin() + START_OTA_ADDR_DATA);
    data = return_value;
  }

  auto DecodeAddressConfigPacket() noexcept -> std::pair<PutDataPacketTarget, data_pipe_address> {
    data_pipe_address return_address{0};
    if (data.at(START_OTA_ID) != static_cast<std::uint8_t>(OtaConfigTypeId::CONFIGURE_ADDRESS)) {
      return {PutDataPacketTarget::TARGET_INVALID, return_address};
    }

    std::copy(data.begin() + START_OTA_ADDR_DATA,
              data.begin() + END_ADDR_CONFIG_DATA,
              return_address.begin());

    PutDataPacketTarget return_target = static_cast<types::PutDataPacketTarget>(data.at(START_ADDR_TARGET_CONFIG_DATA));

    return {return_target, return_address};
  }

  OtaConfigPacket() : ComDataPacket() {
    type = types::ComDataPacketType::COM_CONFIG_PACKET;
  };

  ~OtaConfigPacket() = default;
};

}  // namespace types

#endif
