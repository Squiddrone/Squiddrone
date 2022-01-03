#ifndef SRC_COM_COM_NRF24L01_HPP_
#define SRC_COM_COM_NRF24L01_HPP_

#include "com_interface.hpp"
#include "com_nrf24l01_reg.hpp"
#include "com_nrf24l01_types.hpp"
#ifndef UNIT_TEST
#include "com_nrf24l01_core.hpp"
#include "com_nrf24l01_spi_protocol.hpp"
#include "utilities/byte.hpp"
#else
#include "byte_mock.hpp"
#include "com_nrf24l01_core_mock.hpp"
#include "com_nrf24l01_spi_protocol_mock.hpp"
#endif

namespace com {

/**
 * @brief Driver for the NRF24L01 transceiver. 
 * 
 */
class NRF24L01 final : public ComInterface {
 public:
  auto GetDataPacket() const noexcept -> types::ComDataPacket override;
  auto PutDataPacket(types::PutDataTarget target_id, types::ComDataPacket &packet) noexcept
      -> types::DriverStatus override;
  auto HandleRxIRQ() noexcept -> void;

  explicit NRF24L01(std::unique_ptr<com::ComMessageBuffer> msg_buf,
                    std::unique_ptr<com::NRF24L01Core> nrf) : ComInterface(std::move(msg_buf)),
                                                              nrf_(std::move(nrf)) {
    nrf_->InitTransceiver(com::rf_config::RF_CHANNEL, DataRateSetting::RF_DR_2MBPS, RFPowerSetting::RF_PWR_0DBM, CRCEncodingScheme::CRC_16BIT);
    nrf_->InitRx();
  };
  NRF24L01() = delete;
  virtual ~NRF24L01() = default;

 private:
  std::unique_ptr<NRF24L01Core> nrf_;
  OperationMode current_operation_mode_;
  std::array<data_pipe_address, 6> partner_drone_address = {0};

  auto LookupComPartnerAddress(types::PutDataTarget target_id) noexcept -> data_pipe_address;
  auto HandleTelemetryPacket(types::com_msg_frame &msg_frame) -> types::DriverStatus;
  auto HandleConfigPacket(types::com_msg_frame &msg_frame) -> types::DriverStatus;
};
}  // namespace com

#endif
