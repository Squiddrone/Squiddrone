#ifndef SRC_COM_INTERFACE_HPP_
#define SRC_COM_INTERFACE_HPP_

#ifndef UNIT_TEST
#include "com_message_buffer.hpp"
#else
#include "com_message_buffer_mock.hpp"
#endif
#include "com_types.hpp"
#include "error_types.hpp"

#include <memory>

namespace com {

/**
 * @brief This is a purely virtual class to act as
 * a facade for the device specific implementation.
 *
 */
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
   * @param msg_buf Pointer to an instance of a com message buffer object.
   */
  explicit ComInterface(std::unique_ptr<com::ComMessageBuffer> msg_buf) : msg_buffer_(std::move(msg_buf)){};

  /**
   * @brief Virtual destructor.
   *
   */
  virtual ~ComInterface() = default;

  /**
   * @brief Get the data packet object
   *
   * @return types::ComDataPacket Returns a data packet of type types::ComDataPacket.
   */
  virtual auto GetDataPacket() const noexcept -> types::ComDataPacket = 0;

  /**
   * @brief Transmit dataframe of max length 32 byte via the drones' wifi interface.
   *
   * @param target_id target_id The id of the receiver. See also types::PutDataPacketTarget.
   * @param packet A data packet of type types::ComDataPacket
   * @return types::DriverStatus COM_OK in case of successful transmission, error code in case something
   * went wrong.
   */
  virtual auto PutDataPacket(types::PutDataPacketTarget target_id, types::ComDataPacket &packet) noexcept
      -> types::DriverStatus = 0;

 protected:
  /**
   * @brief Unique pointer to an instance of a message buffer queue.
   *
   */
  std::unique_ptr<com::ComMessageBuffer> msg_buffer_;
};
}  // namespace com

#endif
