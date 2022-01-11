#ifndef TESTS_COM_COM_NRF24L01_CORE_MOCK_HPP_
#define TESTS_COM_COM_NRF24L01_CORE_MOCK_HPP_

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "com_nrf24l01_reg.hpp"
#include "com_nrf24l01_types.hpp"
#include "error_types.hpp"

namespace com {

class NRF24L01Core {
 public:
  MOCK_METHOD((types::DriverStatus), EnableDataPipe, (DataPipe), (noexcept));
  MOCK_METHOD((types::DriverStatus), DisableDataPipe, (DataPipe), (noexcept));
  MOCK_METHOD((types::DriverStatus), SetTxAddress, (data_pipe_address), (const noexcept));
  MOCK_METHOD((types::DriverStatus), SetRxAddress, (DataPipe, data_pipe_address), (const noexcept));
  MOCK_METHOD((data_pipe_address), GetPipeAddress, (DataPipe), (noexcept));
  MOCK_METHOD((types::DriverStatus), SetPipeAddress, (DataPipe, data_pipe_address), (noexcept));
  MOCK_METHOD((types::DriverStatus), SetRxPayloadSize, (DataPipe, std::size_t), (const noexcept));
  MOCK_METHOD((types::DriverStatus), EnableAutoAck, (DataPipe), (noexcept));
  MOCK_METHOD((types::DriverStatus), InitTx, (com::data_pipe_address tx_target_address), (noexcept));
  MOCK_METHOD((types::DriverStatus), InitRx, (data_pipe_address), (noexcept));
  MOCK_METHOD((types::DriverStatus), InitTransceiver, (std::uint8_t, DataRateSetting, RFPowerSetting, CRCEncodingScheme, data_pipe_address), (noexcept));
  MOCK_METHOD((types::DriverStatus), SetOperationMode, (OperationMode), (noexcept));
  MOCK_METHOD((types::DriverStatus), SetPowerState, (State), (noexcept));
  MOCK_METHOD((types::DriverStatus), SetRFChannel, (std::uint8_t), (noexcept));
  MOCK_METHOD((types::DriverStatus), SetDataRate, (DataRateSetting), (noexcept));
  MOCK_METHOD((types::DriverStatus), SetRFOutputPower, (RFPowerSetting), (noexcept));
  MOCK_METHOD((types::DriverStatus), MaskInterruptOnPin, (MaskeableInterrupts), (noexcept));
  MOCK_METHOD((types::DriverStatus), SetAddressWidth, (DataPipeAddressWidth), (noexcept));
  MOCK_METHOD((types::DriverStatus), EnableCRC, (), (noexcept));
  MOCK_METHOD((types::DriverStatus), SetCRCEncodingScheme, (CRCEncodingScheme), (noexcept));
  MOCK_METHOD((types::DriverStatus), ConfigAutoRetransmission, (AutoRetransmissionDelay, AutoRetransmitCount), (noexcept));
  MOCK_METHOD((std::pair<types::DriverStatus, std::uint8_t>), GetIRQFlags, (), (noexcept));
  MOCK_METHOD((types::DriverStatus), SetTxPayload, (std::vector<std::uint8_t> &), (noexcept));
  MOCK_METHOD((types::DriverStatus), GetRxPayload, (std::vector<std::uint8_t> &), (noexcept));
  MOCK_METHOD((types::DriverStatus), SetChipEnable, (State), (noexcept));

  NRF24L01Core() = default;
  virtual ~NRF24L01Core() = default;
};
}  // namespace com

#endif