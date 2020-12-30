#ifndef SRC_COM_COM_NRF24L01_HPP_
#define SRC_COM_COM_NRF24L01_HPP_

#include "com_interface.hpp"
#include "com_nrf24l01_reg.hpp"
#include "spi.hpp"

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

  explicit NRF24L01(std::unique_ptr<com::ComMessageBuffer> msg_buf, spi::CSPinDefinition &cs_pin) : ComInterface(std::move(msg_buf)),
                                                                                                    cs_pin_(cs_pin){};
  NRF24L01() = delete;
  ~NRF24L01() = default;

 private:
  spi::CSPin cs_pin_;
  spi::SPI spi_{cs_pin_};

  //Pipe configuration
  auto EnableDataPipe(DataPipe pipe_no) const noexcept -> types::DriverStatus;
  auto DisableDataPipe(DataPipe pipe_no) const noexcept -> types::DriverStatus;
  /**
   * @brief Set the Tx Address and configure Pipe 0 for ack reception.
   * 
   * @param tx_addr 
   * @return types::DriverStatus 
   */
  auto SetTxAddress(data_pipe_address tx_addr) const noexcept -> types::DriverStatus;
  auto SetRxAddress(DataPipe pipe_no, data_pipe_address rx_addr) const noexcept -> types::DriverStatus;
  /**
   * @brief Set the Rx Payload Size per data pipe.
   * 
   * @param pipe_no 
   * @param payload_size Payload size in bytes. 0-32 bytes allowed.
   * @return types::DriverStatus 
   */
  auto SetRxPayloadSize(DataPipe pipe_no, std::size_t payload_size) const noexcept -> types::DriverStatus;
  auto EnableAutoAck(DataPipe pipe_no) const noexcept -> types::DriverStatus;

  // Transceiver hardware configuration
  auto EnableTxMode() const noexcept -> types::DriverStatus;
  auto EnableRxMode() const noexcept -> types::DriverStatus;
  auto SetPowerState(State power_state) const noexcept -> types::DriverStatus;
  auto SetRFChannel(std::uint8_t channel) const noexcept -> types::DriverStatus;
  auto SetDataRate(DataRateSetting data_rate) const noexcept -> types::DriverStatus;
  auto SetRFOutputPower(RFPowerSetting rf_power) const noexcept -> types::DriverStatus;
  // Not sure if we ever need this
  auto SetLNAGain(State state) const noexcept -> types::DriverStatus;

  // General protocol configuration
  auto SetPayloadData() const noexcept -> types::DriverStatus;
  auto SetAddressWidth(DataPipeAddressWidth address_width) const noexcept -> types::DriverStatus;
  auto EnableCRC() const noexcept -> types::DriverStatus;
  auto SetCRCEncodingScheme(CRCEncodingScheme encoding_scheme) const noexcept -> types::DriverStatus;
  auto ConfigAutoRetransmission(AutoRetransmissionDelay delay, AutoRetransmitCount count)
      const noexcept -> types::DriverStatus;

  // Status register access
  auto CarrierDetected() const noexcept -> bool;

  // Helper functions
  auto ReadRegister(std::uint8_t register_address) noexcept -> std::uint8_t;
  auto WriteRegister(std::uint8_t register_address, std::uint8_t register_content) -> types::DriverStatus;
};
}  // namespace com

#endif
