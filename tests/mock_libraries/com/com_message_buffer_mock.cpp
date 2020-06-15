#include "com_message_buffer_mock.hpp"

namespace com {
  auto ComMessageBuffer::PutData(types::com_msg_frame &data) const noexcept -> types::ComError{
    return types::ComError::COM_OK;
  }

  auto ComMessageBuffer::GetData() const noexcept -> types::com_msg_frame{
    return data_;
  }
}