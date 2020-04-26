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
      explicit ComInterface(){};

      /** 
      * @brief Get the data packet object
      * 
      * @return decltype(array<uint8_t, 32>) 
      */
      virtual const auto get_data_packet() const noexcept -> decltype(array<uint8_t, 32>) = 0;
      
      /** 
      * @brief Transmit dataframe of max length 32 byte via the drones' wifi interface.
      * 
      * @param target_id target_id The wifi id of the receiver.
      * @param payload payload An array of bytes. Max length 32 bytes. Must conform to SquidDrone 
      * com protocol specification.
      * @return decltype(bool) true in case of successful transmission, false in case something 
      * went wrong.
      */
      virtual const auto put_data_packet(uint8_t target_id, array<uint8_t> &payload) const noexcept
      -> decltype(bool) = 0;
      
    protected:
      /** 
      * @brief 
      * 
      */
      ComMessageBuffer &msg_buffer;
}

}

#endif