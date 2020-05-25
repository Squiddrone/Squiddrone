#include "gtest/gtest.h"
#include "com_interface.hpp"
#include "com_message_buffer.hpp"

namespace{
  class ComInterfaceDerived: public com::ComInterface {
    private:
      std::array<std::uint8_t, 32> ret_array = {0};
    public:
      explicit ComInterfaceDerived(std::unique_ptr<com::ComMessageBuffer> com_buf) : com::ComInterface(std::move(com_buf)){};
      auto get_data_packet() const noexcept -> std::array<std::uint8_t, 32>{return ret_array;};
      auto put_data_packet(std::uint8_t target_id, std::array<std::uint8_t, 32> &payload) const noexcept
        -> std::uint8_t{return 0;};
  };

  class ComInterfaceTests: public ::testing::Test{
    protected:
      virtual void SetUp(){
      }
  };
}

TEST_F(ComInterfaceTests, signture_stability){
    auto com_buffer_ = std::make_unique<com::ComMessageBuffer>();
    std::make_unique<ComInterfaceDerived>(std::move(com_buffer_));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}