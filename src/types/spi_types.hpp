#ifndef SRC_SPI_SPI_TYPES_HPP_
#define SRC_SPI_SPI_TYPES_HPP_

#include <cinttypes>

namespace types {

static constexpr std::uint8_t SPI_TRANSACTION_LENGTH_LIMIT = 64;
static constexpr std::uint8_t SPI_HAL_TX_RX_TIMEOUT = 100;

}  // namespace types

#endif