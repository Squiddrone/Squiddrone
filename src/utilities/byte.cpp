#include "utilities/byte.hpp"

namespace utilities {

auto Byte::Get(void) noexcept -> std::uint8_t {
  return byte_;
}

auto Byte::SetBit(std::uint8_t bit_number_between_0_and_7) noexcept -> void {
  byte_ = static_cast<std::uint8_t>(byte_ | 1 << bit_number_between_0_and_7);
}

}  // namespace utilities