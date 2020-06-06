#include "gtest/gtest.h"
#include "com_message_buffer.hpp"

namespace{
  class ComMessageBufferTests: public ::testing::Test{
    protected:
      virtual void SetUp(){
        ref_data.fill(0xfa);
      }
      types::com_msg_frame ref_data;
  };
}

TEST_F(ComMessageBufferTests, put_data){
  auto com_buffer = std::make_unique<com::ComMessageBuffer>();
  auto rv = com_buffer->PutData(ref_data);
  ASSERT_EQ(rv, types::ComError::COM_OK);
}

TEST_F(ComMessageBufferTests, put_data_buffer_overflow){
  auto com_buffer = std::make_unique<com::ComMessageBuffer>();
  for (int n = 0; n <= types::MAX_QUEUE_LENGTH; n++){
    com_buffer->PutData(ref_data);
  }
  auto rv = com_buffer->PutData(ref_data);
  ASSERT_EQ(rv, types::ComError::COM_BUFFER_OVERFLOW);
}

TEST_F(ComMessageBufferTests, get_data){
  auto com_buffer = std::make_unique<com::ComMessageBuffer>();
  com_buffer->PutData(ref_data);
  auto retrieved_data = com_buffer->GetData();
  ASSERT_EQ(ref_data,retrieved_data);
}

TEST_F(ComMessageBufferTests, get_data_with_empty_queue){
  auto com_buffer = std::make_unique<com::ComMessageBuffer>();
  types::com_msg_frame comp_data = {0};
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