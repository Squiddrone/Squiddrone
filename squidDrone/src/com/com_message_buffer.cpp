#include "com_message_buffer.hpp"
#include "com_types.hpp"

namespace com {
  auto ComMessageBuffer::PutData(std::array<std::uint8_t, 32> &data) noexcept -> types::ComError{
    if(data_.size() > max_queue_len){
      return types::ComError::COM_BUFFER_OVERFLOW;
    }
    data_.push(data);
    return CheckData(data);
  }

  auto ComMessageBuffer::GetData() noexcept -> std::array<std::uint8_t, 32>{
    std::array<std::uint8_t, 32> queue_item;
    queue_item = data_.front();
    data_.pop();
    return queue_item;
  }

auto ComMessageBuffer::CheckData(std::array<std::uint8_t, 32> &data) const noexcept -> types::ComError{
    if(data_.front() == data){
      return types::ComError::COM_OK;
    }
    else {
      return types::ComError::COM_BUFFER_IO_ERROR;
    }
  }
}
