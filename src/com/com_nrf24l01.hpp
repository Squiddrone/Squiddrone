#ifndef SRC_COM_COM_NRF24L01_HPP_
#define SRC_COM_COM_NRF24L01_HPP_

#include "com_interface.hpp"
#include "com_nrf24l01_reg.hpp"
#ifndef UNIT_TEST
#include "com_nrf24l01_spi_protocol.hpp"
#else
#include "com_nrf24l01_spi_protocol_mock.hpp"
#endif

namespace com {

/**
 * @brief Driver for the NRF24L01 transceiver. 
 * 
 */
class NRF24L01 final : public ComInterface {
 public:
  auto GetDataPacket() const noexcept -> types::com_msg_frame override;
  auto PutDataPacket(std::uint8_t target_id, types::com_msg_frame &payload) noexcept
      -> types::ComError override;

  explicit NRF24L01(std::unique_ptr<com::ComMessageBuffer> msg_buf,
                    NRF24L01SpiProtocol &spi_protocol) : ComInterface(std::move(msg_buf)), spi_protocol_(spi_protocol){};
  NRF24L01() = delete;
  ~NRF24L01() = default;

 private:
  NRF24L01SpiProtocol &spi_protocol_;
  std::uint8_t irq_flags;

  //Pipe configuration
  auto EnableDataPipe(DataPipe pipe_no) noexcept -> types::DriverStatus;
  auto DisableDataPipe(DataPipe pipe_no) noexcept -> types::DriverStatus;
  /**
   * @brief Set the Tx Address and configure Pipe 0 for ack reception.
   * 
   * @param tx_addr 
   * @return types::DriverStatus 
   */
  auto SetTxAddress(data_pipe_address tx_addr) const noexcept -> types::DriverStatus;
  auto SetRxAddress(DataPipe pipe_no, data_pipe_address rx_addr) const noexcept -> types::DriverStatus;
  auto GetPipeAddress(DataPipe pipe_no) noexcept -> data_pipe_address;
  /**
   * @brief Set the Rx Payload Size per data pipe.
   * 
   * @param pipe_no 
   * @param payload_size Payload size in bytes. 0-32 bytes allowed.
   * @return types::DriverStatus 
   */
  auto SetRxPayloadSize(DataPipe pipe_no, std::size_t payload_size) const noexcept -> types::DriverStatus;
  auto EnableAutoAck(DataPipe pipe_no) noexcept -> types::DriverStatus;

  // Mode switching
  auto InitTx() noexcept -> types::DriverStatus;
  auto InitRx() noexcept -> types::DriverStatus;

  // Transceiver hardware configuration
  auto InitTransceiver(std::uint8_t channel,
                       DataRateSetting data_rate,
                       RFPowerSetting rf_power,
                       CRCEncodingScheme encoding_scheme) noexcept -> types::DriverStatus;
  auto SetOperationMode(OperationMode mode) noexcept -> types::DriverStatus;
  auto SetPowerState(State power_state) noexcept -> types::DriverStatus;
  auto SetRFChannel(std::uint8_t channel) noexcept -> types::DriverStatus;
  auto SetDataRate(DataRateSetting data_rate) noexcept -> types::DriverStatus;
  auto SetRFOutputPower(RFPowerSetting rf_power) noexcept -> types::DriverStatus;
  // Not sure if we ever need this
  auto SetLNAGain(State state) noexcept -> types::DriverStatus;

  // General protocol configuration
  auto SetAddressWidth(DataPipeAddressWidth address_width) noexcept -> types::DriverStatus;
  auto EnableCRC() noexcept -> types::DriverStatus;
  auto SetCRCEncodingScheme(CRCEncodingScheme encoding_scheme) noexcept -> types::DriverStatus;
  auto ConfigAutoRetransmission(AutoRetransmissionDelay delay, AutoRetransmitCount count) noexcept -> types::DriverStatus;

  // Status register access
  auto CarrierDetected() noexcept -> bool;
};
}  // namespace com

#endif
