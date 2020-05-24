#include "gtest/gtest.h"
#include "com_interface.hpp"
#include "com_message_buffer.hpp"

namespace{

  class ComInterfaceTests: public ::testing::Test{
  protected:
    virtual void SetUp(){
    }
  };
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}