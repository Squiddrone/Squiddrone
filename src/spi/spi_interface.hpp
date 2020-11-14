#ifndef SRC_SPI_SPI_INTERFACE_HPP_
#define SRC_SPI_SPI_INTERFACE_HPP_

#include <cstdint>
#include <vector>

#include <spi_types.hpp>

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
   * @brief Perform an SPI Tx/Rx transaction. The transaction is bidirectional. While MOSI data are transmitted, the incoming MISO data are 
   * stored in the miso_data_buffer. The maximum length of any SPI transaction is limited to a maximum length defined in
   * SPI_TRANSACTION_BUFFER_SIZE_LIMIT. Transaction buffer size for both buffers is determined by the MOSI buffer.
   * 
   * @param miso_data_buffer Reference to buffer for received data. Has to be provided by the caller.
   * @param mosi_data_buffer Reference to buffer holding the data to be transmitted. Has to be provided by the caller.
   * @return spi::SPIStatus Status information about the success of the transmission. See SPIStatus for details.
   */
  virtual auto Transfer(std::vector<std::uint8_t> &miso_data_buffer, std::vector<std::uint8_t> &mosi_data_buffer) noexcept -> types::SPIStatus = 0;
};
}  // namespace spi

#endif