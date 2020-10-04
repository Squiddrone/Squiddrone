#ifndef SRC_UTILITIES_BYTE_HPP_
#define SRC_UTILITIES_BYTE_HPP_

#include "cstdint"

namespace utilities {

class Byte {
 public:
  Byte() = delete;
  ~Byte() = default;

  explicit Byte(std::uint8_t byte) : byte_(byte){};

  auto Get(void) noexcept -> std::uint8_t {
    return byte_;
  }

  auto SetBit(std::uint8_t bit_number_between_0_and_7) noexcept -> void {
    byte_ = SetBitInByte(byte_, bit_number_between_0_and_7);
  }

  auto ClearBit(std::uint8_t bit_number_between_0_and_7) noexcept -> void {
    byte_ = static_cast<std::uint8_t>(byte_ & ~SetBitInByte(0, bit_number_between_0_and_7));
  }

 private:
  auto SetBitInByte(std::uint8_t byte, std::uint8_t bit_number_between_0_and_7) noexcept -> std::uint8_t {
    return static_cast<std::uint8_t>(byte | 1 << bit_number_between_0_and_7);
  }

  std::uint8_t byte_ = 0;
};

}  // namespace utilities

#endif