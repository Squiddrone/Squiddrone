#ifndef COM_COM_NRF24L01_TYPES_HPP_
#define COM_COM_NRF24L01_TYPES_HPP_

namespace com {

enum class State : std::uint8_t {
  disabled = 0,
  enabled
};

enum class CRCEncodingScheme : std::uint8_t {
  crc_8bit,
  crc_16bit
};

enum class DataPipe : std::uint8_t {
  rx_pipe_0 = 0,
  rx_pipe_1,
  rx_pipe_2,
  rx_pipe_3,
  rx_pipe_4,
  rx_pipe_5,
  tx_pipe
};

enum class DataPipeAddressWidth : std::uint8_t {
  aw_3bytes = 0x1,
  aw_4bytes = 0x2,
  aw_5bytes = 0x3,
};

enum class AutoRetransmissionDelay : std::uint8_t {
  // auto retransmis delay 250-4000 us
  ard250us = 0x0,
  ard500us = 0x1,
  ard750us = 0x2,
  ard1000us = 0x3,
  ard1250us = 0x4,
  ard1500us = 0x5,
  ard1750us = 0x6,
  ard2000us = 0x7,
  ard2250us = 0x8,
  ard2500us = 0x9,
  ard2750us = 0xa,
  ard3000us = 0xb,
  ard3250us = 0xc,
  ard3500us = 0xd,
  ard3750us = 0xe,
  ard4000us = 0xf
};

enum class AutoRetransmitCount : std::uint8_t {
  // auto retransmit count 0-15 in case of failed AR
  arc0 = 0x0,
  arc1 = 0x1,
  arc2 = 0x2,
  arc3 = 0x3,
  arc4 = 0x4,
  arc5 = 0x5,
  arc6 = 0x6,
  arc7 = 0x7,
  arc8 = 0x8,
  arc9 = 0x9,
  arc10 = 0xa,
  arc11 = 0xb,
  arc12 = 0xc,
  arc13 = 0xd,
  arc14 = 0xe,
  arc15 = 0xf
};

enum class OperationMode : std::uint8_t {
  undefined = 0,
  prim_rx,
  prim_tx
};

enum class RFPowerSetting : std::uint8_t {
  rf_pwr_18dBm = 0x0,
  rf_pwr_12dBm = 0x1,
  rf_pwr_6dBm = 0x2,
  rf_pwr_0dBm = 0x3
};

enum class DataRateSetting : std::uint8_t {
  rf_dr_1mbps = 0,
  rf_dr_2mbps = 1
};

enum class MaskeableInterrupts : std::uint8_t {
  max_nr_of_retries_reached = 4,
  tx_data_sent = 5,
  rx_data_ready = 6
};

using data_pipe_address = std::array<std::uint8_t, 5>;
using register_t = std::uint8_t;

}  // namespace com

#endif
