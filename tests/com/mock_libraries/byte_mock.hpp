#ifndef TESTS_COM_MOCK_LIBRARIES_BYTE_MOCK_HPP_
#define TESTS_COM_MOCK_LIBRARIES_BYTE_MOCK_HPP_

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace utilities {

class Byte {
 public:
  explicit Byte(std::uint8_t){};
  MOCK_METHOD(std::uint8_t, Get, (), (noexcept));
  MOCK_METHOD(void, SetBit, (std::uint8_t), (noexcept));
  MOCK_METHOD(void, ClearBit, (std::uint8_t), (noexcept));
  MOCK_METHOD(void, SetLowNibble, (std::uint8_t), (noexcept));
  MOCK_METHOD(void, SetHighNibble, (std::uint8_t), (noexcept));
};
}  // namespace utilities

#endif
