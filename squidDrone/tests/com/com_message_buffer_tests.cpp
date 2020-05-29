#include "gtest/gtest.h"
#include "com_message_buffer.hpp"

namespace{
  // Derived class for testing queue behaviour
  class ComMessageBufferTest: public com::ComMessageBuffer {
    public:
      using com::ComMessageBuffer::data_;
      using com::ComMessageBuffer::check_data;
      ComMessageBufferTest(){};
  };

  class ComMessageBufferTests: public ::testing::Test{
    protected:
      virtual void SetUp(){
        ref_data.fill(0xfa);
      }
      std::array<std::uint8_t, 32> ref_data;
  };
}

TEST_F(ComMessageBufferTests, check_data){
  auto com_buffer = std::make_unique<ComMessageBufferTest>();
  std::array<std::uint8_t, 32> false_data;
  false_data.fill(0xaa);
  com_buffer->put_data(false_data);
  auto rv = com_buffer->check_data(ref_data);
  ASSERT_EQ(rv, types::ComError::COM_BUFFER_IO_ERROR);
}

TEST_F(ComMessageBufferTests, put_data){
  auto com_buffer = std::make_unique<ComMessageBufferTest>();
  com_buffer->put_data(ref_data);
  ASSERT_EQ(com_buffer->data_.front(),ref_data);
}

TEST_F(ComMessageBufferTests, get_data){
  auto com_buffer = std::make_unique<ComMessageBufferTest>();
  com_buffer->data_.push(ref_data);
  auto retrieved_data = com_buffer->get_data();
  ASSERT_EQ(ref_data,retrieved_data);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}