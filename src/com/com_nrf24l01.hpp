#ifndef SRC_COM_COM_NRF24L01_HPP_
#define SRC_COM_COM_NRF24L01_HPP_
#include <algorithm>

#include "com_interface.hpp"
#include "com_nrf24l01_reg.hpp"
#include "com_nrf24l01_types.hpp"
#ifndef UNIT_TEST
#include "com_nrf24l01_core.hpp"
#include "com_nrf24l01_spi_protocol.hpp"
#include "utilities/byte.hpp"
#else
#include "byte_mock.hpp"
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
      -> types::DriverStatus override;
  auto HandleRxIRQ() noexcept -> void;

  explicit NRF24L01(std::unique_ptr<com::ComMessageBuffer> msg_buf,
                    std::unique_ptr<com::NRF24L01Core> nrf) : ComInterface(std::move(msg_buf)),
                                                              nrf_(std::move(nrf)),
                                                              irq_flags(0),
                                                              current_operation_mode_(com::OperationMode::UNDEFINED),
                                                              is_initialized_(false) {
    nrf_->InitTransceiver(com::rf_config::RF_CHANNEL, DataRateSetting::RF_DR_1MBPS, RFPowerSetting::RF_PWR_0DBM, CRCEncodingScheme::CRC_16BIT);
    nrf_->InitRx();
  };
  NRF24L01() = delete;
  virtual ~NRF24L01() = default;

 private:
  std::unique_ptr<NRF24L01Core> nrf_;
  std::uint8_t irq_flags;
  OperationMode current_operation_mode_;
  bool is_initialized_;
};
}  // namespace com

#endif
