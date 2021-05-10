#ifndef SRC_COM_COM_INTERRUPT_HANDLER_HPP_
#define SRC_COM_COM_INTERRUPT_HANDLER_HPP_

#include "com_nrf24l01.hpp"

namespace com {

class ComInterruptHandler {
 public:
  static auto HandleComInterrupt() -> void {
    com_->HandleRxIRQ();
  };

  ComInterruptHandler(std::shared_ptr<com::NRF24L01> com_object) {
    com_ = com_object;
  };
  ComInterruptHandler() = delete;
  ~ComInterruptHandler() = default;

 private:
  static std::shared_ptr<com::NRF24L01> com_;
};

}  // namespace com

#endif