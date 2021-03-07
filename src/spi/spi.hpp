#ifndef SRC_SPI_SPI_HPP_
#define SRC_SPI_SPI_HPP_

#include <array>
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

  auto Write(std::vector<std::uint8_t> &mosi_data_buffer) noexcept -> types::DriverStatus override;
  auto Transfer(std::vector<std::uint8_t> &mosi_data_buffer, std::vector<uint8_t> &miso_data_buffer) noexcept -> types::DriverStatus override;

 private:
  CSPin chip_select_;

  auto IsTransactionLengthExceedingLimits(std::uint8_t transaction_length) noexcept -> bool;

  auto IsMisoBufferTooSmall(std::vector<uint8_t> &mosi_buffer, std::vector<uint8_t> &miso_buffer) noexcept -> bool;

  auto SetChipSelectPin(PinSetting pin_state) const noexcept -> void;

  auto GetCSOutputLevel(PinSetting pin_setting) const noexcept -> GPIO_PinState;
};

}  // namespace spi

#endif
