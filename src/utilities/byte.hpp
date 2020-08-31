#ifndef SRC_UTILITIES_BYTE_HPP_
#define SRC_UTILITIES_BYTE_HPP_

#include "cstdint"

namespace utilities {

class Byte {
 public:
  ~Byte() = default;

  Byte(){};
  Byte(std::uint8_t byte) : byte_(byte){};
  auto Get(void) noexcept -> std ::uint8_t;

 private:
  std::uint8_t byte_ = 0;
};

}  // namespace utilities

#endif