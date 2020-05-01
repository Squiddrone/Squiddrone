#ifndef SRC_COM_MESSAGE_BUFFER_HPP_
#define SRC_COM_MESSAGE_BUFFER_HPP_

/** 
* @file ComMessageBuffer.hpp
* @author your name (you@domain.com)
* @brief 
* @version 0.1
* @date 2020-04-27
* 
* @copyright Copyright (c) 2020
* 
*/

#include <array>
#include <queue>

namespace com {
  /** 
  * @class ComMessageBuffer
  * @brief This class represents a queue style buffer for communication
  * frames exchanged between drones.
  * 
  */
  class ComMessageBuffer {
    public:
      /** 
      * @brief Construct a new Com Message Buffer object
      */
      ComMessageBuffer(){};

      /** 
      * @brief Transfer data to queue buffer
      * 
      * @param data Reference to data frame. Must conform to data frame specifications.
      * @return uint8_t Number of bytes put into the data queue.
      */
      uint8_t put_data(std::array<std::uint8_t, 32> &data);

      /** 
      * @brief Retrieve data frame from queue buffer.
      * 
      * @return std::array<std::uint8_t, 32> 
      */
      std::array<std::uint8_t, 32> get_data();
    private:
      /** 
      * @brief Queue to hold the 32 byte long data frames. Queue shall be emptied on
      * each execution slice and the data frames shall be processed.
      * 
      */
      std::queue<std::array<std::uint8_t,32>> _data;
  };
}

#endif