#ifndef SRC_UTILITIES_SLEEP_HPP_
#define SRC_UTILITIES_SLEEP_HPP_

#include "stm32g4xx_hal.h"

namespace utilities {

auto Sleep(uint32_t sleep_time_in_ms) noexcept -> void;

}  // namespace utilities

#endif