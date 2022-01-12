#ifndef SRC_COM_COM_NRF24L01_HPP_
#define SRC_COM_COM_NRF24L01_HPP_

#include "com_interface.hpp"
#include "com_nrf24l01_error_handler.hpp"
#include "com_nrf24l01_reg.hpp"
#include "com_nrf24l01_types.hpp"
#ifndef UNIT_TEST
#include "com_nrf24l01_core.hpp"
#include "com_nrf24l01_spi_protocol.hpp"
#include "ota_config.hpp"
#include "utilities/byte.hpp"
#include "utilities/sleep.hpp"
#else
#include "byte_mock.hpp"
#include "com_nrf24l01_core_mock.hpp"
#include "com_nrf24l01_spi_protocol_mock.hpp"
#include "ota_config_mock.hpp"
#include "sleep_mock.hpp"
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
  /**
   * @brief IRQ handler function is called by HAL layer, when an incoming data frame triggers
   * an interrupt.
   * 
   */
  auto HandleRxIRQ() noexcept -> void;

  /**
   * @brief Call initializing function for NRF.
   * 
   * @return types::DriverStatus 
   */
  auto NRFInit() noexcept -> types::DriverStatus;

  /**
   * @brief Construct a new NRF24L01 object and initialize the transceiver.
   * 
   * @param msg_buf Unique pointer to an object of type com::ComMessageBuffer.
   * @param nrf Unique pointer to an object of type NF24L01Core.
   */
  explicit NRF24L01(std::unique_ptr<com::ComMessageBuffer> msg_buf,
                    std::unique_ptr<com::NRF24L01Core> nrf) : ComInterface(std::move(msg_buf)),
                                                              nrf_(std::move(nrf)){};

  /**
   * @brief Default constructor is not used.
   * 
   */
  NRF24L01() = delete;

  /**
   * @brief Destroy the NRF24L01 object
   * 
   */
  virtual ~NRF24L01() = default;

 private:
  std::unique_ptr<NRF24L01Core> nrf_;
  /**
   * @brief This array holds addresses of all valid put data targets. 
   * Beware: The last line may never change! This is the default address of any NRF as fallback. 
   * See also types::PutDataTarget.
   */
  std::array<types::data_pipe_address, 8> partner_drone_address_{{
      {{0, 0, 0, 0, 0}},
      {{0, 0, 0, 0, 0}},
      {{0, 0, 0, 0, 0}},
      {{0, 0, 0, 0, 0}},
      {{0, 0, 0, 0, 0}},
      {{0, 0, 0, 0, 0}},
      {{0, 0, 0, 0, 0}},
      {{0xe7, 0xe7, 0xe7, 0xe7, 0xe7}},
  }};
  types::data_pipe_address base_address_{{0xe7, 0xe7, 0xe7, 0xe7, 0xe7}};

  auto LookupComPartnerAddress(types::PutDataTarget target_id) noexcept -> types::data_pipe_address;
  auto HandleTelemetryPacket(types::com_msg_frame &msg_frame) -> types::DriverStatus;
  auto HandleConfigPacket(types::com_msg_frame &msg_frame) -> types::DriverStatus;
};
}  // namespace com

#endif
