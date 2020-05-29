#ifndef SRC_COM_MESSAGE_BUFFER_HPP_
#define SRC_COM_MESSAGE_BUFFER_HPP_

#include <array>
#include <queue>
#include "com_types.hpp"

namespace com {
  /** 
    * @brief This class represents a queue style buffer for communication
    * frames exchanged between drones.
    * 
    */
  class ComMessageBuffer {
    public:
      /** 
       * @brief Construct a new Com Message Buffer object
       * 
       */
      ComMessageBuffer(){};

      /** 
       * @brief Transfer data to queue buffer. 
       * 
       * @param data Reference to data frame. Must conform to data frame specifications.
       * @return uint8_t Returns 0 on no error, otherwise negative value.
       * 
       */
      types::ComError put_data(std::array<std::uint8_t, 32> &data);

      /** 
       * @brief Retrieve data frame from queue buffer.
       * 
       * @return std::array<std::uint8_t, 32> 
       * 
       */
      std::array<std::uint8_t, 32> get_data();
    
    protected:
      /** 
       * @brief Queue to hold the 32 byte long data frames. Queue shall be emptied on
       * each execution slice and the data frames shall be processed.
       * 
       */
      std::queue<std::array<std::uint8_t,32>> data_;

      /**
       * @brief Check if queue front entry matches data parameter
       * 
       * @param data Data to be checked against
       * @return types::ComError COM_OK if ok, COM_BUFFER_IO_ERROR if not ok.
       */
      types::ComError check_data(std::array<std::uint8_t, 32> &data);

      // The maximum length for the queue.
      const std::uint8_t max_queue_len = 5;
  };
}

#endif
