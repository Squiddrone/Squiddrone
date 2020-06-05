#include "gtest/gtest.h"
#include "com_interface.hpp"

namespace{
  class ConcreteComInterface final: public com::ComInterface {
    private:
      types::com_msg_frame ret_array_ = {0};

    public:
      using com::ComInterface::msg_buffer_;
      explicit ConcreteComInterface(std::unique_ptr<com::ComMessageBuffer> com_buf) : com::ComInterface(std::move(com_buf)){}

      auto GetDataPacket() const noexcept -> types::com_msg_frame{
        return msg_buffer_->GetData();
      }

      auto PutDataPacket(std::uint8_t target_id, types::com_msg_frame &payload) const noexcept-> types::ComError{
        return types::ComError::COM_OK;
      }
  };

  class ComInterfaceTests: public ::testing::Test{
    protected:
      virtual void SetUp(){
      }
  };
}

TEST_F(ComInterfaceTests, is_constructible_with_com_buffer){
  auto com_buffer = std::make_unique<com::ComMessageBuffer>();
  com_buffer->test_member = 0xfa;
  auto unit_under_test = std::make_unique<ConcreteComInterface>(std::move(com_buffer));
  ASSERT_EQ(0xfa, unit_under_test->msg_buffer_->test_member);
}

TEST_F(ComInterfaceTests, get_data_packet){
  types::com_msg_frame data_compare;
  data_compare.fill(0xaa);
  auto com_buffer = std::make_unique<com::ComMessageBuffer>();
  auto unit_under_test = std::make_unique<ConcreteComInterface>(std::move(com_buffer));
  ASSERT_EQ(data_compare, unit_under_test->GetDataPacket());
}

TEST_F(ComInterfaceTests, put_data_packet){
  types::com_msg_frame data;
  auto com_buffer = std::make_unique<com::ComMessageBuffer>();
  auto unit_under_test = std::make_unique<ConcreteComInterface>(std::move(com_buffer));
  ASSERT_EQ(types::ComError::COM_OK, unit_under_test->PutDataPacket(1, data));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
