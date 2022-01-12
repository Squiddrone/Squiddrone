#include "ota_config.hpp"

namespace types {

auto OtaConfigPacket::EncodeAddressConfigPacket(PutDataTarget target, data_pipe_address address) noexcept -> ota_config_data {
  ota_config_data return_value(32, 0);
  return_value.at(START_CONFIG_DATA_ID) = ID_CONFIG_ADDRESS;
  return_value.at(START_ADDR_TARGET_CONFIG_DATA) = static_cast<std::uint8_t>(target);
  std::copy(address.begin(), address.end(), return_value.begin() + START_ADDR_CONFIG_DATA);
  return return_value;
}

auto OtaConfigPacket::DecodeAddressConfigPacket(ota_config_data config_data) noexcept -> std::pair<PutDataTarget, data_pipe_address> {
  data_pipe_address return_address{0};
  if (config_data.at(START_CONFIG_DATA_ID) != ID_CONFIG_ADDRESS) {
    return {PutDataTarget::TARGET_INVALID, return_address};
  }

  std::copy(config_data.begin() + START_ADDR_CONFIG_DATA,
            config_data.begin() + END_ADDR_CONFIG_DATA,
            return_address.begin());

  PutDataTarget return_target = static_cast<types::PutDataTarget>(config_data.at(START_ADDR_TARGET_CONFIG_DATA));

  return {return_target, return_address};
}

}  // namespace types