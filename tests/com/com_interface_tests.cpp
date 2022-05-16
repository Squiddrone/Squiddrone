#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "com_interface.hpp"
#include "com_types.hpp"

using ::testing::NiceMock;
using ::testing::Return;

namespace {
class ConcreteComInterface final : public com::ComInterface {
 private:
 public:
  using com::ComInterface::msg_buffer_;
  explicit ConcreteComInterface(std::unique_ptr<com::ComMessageBuffer> com_buf) : com::ComInterface(std::move(com_buf)) {}

  auto GetDataPacket() const noexcept -> types::ComDataPacket override {
    types::ComDataPacket mock_packet;
    return mock_packet;
  }

  auto PutDataPacket(types::ComPartnerId partner_id, types::ComDataPacket &packet) noexcept -> types::DriverStatus override {
    return types::DriverStatus::OK;
  }
};

class ComInterfaceTests : public ::testing::Test {
 protected:
  std::unique_ptr<com::ComMessageBuffer> com_buffer_ = std::make_unique<NiceMock<com::ComMessageBuffer>>();

  virtual void SetUp() {
    com_buffer_->test_member = 0xfa;
  }
};
}  // namespace

TEST_F(ComInterfaceTests, is_constructible_with_com_buffer) {
  auto unit_under_test = std::make_unique<ConcreteComInterface>(std::move(com_buffer_));
  ASSERT_EQ(0xfa, unit_under_test->msg_buffer_->test_member);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
