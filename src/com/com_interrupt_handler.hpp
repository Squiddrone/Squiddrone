#ifndef SRC_COM_COM_INTERRUPT_HANDLER_HPP_
#define SRC_COM_COM_INTERRUPT_HANDLER_HPP_

#ifndef UNIT_TEST
#include "com_nrf24l01.hpp"
#else
#include "com_nrf24l01_mock.hpp"
#endif

namespace com {

class ComInterruptHandler {
 public:
  static auto HandleComInterrupt() noexcept -> void {
    com_->HandleRxIRQ();
  };

  static auto SetComDriver(std::shared_ptr<com::NRF24L01> com_object) noexcept -> void {
    com_ = com_object;
  };
  ComInterruptHandler() = delete;
  ~ComInterruptHandler() = default;

 private:
  static std::shared_ptr<com::NRF24L01> com_;
};

}  // namespace com

#endif
