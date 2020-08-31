#ifndef SRC_UTILITIES_BYTE_HPP_
#define SRC_UTILITIES_BYTE_HPP_

#include "cstdint"

namespace utilities {

class Byte {
 public:
  ~Byte() = default;

  Byte(){};
  Byte(std::uint8_t byte) : byte_(byte){};
  auto Get(void) noexcept -> std::uint8_t;
  auto SetBit(std::uint8_t bit_number_between_0_and_7) noexcept -> void;

 private:
  std::uint8_t byte_ = 0;
};

}  // namespace utilities

#endif