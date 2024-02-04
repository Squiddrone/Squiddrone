#ifndef SRC_TYPES_COM_RC_TYPES_HPP_
#define SRC_TYPES_COM_RC_TYPES_HPP_

#include "com_types.hpp"

struct RCDataPacket : public types::ComDataPacket {
  union {
    float f;
    uint8_t u[sizeof(float)];
  } throttle_cast;

  inline auto Decode() noexcept -> float {
    std::copy(data.begin(),
              data.begin() + sizeof(float),
              std::begin(throttle_cast.u));
    return throttle_cast.f;
  }

  RCDataPacket() : types::ComDataPacket(){};
  explicit RCDataPacket(const types::ComDataPacket &p) : types::ComDataPacket() {
    data = p.data;
  }
  ~RCDataPacket() = default;
};

#endif