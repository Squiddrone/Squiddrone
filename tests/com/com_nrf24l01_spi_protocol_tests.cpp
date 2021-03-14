#include "com_nrf24l01_spi_protocol.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace {
class ComNRF24L01SpiProtocolTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }
};

TEST_F(ComNRF24L01SpiProtocolTests, sometest) {
  auto unit_under_test_ = std::make_unique<com::NRF24L01SpiProtocol>;
  ASSERT_TRUE(true);
}

}  // namespace