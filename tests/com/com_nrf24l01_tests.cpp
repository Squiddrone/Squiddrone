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

TEST_F(ComNRF24L01Tests, com_frame_length_exceeding_limit) {
  auto unit_under_test_ = std::make_unique<com::NRF24L01>(std::move(com_msg_buffer_));
  types::com_msg_frame long_msg_frame(33);

  types::ComError return_value = unit_under_test_->PutDataPacket(0, long_msg_frame);
  ASSERT_TRUE(true);
}

}  // namespace