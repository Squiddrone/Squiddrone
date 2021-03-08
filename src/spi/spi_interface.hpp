#ifndef SRC_SPI_SPI_INTERFACE_HPP_
#define SRC_SPI_SPI_INTERFACE_HPP_

#include <cstdint>
#include <vector>

#include <error_types.hpp>
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
   * @brief Perform an SPI Write transaction. MISO data are disregarded.
   * 
   * @param mosi_data_buffer Reference to buffer holding the data to be transmitted.
   * @return types::DriverStatus Status information about the success of the transmission.
   */
  virtual auto Write(std::vector<std::uint8_t> &mosi_data_buffer) noexcept -> types::DriverStatus = 0;

  /**
   * @brief Perform an SPI Tx/Rx transaction. The transaction is bidirectional. While MOSI data are transmitted, the incoming MISO data are 
   * stored in the miso_data_buffer. The maximum length of any SPI transaction is limited to a maximum length defined in
   * SPI_TRANSACTION_LENGTH_LIMIT.
   * @param mosi_data_buffer Reference to buffer holding the data to be transmitted. Has to be provided by the caller.
   * @param miso_data_buffer Reference to buffer for received data. Has to be provided by the caller. Must be at least as big as mosi_data_buffer.
   * In case of a read action, miso data buffer length can be used to force the transfer length.
   * @return types::DriverStatus Status information about the success of the transmission. Possible values: 
   * -OK - Transaction finished without errors.
   * -HAL_ERROR - HAL function returned an error status
   * -INPUT_ERROR - Maximum transaction length exceeded or miso buffer too small
   * -TIMEOUT - HAL function returns timeout.
   */
  virtual auto Transfer(std::vector<std::uint8_t> &mosi_data_buffer, std::vector<std::uint8_t> &miso_data_buffer) noexcept -> types::DriverStatus = 0;
};
}  // namespace spi

#endif