#ifndef SRC_COM_COM_NRF24L01_CORE_HPP_
#define SRC_COM_COM_NRF24L01_CORE_HPP_

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
#include "uart_print_mock.hpp"
#endif
namespace com {

class NRF24L01Core {
 public:
  //Pipe configuration
  auto EnableDataPipe(DataPipe pipe_no) noexcept -> types::DriverStatus;
  auto DisableDataPipe(DataPipe pipe_no) noexcept -> types::DriverStatus;

  auto SetPipeAddress(DataPipe pipe_no, data_pipe_address pipe_addr) noexcept -> types::DriverStatus;
  auto GetPipeAddress(DataPipe pipe_no) noexcept -> std::pair<types::DriverStatus, data_pipe_address>;

  auto SetRxPayloadSize(DataPipe pipe_no, std::size_t payload_size) const noexcept -> types::DriverStatus;
  auto EnableAutoAck(DataPipe pipe_no) noexcept -> types::DriverStatus;

  // Mode switching
  auto InitTx(data_pipe_address tx_target_address) noexcept -> types::DriverStatus;
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
  auto MaskInterruptOnIntPin(MaskeableInterrupts interrupt) -> types::DriverStatus;
  auto SetChipEnable(State power_state) noexcept -> types::DriverStatus;
  // Not sure if we ever need this
  // auto SetLNAGain(State state) noexcept -> types::DriverStatus;

  // General protocol configuration
  auto SetAddressWidth(DataPipeAddressWidth address_width) noexcept -> types::DriverStatus;
  auto EnableCRC() noexcept -> types::DriverStatus;
  auto SetCRCEncodingScheme(CRCEncodingScheme encoding_scheme) noexcept -> types::DriverStatus;
  auto ConfigAutoRetransmission(AutoRetransmissionDelay delay, AutoRetransmitCount count) noexcept -> types::DriverStatus;

  // Status register access
  auto GetIRQFlags() noexcept -> std::pair<types::DriverStatus, std::uint8_t>;
  //auto CarrierDetected() noexcept -> bool;

  // Payload
  auto SetTxPayload(std::vector<std::uint8_t> &payload) noexcept -> types::DriverStatus;
  auto GetRxPayload(std::vector<std::uint8_t> &payload) noexcept -> types::DriverStatus;

  explicit NRF24L01Core(std::unique_ptr<NRF24L01SpiProtocol> spi_protocol) : spi_protocol_(std::move(spi_protocol)),
                                                                             irq_flags(0),
                                                                             current_operation_mode_(com::OperationMode::UNDEFINED),
                                                                             is_initialized_(false) {}
  NRF24L01Core() = delete;
  virtual ~NRF24L01Core() = default;

 private:
  std::unique_ptr<NRF24L01SpiProtocol> spi_protocol_;
  std::uint8_t irq_flags;
  OperationMode current_operation_mode_;
  bool is_initialized_;
};
}  // namespace com

#endif