#include "com_message_buffer.hpp"
#include "com_types.hpp"

namespace com {
auto ComMessageBuffer::PutData(types::com_msg_frame &data) noexcept -> types::ComError {
  if (data_.size() > types::COM_BUFFER_MAX_QUEUE_LENGTH) {
    return types::ComError::COM_BUFFER_OVERFLOW;
  }
  if (data.size() > types::COM_MAX_FRAME_LENGTH) {
    return types::ComError::COM_BUFFER_IO_ERROR;
  }

  data_.push(data);
  return types::ComError::COM_OK;
}

auto ComMessageBuffer::GetData() noexcept -> types::com_msg_frame {
  types::com_msg_frame queue_item = {0};
  if (!BufferIsEmpty()) {
    queue_item = data_.front();
    data_.pop();
  }
  return queue_item;
}

auto ComMessageBuffer::BufferIsEmpty() const noexcept -> bool {
  return data_.empty();
};
}  // namespace com
