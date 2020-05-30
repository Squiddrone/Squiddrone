#include "com_message_buffer_mock.hpp"

namespace com {
  auto ComMessageBuffer::PutData(std::array<std::uint8_t, 32> &data) const noexcept -> types::ComError{
    return types::ComError::COM_OK;
  }

  auto ComMessageBuffer::GetData() const noexcept -> std::array<std::uint8_t, 32>{
    return data_;
  }
}