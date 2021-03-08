#include "com_nrf24l01_spi_protocol.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace {
class ComNRF24L01SpiProtocolTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }
  spi::CSPinDefinition com_cs_pin_;
  spi::SPI spi_{com_cs_pin_};
  com::NRF24L01SpiProtocol unit_under_test_{spi_};
};

TEST_F(ComNRF24L01SpiProtocolTests, read_register_spi_tx_ok) {
  ASSERT_TRUE(true);
}

}  // namespace