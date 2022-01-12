#ifndef SRC_COM_COM_NRF24L01_CORE_HPP_
#define SRC_COM_COM_NRF24L01_CORE_HPP_

#include "com_nrf24l01_error_handler.hpp"
#include "com_nrf24l01_reg.hpp"
#include "com_nrf24l01_types.hpp"
#include "com_types.hpp"
#include "mcu_settings.h"
#include "stm32g4xx_hal.h"

#ifndef UNIT_TEST
#include "com_nrf24l01_spi_protocol.hpp"
#include "utilities/byte.hpp"
#include "utilities/sleep.hpp"
#else
#include "byte_mock.hpp"
#include "com_nrf24l01_spi_protocol_mock.hpp"
#include "sleep_mock.hpp"
#endif
namespace com {
/**
 * @brief Control the main features of the NRF24L01 device.
 * 
 */
class NRF24L01Core {
 public:
  //Pipe configuration
  /**
   * @brief Set enable bit in data pipe register.
   * 
   * @param pipe_no Pipe that shall be enabled. See com::DataPipe for details.
   * @return types::DriverStatus 
   */
  auto EnableDataPipe(DataPipe pipe_no) noexcept -> types::DriverStatus;

  /**
   * @brief Clear enable bit in the data pipe register.
   * 
   * @param pipe_no Pipe that shall be disabled. See com::DataPipe for details.
   * @return types::DriverStatus 
   */
  auto DisableDataPipe(DataPipe pipe_no) noexcept -> types::DriverStatus;

  /**
   * @brief Set the Pipe Address
   * 
   * @param pipe_no The pipe for which the address shall be set.
   * @param pipe_addr An array of five address bytes. See types::data_pipe_address. 
   * Note that for pipes 2 through 5 only the first byte in the array is relevant, 
   * other bytes may be zero.
   * @return types::DriverStatus 
   */
  auto SetPipeAddress(DataPipe pipe_no, types::data_pipe_address pipe_addr) noexcept -> types::DriverStatus;

  /**
   * @brief Get the Pipe Address
   * 
   * @param pipe_no The pipe to retrieve the address from.
   * @return std::pair<types::DriverStatus, data_pipe_address> 
   */
  auto GetPipeAddress(DataPipe pipe_no) noexcept -> std::pair<types::DriverStatus, types::data_pipe_address>;

  /**
   * @brief Set the Rx Payload Size
   * 
   * @param pipe_no Pipe to set the payload size.
   * @param payload_size Payload size in bytes.
   * @return types::DriverStatus 
   */
  auto SetRxPayloadSize(DataPipe pipe_no, std::size_t payload_size) const noexcept -> types::DriverStatus;

  /**
   * @brief Set autoack bit in configuration register.
   * 
   * @param pipe_no The pipe for which autoack shall be enabled.
   * @return types::DriverStatus 
   */
  auto EnableAutoAck(DataPipe pipe_no) noexcept -> types::DriverStatus;

  // Mode switching
  /**
   * @brief Make the device ready for transmission mode.
   * 
   * @param tx_target_address The address of the transmission target. See com::data_pipe_address.
   * @return types::DriverStatus 
   */
  auto InitTx(types::data_pipe_address tx_target_address) noexcept -> types::DriverStatus;

  /**
   * @brief Switch the device in reception mode.
   * @param base_address The units own address.
   * 
   * @return types::DriverStatus 
   */
  auto InitRx(types::data_pipe_address base_address) noexcept -> types::DriverStatus;

  // Transceiver hardware configuration
  /**
   * @brief Configuration of the transceiver.
   * 
   * @param channel The RF channel frequency determines the center of the channel used by the nRF24L01. The channel occupies a bandwidth of 1MHz at 1Mbps and 2MHz at 2Mbps.
   * nRF24L01 can operate on frequencies from 2.400GHz to 2.525GHz. The resolution of the RF channel frequency setting is 1MHz.
   * At 2Mbps the channel occupies a bandwidth wider than the resolution of the RF channel frequency setting.
   * To ensure non-overlapping channels in 2Mbps mode, the channel spacing must be 2MHz or more.
   * At 1Mbps the channel bandwidth is the same as the resolution of the RF frequency setting.
   * The RF channel frequency is set by the channel value according to the following formula: F0= 2400 + channel [MHz]
   * A transmitter and a receiver must be programmed with the same RF channel frequency to be able to com- municate with each other.
   * @param data_rate Transmission date rate. See com::DataRateSetting.
   * @param rf_power Transmission RF power. See com::RFPowerSetting.
   * @param encoding_scheme CRC encoding scheme. See com::CRCEncodingScheme.
   * @param base_address The drones own address.
   * @return types::DriverStatus 
   */
  auto InitTransceiver(std::uint8_t channel,
                       DataRateSetting data_rate,
                       RFPowerSetting rf_power,
                       CRCEncodingScheme encoding_scheme,
                       types::data_pipe_address base_address) noexcept -> types::DriverStatus;

