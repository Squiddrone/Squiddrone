#ifndef SRC_COM_COM_NRF24L01_REG_HPP_
#define SRC_COM_COM_NRF24L01_REG_HPP_

#include <cstdint>

namespace com {
namespace reg {

/// configuration register
namespace config {
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
const std::uint8_t ENAA_P5 = 5;
const std::uint8_t ENAA_P4 = 4;
const std::uint8_t ENAA_P3 = 3;
const std::uint8_t ENAA_P2 = 2;
const std::uint8_t ENAA_P1 = 1;
const std::uint8_t ENAA_P0 = 0;
}  // namespace en_aa

/// enable RX data pipes
namespace en_rxaddr {
const std::uint8_t ERX_P5 = 5;
const std::uint8_t ERX_P4 = 4;
const std::uint8_t ERX_P3 = 3;
const std::uint8_t ERX_P2 = 2;
const std::uint8_t ERX_P1 = 1;
const std::uint8_t ERX_P0 = 1;
}  // namespace en_rxaddr

/// setup of address widths
namespace setup_aw {
const std::uint8_t AW_3BYTES = 0x1;
const std::uint8_t AW_4BYTES = 0x2;
const std::uint8_t AW_5BYTES = 0x3;
}  // namespace setup_aw

/// setup of automatic retransmission
namespace setup_retr {
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

}  // namespace reg
}  // namespace com

#endif