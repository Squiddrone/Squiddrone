#include "gtest/gtest.h"
#include "com_message_buffer.hpp"

namespace{
  // Derived class for testing queue behaviour
  class ComMessageBufferTest: public com::ComMessageBuffer {
    public:
      using com::ComMessageBuffer::max_queue_len;
      using com::ComMessageBuffer::data_;
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

TEST_F(ComMessageBufferTests, put_data){
  auto com_buffer = std::make_unique<com::ComMessageBuffer>();
  auto rv = com_buffer->PutData(ref_data);
  ASSERT_EQ(rv, types::ComError::COM_OK);
}

TEST_F(ComMessageBufferTests, put_data_buffer_overflow){
  auto com_buffer = std::make_unique<ComMessageBufferTest>();
  for (int n = 0; n <= com_buffer->max_queue_len; n++){
    com_buffer->data_.push(ref_data);
  }
  auto rv = com_buffer->PutData(ref_data);
  ASSERT_EQ(rv, types::ComError::COM_BUFFER_OVERFLOW);
}

TEST_F(ComMessageBufferTests, get_data){
  auto com_buffer = std::make_unique<ComMessageBufferTest>();
  com_buffer->data_.push(ref_data);
  auto retrieved_data = com_buffer->GetData();
  ASSERT_EQ(ref_data,retrieved_data);
}

TEST_F(ComMessageBufferTests, get_data_with_empty_queue){
  auto com_buffer = std::make_unique<com::ComMessageBuffer>();
  std::array<uint8_t, 32> comp_data = {0};
  auto retrieved_data = com_buffer->GetData();
  ASSERT_EQ(comp_data,retrieved_data);
}

TEST_F(ComMessageBufferTests, buffer_is_empty){
  auto com_buffer = std::make_unique<com::ComMessageBuffer>();
  com_buffer->PutData(ref_data);
  com_buffer->GetData();
  auto rv = com_buffer->BufferIsEmpty();
  ASSERT_EQ(rv, true);
}

TEST_F(ComMessageBufferTests, buffer_is_not_empty){
  auto com_buffer = std::make_unique<com::ComMessageBuffer>();
  com_buffer->PutData(ref_data);
  auto rv = com_buffer->BufferIsEmpty();
  ASSERT_EQ(rv, false);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}