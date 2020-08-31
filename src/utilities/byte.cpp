#include "utilities/byte.hpp"

namespace utilities {

auto Byte::Get(void) noexcept -> std::uint8_t {
  return byte_;
}

auto Byte::SetBit(std::uint8_t bit_number_between_0_and_7) noexcept -> void {
  byte_ = SetBitInByte(byte_, bit_number_between_0_and_7);
}

auto Byte::SetBitInByte(std::uint8_t byte, std::uint8_t bit_number_between_0_and_7) noexcept -> std::uint8_t {
  return static_cast<std::uint8_t>(byte | 1 << bit_number_between_0_and_7);
}

auto Byte::ClearBit(std::uint8_t bit_number_between_0_and_7) noexcept -> void {
  byte_ = static_cast<std::uint8_t>(byte_ & ~SetBitInByte(0, bit_number_between_0_and_7));
}

}  // namespace utilities