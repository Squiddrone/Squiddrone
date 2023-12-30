#include "stm32g431xx.h"
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
  /**
   * @brief Construct a new CSPin object.
   *
   * @param peripheral Pointer to the GPIO Peripheral that acts as chip select pin.
   * @param gpio_pin Pin number of the GPIO Peripheral that acts as chip select pin.
   * @param active_state Can be active high or active low, depending on the necessary SPI configuration.
   */
  explicit CSPin(GPIO_TypeDef *peripheral,
                 uint16_t gpio_pin,
                 CSActiveState active_state) : peripheral_(peripheral),
                                               gpio_pin_(gpio_pin),
                                               active_state_(active_state) { MapActiveStateToPinSetting(); };
  /**
   * @brief Activate the chip select pin. Actual pin value (high or low) depends on the
   * selection of active_state.
   *
   */
  auto SetCSActive() noexcept -> void;

  /**
   * @brief Deactivate the chip select pin. Actual pin value (high or low) depends on the
   * selection of active_state.
   *
   */
  auto SetCSInactive() noexcept -> void;
};

}  // namespace spi