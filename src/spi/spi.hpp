#ifndef SRC_SPI_SPI_HPP_
#define SRC_SPI_SPI_HPP_

#include <array>
#include <spi_types.hpp>
#include "spi_interface.hpp"
#include "stm32g4xx_hal.h"

//preserve include order
#include "spi_config.h"

namespace spi {

static constexpr std::uint8_t SPI_TRANSACTION_BUFFER_SIZE_LIMIT = 64;
static constexpr std::uint8_t SPI_HAL_TX_RX_TIMEOUT = 100;

/**
 * @brief Valid values for chip select pin setting
 * 
 */
enum class PinSetting : bool {
  HIGH = true,
  LOW = false
};

/**
 * @brief Data structure to hold the chip select GPIO information
 * 
 */
typedef struct CSPinDefinition {
  GPIO_TypeDef *peripheral;
  uint16_t gpio_pin;
} CSPin;

/**
 * @brief Concrete implementation of the SPI interface.
 * 
 */
class SPI final : spi::SPIInterface {
 public:
  SPI() = delete;
  explicit SPI(const CSPin chip_select) : spi::SPIInterface(), chip_select_(chip_select){};
  virtual ~SPI() = default;

  auto Transfer(std::vector<uint8_t> &miso_data_buffer, std::vector<uint8_t> &mosi_data_buffer) noexcept -> types::SPIStatus override;

 private:
  CSPin chip_select_;

  /**
   * @brief Check if buffer size is exceeding maximuzm size.
   * 
   * @param buffer_size Buffer size in bytes.
   * @return true Buffer size is exceeding limits.
   * @return false Buffer size is within limits.
   */
  auto IsBufferSizeExceedingLimits(std::uint8_t buffer_size) noexcept -> bool;

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