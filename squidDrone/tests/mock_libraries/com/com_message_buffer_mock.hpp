#ifndef TESTS_MOCK_LIBRARIES_COM_COM_MESSAGE_BUFFER_HPP_
#define TESTS_MOCK_LIBRARIES_COM_COM_MESSAGE_BUFFER_HPP_

#include <queue>
#include <array>

namespace com 
{

  class ComMessageBuffer {
    public:
      ComMessageBuffer(): test_member(0), data_({0}){
        data_.fill(0xaa);
      };
      std::uint8_t put_data(std::array<std::uint8_t, 32> &data);
      std::array<std::uint8_t, 32> get_data();

      std::uint8_t test_member;

    protected:
      std::array<std::uint8_t,32> data_;
  };
}

#endif
