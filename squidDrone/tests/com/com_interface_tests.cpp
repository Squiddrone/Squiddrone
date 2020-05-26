#include "gtest/gtest.h"
#include "com_interface.hpp"

namespace{
  class ConcreteComInterface final: public com::ComInterface {
    private:
      std::array<std::uint8_t, 32> ret_array = {0};

    public:
      using com::ComInterface::msg_buffer;
      explicit ConcreteComInterface(std::unique_ptr<com::ComMessageBuffer> com_buf) : com::ComInterface(std::move(com_buf)){}

      auto get_data_packet() const noexcept -> std::array<std::uint8_t, 32>{
        return msg_buffer->get_data();
      }

      auto put_data_packet(std::uint8_t target_id, std::array<std::uint8_t, 32> &payload) const noexcept-> std::uint8_t{
        return 1;
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
  ASSERT_EQ(0xfa, unit_under_test->msg_buffer->test_member);
}

TEST_F(ComInterfaceTests, get_data_packet){
  std::array<std::uint8_t, 32> data_compare;
  data_compare.fill(0xaa);
  auto com_buffer = std::make_unique<com::ComMessageBuffer>();
  auto unit_under_test = std::make_unique<ConcreteComInterface>(std::move(com_buffer));
  ASSERT_EQ(data_compare, unit_under_test->get_data_packet());
}

TEST_F(ComInterfaceTests, put_data_packet){
  std::array<std::uint8_t, 32> data;
  auto com_buffer = std::make_unique<com::ComMessageBuffer>();
  auto unit_under_test = std::make_unique<ConcreteComInterface>(std::move(com_buffer));
  ASSERT_EQ(1, unit_under_test->put_data_packet(1, data));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
