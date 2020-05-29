#include "com_message_buffer.hpp"
#include "com_types.hpp"

namespace com {
  types::ComError ComMessageBuffer::put_data(std::array<std::uint8_t, 32> &data){
    if(data_.size() > max_queue_len){
      return types::ComError::COM_BUFFER_OVERFLOW;
    }
    data_.push(data);
    return check_data(data);
  }

  std::array<std::uint8_t, 32> ComMessageBuffer::get_data(){
    std::array<std::uint8_t, 32> queue_item;
    queue_item = data_.front();
    data_.pop();
    return queue_item;
  }

  types::ComError ComMessageBuffer::check_data(std::array<std::uint8_t, 32> &data){
    if(data_.front() == data){
      return types::ComError::COM_OK;
    }
    else {
      return types::ComError::COM_BUFFER_IO_ERROR;
    }
  }
}
