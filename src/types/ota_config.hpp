#ifndef SRC_TYPES_OTA_CONFIG_TYPES_HPP_
#define SRC_TYPES_OTA_CONFIG_TYPES_HPP_

#include <array>
#include <cstdint>
#include <vector>

#include "com_types.hpp"

namespace types {

using ota_config_data = std::vector<std::uint8_t>;

/// Position for config data id.
static constexpr std::uint8_t OTA_ID_START = 0;
/// Maximum length for ota data segment
static constexpr std::uint8_t OTA_DATA_MAX_LEN = 30;

/// ID for address configuration data.
enum class OtaConfigTypeId : std::uint8_t {
  CONFIGURE_ADDRESS
};

namespace ota_addr_config {

/**
 * @brief Data structure for address configuration data is as follows:
 *  ________________________________________
 * | ID     | Address | ComPartnerId        |
 * |________|_________|_____________________|
 * | 1 byte | 5 bytes | 1 byte              |
 * |________|_________|_____________________|
 */

/// Begin of address data.
static constexpr std::uint8_t ADDR_DATA_START = 1;
/// End of address data.
static constexpr std::uint8_t ADDR_DATA_END = 6;
/// Begin of address target information.
static constexpr std::uint8_t PARTNER_ID_START = 7;

}  // namespace ota_addr_config

/**
 * @brief Data packet for over the air configuration.
 *
 */
struct OtaConfigPacket : public ComDataPacket {
  auto GetConfigTypeId() noexcept -> OtaConfigTypeId {
    return static_cast<OtaConfigTypeId>(data.at(OTA_ID_START));
  }

  inline auto EncodeAddressConfigPacket(ComPartnerId target, data_pipe_address address) noexcept -> void {
    ota_config_data return_value(OTA_DATA_MAX_LEN);
    return_value.at(OTA_ID_START) = static_cast<std::uint8_t>(OtaConfigTypeId::CONFIGURE_ADDRESS);
    return_value.at(ota_addr_config::PARTNER_ID_START) = static_cast<std::uint8_t>(target);
    std::copy(address.begin(), address.end(), return_value.begin() + ota_addr_config::ADDR_DATA_START);
    data = return_value;
  }

  inline auto DecodeAddressConfigPacket() noexcept -> std::pair<ComPartnerId, data_pipe_address> {
    data_pipe_address return_address{0};
    if (data.at(OTA_ID_START) != static_cast<std::uint8_t>(OtaConfigTypeId::CONFIGURE_ADDRESS)) {
      return {ComPartnerId::INVALID, return_address};
    }

    std::copy(data.begin() + ota_addr_config::ADDR_DATA_START,
              data.begin() + ota_addr_config::ADDR_DATA_END,
              return_address.begin());

    ComPartnerId return_target = static_cast<types::ComPartnerId>(data.at(ota_addr_config::PARTNER_ID_START));

    return {return_target, return_address};
  }

  OtaConfigPacket() : ComDataPacket() {
    type = types::ComDataPacketType::COM_CONFIG_PACKET;
  };

  ~OtaConfigPacket() = default;
};

}  // namespace types

#endif
