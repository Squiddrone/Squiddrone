#include "sleep.hpp"

#ifdef UNIT_TEST
#define HAL_Delay(x)
#endif

namespace utilities {

auto Sleep(uint32_t sleep_time_in_ms) noexcept -> void {
  HAL_Delay(sleep_time_in_ms);
}

}  // namespace utilities
