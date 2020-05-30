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
       * @return types::ComError COM_OK if ok, COM_BUFFER_IO_ERROR if not ok.
       * 
       */
      auto PutData(std::array<std::uint8_t, 32> &data) noexcept -> types::ComError;

      /** 
       * @brief Retrieve data frame from queue buffer.
       * 
       * @return std::array<std::uint8_t, 32> 
       * 
       */
      auto GetData() noexcept -> std::array<std::uint8_t, 32>;
    
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
      auto CheckData(std::array<std::uint8_t, 32> &data) const noexcept -> types::ComError;

      // The maximum length for the queue.
      static constexpr std::uint8_t max_queue_len = 5;
  };
}

#endif
