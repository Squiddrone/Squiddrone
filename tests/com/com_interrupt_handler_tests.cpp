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
  }

  std::shared_ptr<com::NRF24L01> com_;
};
}  // namespace

TEST_F(ComInterruptHandlerTests, is_constructible_with_com) {
}