#ifndef SRC_TYPES_OTA_CONFIG_TYPES_HPP_
#define SRC_TYPES_OTA_CONFIG_TYPES_HPP_

#include <cstdint>
#include <vector>

#include "com_types.hpp"

namespace types {

using ota_config_data = std::vector<std::uint8_t>;

struct OtaConfigPacket : public ComDataPacket {
  auto MakeAddrConfigPacket(data_pipe_address addr) -> void;

  OtaConfigPacket() = delete;
  explicit OtaConfigPacket(ota_config_data config_data) {
    type = types::ComPacketType::COM_CONFIG_PACKET;
    data = config_data;
  };
  ~OtaConfigPacket() = default;
};

}  // namespace types

#endif