  /**
   * @brief Set the Operation Mode.
   * 
   * @param mode Operation mode of the device. See com::OperationMode.
   * @return types::DriverStatus 
   */
  auto SetOperationMode(OperationMode mode) noexcept -> types::DriverStatus;

  /**
   * @brief Set the Power State
   * 
   * @param power_state Power state of the device. Power up or power down mode. See com::State.
   * @return types::DriverStatus 
   */
  auto SetPowerState(State power_state) noexcept -> types::DriverStatus;

  /**
   * @brief Set RF channel frequency. Is called by InitTransceiver.
   * 
   * @param channel RF channel frequency.
   * @return types::DriverStatus 
   */
  auto SetRFChannel(std::uint8_t channel) noexcept -> types::DriverStatus;

  /**
   * @brief Set the Data Rate
   * 
   * @param data_rate Transmission data rate. Called by InitTransceiver. See com::DataRateSetting.
   * @return types::DriverStatus 
   */
  auto SetDataRate(DataRateSetting data_rate) noexcept -> types::DriverStatus;

  /**
   * @brief Set RF output power. Called by InitTransceiver. See com::RFPowerSetting.
   * 
   * @param rf_power RF power setting.
   * @return types::DriverStatus 
   */
  auto SetRFOutputPower(RFPowerSetting rf_power) noexcept -> types::DriverStatus;

  /**
   * @brief Select interrupts that shall not lead to a interrupt pin change.
   * 
   * @param interrupt Interrupt to be masked out. See com::MasekableInterrupts.
   * @return types::DriverStatus 
   */
  auto MaskInterruptOnIntPin(MaskeableInterrupts interrupt) -> types::DriverStatus;

  /**
   * @brief Set the Chip Enable pin state.
   * 
   * @param chip_enable_state State of the chip enable pin. See com::State.
   * @return types::DriverStatus 
   */
  auto SetChipEnable(State chip_enable_state) noexcept -> types::DriverStatus;

  // General protocol configuration
  /**
   * @brief Set the Address Width
   * 
   * @param address_width Address width setting. See com::DataPipeAddressWidth.
   * @return types::DriverStatus 
   */
  auto SetAddressWidth(DataPipeAddressWidth address_width) noexcept -> types::DriverStatus;

  /**
   * @brief Enable CRC mode.
   * 
   * @return types::DriverStatus 
   */
  auto EnableCRC() noexcept -> types::DriverStatus;

  /**
   * @brief Set the CRC encoding scheme. Called by InitTransceiver. See also com::CRCEncodingScheme.
   * 
   * @param encoding_scheme 
   * @return types::DriverStatus 
   */
  auto SetCRCEncodingScheme(CRCEncodingScheme encoding_scheme) noexcept -> types::DriverStatus;

  /**
   * @brief Configure delay and max. count for automatic retransmission after transmission failure.
   * 
   * @param delay Retransmission delay. See also com::AutoRetransmissionDelay.
   * @param count Retransmission count. See also com::AutoRetransmitCount.
   * @return types::DriverStatus 
   */
  auto ConfigAutoRetransmission(AutoRetransmissionDelay delay, AutoRetransmitCount count) noexcept -> types::DriverStatus;

  // Status register access
  /**
   * @brief Read and clear the IRQ flag register of the device.
   * 
   * @return std::pair<types::DriverStatus, std::uint8_t> 
   */
  auto GetIRQFlags() noexcept -> std::pair<types::DriverStatus, std::uint8_t>;

  // Payload
  /**
   * @brief Set the Tx Payload
   * 
   * @param payload Data to be transmitted.
   * @return types::DriverStatus 
   */

  auto SetTxPayload(std::vector<std::uint8_t> &payload) noexcept -> types::DriverStatus;

  /**
   * @brief Get the Rx Payload
   * 
   * @param payload Get the top content of the rx fifo buffer.
   * @return types::DriverStatus 
   */
  auto GetRxPayload(std::vector<std::uint8_t> &payload) noexcept -> types::DriverStatus;

  /**
   * @brief Construct a new NRF24L01Core object
   * 
   * @param spi_protocol Unique pointer to a spi protocol object. See NRF24L01SpiProtocol.
   */
  explicit NRF24L01Core(std::unique_ptr<NRF24L01SpiProtocol> spi_protocol) : spi_protocol_(std::move(spi_protocol)),
                                                                             current_operation_mode_(com::OperationMode::UNDEFINED),
                                                                             is_initialized_(false) {}

  /**
   * @brief Default constructor is not used.
   * 
   */
  NRF24L01Core() = delete;

  /**
   * @brief Destroy the NRF24L01Core object
   * 
   */
  virtual ~NRF24L01Core() = default;

 private:
  std::unique_ptr<NRF24L01SpiProtocol> spi_protocol_;
  OperationMode current_operation_mode_;
  bool is_initialized_;
};
}  // namespace com

#endif