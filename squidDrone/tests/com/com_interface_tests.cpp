#include "gtest/gtest.h"
#include "com_interface.hpp"
#include "com_message_buffer.hpp"

namespace{

  class ComInterfaceTests: public ::testing::Test{
  protected:
    virtual void SetUp(){
      auto msg_buffer_ = std::make_unique<com::ComMessageBuffer>();
      unit_under_test_ = std::make_unique<com::ComInterface>(std::move(msg_buffer_));
    }

    std::unique_ptr<com::ComMessageBuffer> msg_buffer_;
    std::unique_ptr<com::ComInterface> unit_under_test_;
  };
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}