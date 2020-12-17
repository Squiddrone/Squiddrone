#ifndef SRC_COM_COM_NRF24L01_REG_HPP_
#define SRC_COM_COM_NRF24L01_REG_HPP_

#include <cstdint>

namespace com {

enum class CRCEncodingScheme : std::uint8_t {
  one_byte,
  two_bytes
};

enum class DataPipe : std::uint8_t {
  data_pipe_0,
  data_pipe_1,
  data_pipe_2,
  data_pipe_3,
  data_pipe_4,
  data_pipe_5
};

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
const std::uint8_t AW_3BYTES = 0x1;
const std::uint8_t AW_4BYTES = 0x2;
const std::uint8_t AW_5BYTES = 0x3;
}  // namespace setup_aw

/// setup of automatic retransmission
namespace setup_retr {
const std::uint8_t REG_ADDR = 0x4;
// auto retransmis delay 250-4000 us
const std::uint8_t ARD250 = 0x00;
const std::uint8_t ARD500 = 0x10;
const std::uint8_t ARD750 = 0x20;
const std::uint8_t ARD1000 = 0x30;
const std::uint8_t ARD1250 = 0x40;
const std::uint8_t ARD1500 = 0x50;
const std::uint8_t ARD1750 = 0x60;
const std::uint8_t ARD2000 = 0x70;
const std::uint8_t ARD2250 = 0x80;
const std::uint8_t ARD2500 = 0x90;
const std::uint8_t ARD2750 = 0xa0;
const std::uint8_t ARD3000 = 0xb0;
const std::uint8_t ARD3250 = 0xc0;
const std::uint8_t ARD3500 = 0xd0;
const std::uint8_t ARD3750 = 0xe0;
const std::uint8_t ARD4000 = 0xf0;

// auto retransmit count 0-15 in case of failed AR
const std::uint8_t ARC0 = 0x0;
const std::uint8_t ARC1 = 0x1;
const std::uint8_t ARC2 = 0x2;
const std::uint8_t ARC3 = 0x3;
const std::uint8_t ARC4 = 0x4;
const std::uint8_t ARC5 = 0x5;
const std::uint8_t ARC6 = 0x6;
const std::uint8_t ARC7 = 0x7;
const std::uint8_t ARC8 = 0x8;
const std::uint8_t ARC9 = 0x9;
const std::uint8_t ARC10 = 0xa;
const std::uint8_t ARC11 = 0xb;
const std::uint8_t ARC12 = 0xc;
const std::uint8_t ARC13 = 0xd;
const std::uint8_t ARC14 = 0xe;
const std::uint8_t ARC15 = 0xf;
}  // namespace setup_retr

namespace rf_ch {
const std::uint8_t REG_ADDR = 0x5;
}  // namespace rf_ch

namespace rf_setup {
const std::uint8_t REG_ADDR = 0x6;
const std::uint8_t PLL_LOCK = 4;
const std::uint8_t RF_DR = 3;
const std::uint8_t RF_PWR = 1;
const std::uint8_t RF_PWR_18dBm = 0x0;
const std::uint8_t RF_PWR_12dBm = 0x1;
const std::uint8_t RF_PWR_6dBm = 0x2;
const std::uint8_t RF_PWR_0dBm = 0x3;
const std::uint8_t LNA_HCURR = 0;
}  // namespace rf_setup

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

namespace observe_tx {
const std::uint8_t REG_ADDR = 0x8;
const std::uint8_t PLOS_CNT = 4;
const std::uint8_t ARC_CNT = 0;
}  // namespace observe_tx

namespace cd {
const std::uint8_t REG_ADDR = 0x9;
const std::uint8_t CD = 0;
}  // namespace cd

namespace rx_addr_p0 {
const std::uint8_t REG_ADDR = 0x0a;
}  // namespace rx_addr_p0

namespace rx_addr_p1 {
const std::uint8_t REG_ADDR = 0x0b;
}  // namespace rx_addr_p1

namespace rx_addr_p2 {
const std::uint8_t REG_ADDR = 0x0c;
}  // namespace rx_addr_p2

namespace rx_addr_p3 {
const std::uint8_t REG_ADDR = 0x0d;
}  // namespace rx_addr_p3

namespace rx_addr_p4 {
const std::uint8_t REG_ADDR = 0x0e;
}  // namespace rx_addr_p4

namespace rx_addr_p5 {
const std::uint8_t REG_ADDR = 0x0f;
}  // namespace rx_addr_p5

namespace tx_addr {
const std::uint8_t REG_ADDR = 0x10;
}  // namespace tx_addr

namespace rx_pw_p0 {
const std::uint8_t REG_ADDR = 0x11;
}  // namespace rx_pw_p0

namespace rx_pw_p1 {
const std::uint8_t REG_ADDR = 0x12;
}  // namespace rx_pw_p1

namespace rx_pw_p2 {
const std::uint8_t REG_ADDR = 0x13;
}  // namespace rx_pw_p2

namespace rx_pw_p3 {
const std::uint8_t REG_ADDR = 0x14;
}  // namespace rx_pw_p3

namespace rx_pw_p4 {
const std::uint8_t REG_ADDR = 0x15;
}  // namespace rx_pw_p4

namespace rx_pw_p5 {
const std::uint8_t REG_ADDR = 0x16;
}  // namespace rx_pw_p5

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