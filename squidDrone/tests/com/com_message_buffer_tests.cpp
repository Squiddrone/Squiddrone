#include "gtest/gtest.h"
#include "com_message_buffer.hpp"

namespace{


  class ComMessageBufferTests: public ::testing::Test{
    protected:
      virtual void SetUp(){
      }
  };
}

TEST_F(ComMessageBufferTests, put_data_get_data){
  std::array<std::uint8_t, 32> data;
  data.fill(0xfa);
  auto com_buffer = std::make_unique<com::ComMessageBuffer>();
  com_buffer->put_data(data);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}