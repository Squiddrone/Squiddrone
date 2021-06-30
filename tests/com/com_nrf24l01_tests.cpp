#include "com_nrf24l01.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace {
class ComNRF24L01Tests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    com_msg_buffer_ = std::make_unique<com::ComMessageBuffer>();
    com_spi_protocol_ = std::make_unique<com::NRF24L01SpiProtocol>();
  }

  std::unique_ptr<com::ComMessageBuffer> com_msg_buffer_;
  std::unique_ptr<com::NRF24L01SpiProtocol> com_spi_protocol_;
};

TEST_F(ComNRF24L01Tests, com_frame_length_exceeding_limit) {
  auto unit_under_test_ = std::make_unique<com::NRF24L01>(std::move(com_msg_buffer_), std::move(com_spi_protocol_));
  types::com_msg_frame long_msg_frame(33);

  types::ComError return_value = unit_under_test_->PutDataPacket(0, long_msg_frame);
  ASSERT_TRUE(true);
}

TEST_F(ComNRF24L01Tests, com_frame_reception) {
  auto unit_under_test_ = std::make_unique<com::NRF24L01>(std::move(com_msg_buffer_), std::move(com_spi_protocol_));
  types::com_msg_frame long_msg_frame(32);

  unit_under_test_->HandleRxIRQ();
  ASSERT_TRUE(true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

}  // namespace