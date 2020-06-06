#ifndef TESTS_MOCK_LIBRARIES_PROPULSION_LITTLE_BEE_20_A_HPP_
#define TESTS_MOCK_LIBRARIES_PROPULSION_LITTLE_BEE_20_A_HPP_

#include <cstdint>

#include "esc_mock.hpp"
#include "stm32g4xx.h"

namespace propulsion {
class LittleBee20A : public Esc {
 public:
  LittleBee20A(TIM_HandleTypeDef* timer, std::uint32_t channel) : Esc(), timer_(timer), channel_(channel) {}
  TIM_HandleTypeDef* timer_;
  std::uint32_t channel_;
};
}  // namespace propulsion

#endif