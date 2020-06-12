#ifndef SRC_SPI_SPI_INTERFACE_HPP_
#define SRC_SPI_SPI_INTERFACE_HPP_

#include <memory>

#include "spi_status.hpp"

namespace spi {
/**
  * @brief Abstract interface class to access SPI peripheral.
  * 
  */
class SPIInterface {
 public:
  /**
    * @brief Construct a new spi interface object. Default constructor.
    * 
    */
  explicit SPIInterface() = default;

  /**
    * @brief Destroy the spi interface object. Default destructor.
    * 
    */
  virtual ~SPIInterface() = default;

  /**
    * @brief Perform an SPI Tx/Rx transaction.
    * 
    * @param RxData Pointer to buffer for received data.
    * @param TxData Pointer to buffer holding the data to be transmitted.
    * @return spi::SPIStatus Status information about the success of the transmission. See \ref SPIStatus for details.
    */
  virtual auto Transfer(std::unique_ptr<std::uint8_t> RxData, std::unique_ptr<std::uint8_t> TxData) noexcept -> spi::SPIStatus = 0;
};
}  // namespace spi

#endif