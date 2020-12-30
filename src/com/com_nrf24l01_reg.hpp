#ifndef SRC_COM_COM_NRF24L01_REG_HPP_
#define SRC_COM_COM_NRF24L01_REG_HPP_

#include <array>
#include <cstdint>

namespace com {

enum class State : std::uint8_t {
  disabled = 0,
  enabled
};

enum class CRCEncodingScheme : std::uint8_t {
  one_byte,
  two_bytes
};

enum class DataPipe : std::uint8_t {
  data_pipe_0 = 0,
  data_pipe_1,
  data_pipe_2,
  data_pipe_3,
  data_pipe_4,
  data_pipe_5
};

enum class DataPipeAddressWidth : std::uint8_t {
  aw_3bytes = 0x1,
  aw_4bytes = 0x2,
  aw_5bytes = 0x3,
};

enum class AutoRetransmissionDelay : std::uint8_t {
  // auto retransmis delay 250-4000 us
  ard250us = 0x00,
  ard500us = 0x10,
  ard750us = 0x20,
  ard1000us = 0x30,
  ard1250us = 0x40,
  ard1500us = 0x50,
  ard1750us = 0x60,
  ard2000us = 0x70,
  ard2250us = 0x80,
  ard2500us = 0x90,
  ard2750us = 0xa0,
  ard3000us = 0xb0,
  ard3250us = 0xc0,
  ard3500us = 0xd0,
  ard3750us = 0xe0,
  ard4000us = 0xf0
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

enum class RFPowerSetting : std::uint8_t {
  rf_pwr_18dBm = 0x0,
  rf_pwr_12dBm = 0x1,
  rf_pwr_6dBm = 0x2,
  rf_pwr_0dBm = 0x3
};

enum class DataRateSetting : std::uint8_t {
  rf_dr_1mbps = 0,
  rf_dr_2mbps = 2
};

using data_pipe_address = std::array<std::uint8_t, 5>;

namespace instruction_word {
const std::uint8_t R_REGISTER = 0x00;
const std::uint8_t W_REGISTER = 0x20;
const std::uint8_t R_RX_PAYLOAD = 0x61;
const std::uint8_t W_TX_PAYLOAD = 0xa0;
const std::uint8_t FLUSH_TX = 0xe1;
const std::uint8_t FLUSH_RX = 0xe2;
const std::uint8_t REUSE_TX_PL = 0xe3;
const std::uint8_t NOP = 0xff;
}  // namespace instruction_word

namespace reg {
/// configuration register
namespace config {
const std::uint8_t REG_ADDR = 0x0;
const std::uint8_t MASK_RX_DR = 6;
const std::uint8_t MASK_TX_DS = 5;
const std::uint8_t MASK_MAX_RT = 4;
const std::uint8_t EN_CRC = 3;
const std::uint8_t CRCO = 2;
const std::uint8_t PWR_UP = 1;
const std::uint8_t PRIM_RX = 0;
}  // namespace config

/// enable enhanced shock burst auto acknowledgement
namespace en_aa {
const std::uint8_t REG_ADDR = 0x1;
const std::uint8_t ENAA_P5 = 5;
const std::uint8_t ENAA_P4 = 4;
const std::uint8_t ENAA_P3 = 3;
const std::uint8_t ENAA_P2 = 2;
const std::uint8_t ENAA_P1 = 1;
const std::uint8_t ENAA_P0 = 0;
}  // namespace en_aa

/// enable RX data pipes
namespace en_rxaddr {
const std::uint8_t REG_ADDR = 0x2;
const std::uint8_t ERX_P5 = 5;
const std::uint8_t ERX_P4 = 4;
const std::uint8_t ERX_P3 = 3;
const std::uint8_t ERX_P2 = 2;
const std::uint8_t ERX_P1 = 1;
const std::uint8_t ERX_P0 = 1;
}  // namespace en_rxaddr

/// setup of address widths
namespace setup_aw {
const std::uint8_t REG_ADDR = 0x3;
}  // namespace setup_aw

/// setup of automatic retransmission
namespace setup_retr {
const std::uint8_t REG_ADDR = 0x4;
}  // namespace setup_retr

/// RF channel setting
namespace rf_ch {
const std::uint8_t REG_ADDR = 0x5;
}  // namespace rf_ch

/// RF setup register
namespace rf_setup {
const std::uint8_t REG_ADDR = 0x6;
const std::uint8_t PLL_LOCK = 4;
const std::uint8_t RF_DR = 3;
const std::uint8_t RF_PWR = 1;
const std::uint8_t LNA_HCURR = 0;
}  // namespace rf_setup

/// Status Register
namespace status {
const std::uint8_t REG_ADDR = 0x7;
const std::uint8_t RX_DR = 6;
const std::uint8_t TX_DS = 5;
const std::uint8_t MAX_RT = 4;
const std::uint8_t RX_P_NO = 1;
const std::uint8_t RX_P_NO_0 = 0b0;
const std::uint8_t RX_P_NO_1 = 0b1;
const std::uint8_t RX_P_NO_2 = 0b10;
const std::uint8_t RX_P_NO_3 = 0b11;
const std::uint8_t RX_P_NO_4 = 0b100;
const std::uint8_t RX_P_NO_5 = 0b101;
const std::uint8_t RX_FIFO_EMPTY = 0b111;
const std::uint8_t TX_FULL = 0;
}  // namespace status

/// Transmit observe register
namespace observe_tx {
const std::uint8_t REG_ADDR = 0x8;
const std::uint8_t PLOS_CNT = 4;
const std::uint8_t ARC_CNT = 0;
}  // namespace observe_tx

/// Carrier detect
namespace cd {
const std::uint8_t REG_ADDR = 0x9;
const std::uint8_t CD = 0;
}  // namespace cd

/// Receive address data pipe 0. 5 Bytes maximum length.
namespace rx_addr_p0 {
const std::uint8_t REG_ADDR = 0x0a;
}  // namespace rx_addr_p0

/// Receive address data pipe 1. 5 Bytes maximum length.
namespace rx_addr_p1 {
const std::uint8_t REG_ADDR = 0x0b;
}  // namespace rx_addr_p1

/// Receive address data pipe 2. Only LSB.
namespace rx_addr_p2 {
const std::uint8_t REG_ADDR = 0x0c;
}  // namespace rx_addr_p2

/// Receive address data pipe 3. Only LSB.
namespace rx_addr_p3 {
const std::uint8_t REG_ADDR = 0x0d;
}  // namespace rx_addr_p3

/// Receive address data pipe 4. Only LSB.
namespace rx_addr_p4 {
const std::uint8_t REG_ADDR = 0x0e;
}  // namespace rx_addr_p4

/// Receive address data pipe 5. Only LSB.
namespace rx_addr_p5 {
const std::uint8_t REG_ADDR = 0x0f;
}  // namespace rx_addr_p5

/// Transmit address. Used for a PTX device only.
namespace tx_addr {
const std::uint8_t REG_ADDR = 0x10;
}  // namespace tx_addr

/// Number of bytes in RX payload in data pipe 0.
namespace rx_pw_p0 {
const std::uint8_t REG_ADDR = 0x11;
}  // namespace rx_pw_p0

/// Number of bytes in RX payload in data pipe 1.
namespace rx_pw_p1 {
const std::uint8_t REG_ADDR = 0x12;
}  // namespace rx_pw_p1

/// Number of bytes in RX payload in data pipe 2.
namespace rx_pw_p2 {
const std::uint8_t REG_ADDR = 0x13;
}  // namespace rx_pw_p2

/// Number of bytes in RX payload in data pipe 3.
namespace rx_pw_p3 {
const std::uint8_t REG_ADDR = 0x14;
}  // namespace rx_pw_p3

/// Number of bytes in RX payload in data pipe 4.
namespace rx_pw_p4 {
const std::uint8_t REG_ADDR = 0x15;
}  // namespace rx_pw_p4

/// Number of bytes in RX payload in data pipe 5.
namespace rx_pw_p5 {
const std::uint8_t REG_ADDR = 0x16;
}  // namespace rx_pw_p5

/// FIFO status register
namespace fifo_status {
const std::uint8_t REG_ADDR = 0x17;
const std::uint8_t TX_REUSE = 6;
const std::uint8_t TX_FULL = 5;
const std::uint8_t TX_EMPTY = 4;
const std::uint8_t RX_FULL = 1;
const std::uint8_t RX_EMPTY = 0;
}  // namespace fifo_status

}  // namespace reg
}  // namespace com

#endif
