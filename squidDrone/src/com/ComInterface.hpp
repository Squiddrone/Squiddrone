#ifndef SRC_COM_COMINTERFACE_HPP_
#define SRC_COM_COMINTERFACE_HPP_

/** 
* @file ComInterface.hpp
* @author your name (you@domain.com)
* @brief 
* @version 0.1
* @date 2020-04-25
* 
* @copyright Copyright (c) 2020
* 
*/

#include "ComMessageBuffer.hpp"
#include <array>

namespace com {

  class ComInterface {
    public:
      /** 
      * @brief Default constructor may not be used.
      * 
      */
      ComInterface() = delete;

      /** 
      * @brief Construct a new Com Interface object
      * 
      */
      explicit ComInterface(ComMessageBuffer &msg_buf) : msg_buffer(msg_buf){};

      /** 
      * @brief Get the data packet object
      * 
      * @return decltype(array<std::uint8_t, 32>) 
      */
      virtual const auto get_data_packet() const noexcept -> std::array<std::uint8_t, 32> = 0;
      
      /** 
      * @brief Transmit dataframe of max length 32 byte via the drones' wifi interface.
      * 
      * @param target_id target_id The wifi id of the receiver.
      * @param payload payload An array of bytes. Max length 32 bytes. Must conform to SquidDrone 
      * com protocol specification.
      * @return decltype(std::uint8_t) true in case of successful transmission, false in case something 
      * went wrong.
      */
      virtual const auto put_data_packet(std::uint8_t target_id, std::array<std::uint8_t, 32> &payload) const noexcept
      -> std::uint8_t = 0;
      
    protected:
      /** 
      * @brief Reference to an instance of a message buffer queue.
      * 
      */
      ComMessageBuffer &msg_buffer;
  };
}

#endif