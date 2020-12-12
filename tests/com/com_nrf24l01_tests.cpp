#include "com_nrf24l01.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace {
class ComNRF24L01Tests : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }

  std::unique_ptr<com::ComMessageBuffer> com_msg_buffer_;
  spi::CSPinDefinition com_cs_pin;
};

TEST_F(ComNRF24L01Tests, some_test) {
  auto nrf24l01 = std::make_unique<com::NRF24L01>(std::move(com_msg_buffer_), com_cs_pin);
  ASSERT_TRUE(true);
}

}  // namespace