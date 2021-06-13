#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "com_interrupt_handler.hpp"

using ::testing::Mock;
using ::testing::NiceMock;
using ::testing::Return;

namespace {

class ComInterruptHandlerTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    com_ = std::make_shared<com::NRF24L01>();
  }

  std::shared_ptr<com::NRF24L01> com_;
};
}  // namespace

TEST_F(ComInterruptHandlerTests, is_constructible_with_com) {
  com::ComInterruptHandler::SetComDriver(com_);
  com::ComInterruptHandler::HandleComInterrupt();

  ASSERT_EQ(com_->handle_rx_irq_was_called, true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
