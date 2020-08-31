#include "utilities/byte.hpp"

namespace utilities {

auto Byte::Get(void) noexcept -> std ::uint8_t {
  return byte_;
}

}  // namespace utilities