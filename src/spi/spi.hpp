#ifndef SRC_SPI_SPI_HPP_
#define SRC_SPI_SPI_HPP_

#include <array>
#include "mcu_settings.h"
#include "spi_interface.hpp"
#include "stm32g4xx_hal.h"

//preserve include order
#include "spi_config.h"

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
 * @brief Data structure to hold the chip select GPIO information
 * 
 */
typedef struct CSPinDefinition {
  GPIO_TypeDef *peripheral;
  uint16_t gpio_pin;
  CSActiveState active_state;
} CSPin;

/**
 * @brief Concrete implementation of the SPI interface.
 * 
 */
class SPI final : spi::SPIInterface {
 public:
  SPI() = delete;
  explicit SPI(const CSPin chip_select) : spi::SPIInterface(), chip_select_(chip_select) { SetChipSelectPin(PinSetting::INACTIVE); };
  virtual ~SPI() = default;

  auto Transfer(std::vector<uint8_t> &mosi_data_buffer, std::vector<uint8_t> &miso_data_buffer) noexcept -> types::DriverStatus override;

 private:
  CSPin chip_select_;

  /**
   * @brief Check if transaction length is exceeding maximum size.
   * 
   * @param transaction_length Transaction length in bytes.
   * @return true Transaction length is exceeding limits.
   * @return false Transaction length is within limits.
   */
  auto IsTransactionLengthExceedingLimits(std::uint8_t transaction_length) noexcept -> bool;

  /**
   * @brief Check if miso buffer is smaller than the mosi buffer.
   * 
   * @param mosi_buffer Reference to the mosi buffer.
   * @param miso_buffer Reference to the miso buffer
   * @return true Miso buffer is too small
   * @return false Miso buffer is large enough.
   */
  auto IsMisoBufferTooSmall(std::vector<uint8_t> &mosi_buffer, std::vector<uint8_t> &miso_buffer) noexcept -> bool;

  /**
   * @brief Set the Chip select GPIO pin.
   * 
   * @param pin_state The desired pin state. High or low.
   * @return void
   */
  auto SetChipSelectPin(PinSetting pin_state) noexcept -> void;
};

}  // namespace spi

#endif
