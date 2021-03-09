#include "stm32g4xx_hal.h"

namespace spi {

/**
 * @brief Valid values for chip select pin setting
 * 
 */
enum class PinSetting : bool {
  ACTIVE = true,
  INACTIVE = false
};

/**
 * @brief Chip select active state setting
 * 
 */
enum class CSActiveState : uint8_t {
  ACTIVE_LOW = 0,
  ACTIVE_HIGH
};

/**
 * @brief Class to control the chip select GPIO pin
 * 
 */
class CSPin {
 private:
  GPIO_TypeDef *peripheral_;
  uint16_t gpio_pin_;
  CSActiveState active_state_;
  GPIO_PinState active_;
  GPIO_PinState inactive_;
  auto SetCS(PinSetting pin_setting) noexcept -> void;
  auto MapActiveStateToPinSetting() -> void;

 public:
  explicit CSPin(GPIO_TypeDef *peripheral,
                 uint16_t gpio_pin,
                 CSActiveState active_state) : peripheral_(peripheral),
                                               gpio_pin_(gpio_pin),
                                               active_state_(active_state) { MapActiveStateToPinSetting(); };
  auto SetCSActive() noexcept -> void;
  auto SetCSInactive() noexcept -> void;
};

}  // namespace spi