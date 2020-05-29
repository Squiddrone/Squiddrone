#include "com_message_buffer.hpp"

namespace com {
  std::int8_t ComMessageBuffer::put_data(std::array<std::uint8_t, 32> &data){
    if(_data.size > max_queue_len){
      return -1;
    }
    _data.push(data);
    return 0;
  }

  std::array<std::uint8_t, 32> ComMessageBuffer::get_data(){
    
  }
}