#include "com_message_buffer.hpp"
#include "com_types.hpp"

namespace com {
  auto ComMessageBuffer::PutData(std::array<std::uint8_t, 32> &data) noexcept -> types::ComError{
    if(data_.size() > max_queue_len){
      return types::ComError::COM_BUFFER_OVERFLOW;
    }
    data_.push(data);
    return types::ComError::COM_OK;
  }

  auto ComMessageBuffer::GetData() noexcept -> std::array<std::uint8_t, 32>{
    std::array<std::uint8_t, 32> queue_item = {0};
    if(!data_.empty()){
      queue_item = data_.front();
      data_.pop();
    }
    return queue_item;
  }

  auto ComMessageBuffer::BufferIsEmpty() const noexcept -> bool{
    return data_.empty();
  };
}
