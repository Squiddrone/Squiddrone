#include "com_message_buffer.hpp"
#include "com_types.hpp"

namespace com {
auto ComMessageBuffer::PutData(types::com_msg_frame &data) noexcept -> types::ComError {
  if (data_.size() > types::MAX_QUEUE_LENGTH) {
    return types::ComError::COM_BUFFER_OVERFLOW;
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
