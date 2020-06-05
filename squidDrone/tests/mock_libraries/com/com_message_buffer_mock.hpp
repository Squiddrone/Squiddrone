#ifndef TESTS_MOCK_LIBRARIES_COM_COM_MESSAGE_BUFFER_HPP_
#define TESTS_MOCK_LIBRARIES_COM_COM_MESSAGE_BUFFER_HPP_

#include <queue>
#include <array>
#include "com_types.hpp"

namespace com 
{

  class ComMessageBuffer {
    public:
      ComMessageBuffer(): test_member(0), data_({0}){
        data_.fill(0xaa);
      };
      auto PutData(types::com_msg_frame &data) const noexcept -> types::ComError;
      auto GetData() const noexcept -> types::com_msg_frame;

      std::uint8_t test_member;

    protected:
      types::com_msg_frame data_;
  };
}

#endif
