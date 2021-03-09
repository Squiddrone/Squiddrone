#include "cspin.hpp"

namespace spi {

auto CSPin::SetCS(PinSetting pin_setting) -> void {
  GPIO_PinState gpio_state = inactive_;

  if (pin_setting == PinSetting::ACTIVE) {
    gpio_state = active_;
  }

  HAL_GPIO_WritePin(peripheral_, gpio_pin_, gpio_state);
}

auto CSPin::SetCSActive() noexcept -> void {
  SetCS(PinSetting::ACTIVE);
}

auto CSPin::SetCSInactive() noexcept -> void {
  SetCS(PinSetting::INACTIVE);
}

auto CSPin::MapActiveStateToPinSetting() -> void {
  active_ = GPIO_PIN_RESET;
  inactive_ = GPIO_PIN_RESET;

  if (active_state_ == CSActiveState::ACTIVE_LOW) {
    inactive_ = GPIO_PIN_SET;
  } else {
    active_ = GPIO_PIN_SET;
  }
}

}  // namespace spi