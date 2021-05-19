#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "com_interrupt_handler.hpp"

using ::testing::NiceMock;
using ::testing::Return;

namespace {

class ComInterruptHandlerTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    com_ = std::make_shared<com::NRF24L01>();
    unit_under_test_ = std::make_unique<com::ComInterruptHandler>(com_);
  }

  std::unique_ptr<com::ComInterruptHandler> unit_under_test_;
  std::shared_ptr<com::NRF24L01> com_;
};
}  // namespace

TEST_F(ComInterruptHandlerTests, is_constructible_with_com) {
  unit_under_test_->HandleComInterrupt();
  EXPECT_CALL(*com_, HandleRxIRQ()).Times(1);

  //ASSERT_EQ(0xfa, unit_under_test->msg_buffer_->test_member);
}