#include "com_message_buffer_mock.hpp"

namespace com {
  uint8_t ComMessageBuffer::put_data(std::array<std::uint8_t, 32> &data){
    return 0;
  }

  std::array<std::uint8_t, 32> ComMessageBuffer::get_data(){
    return _data;
  }
}