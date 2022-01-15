#ifndef SRC_COM_COM_NRF24L01_ERROR_HANDLER_HPP_
#define SRC_COM_COM_NRF24L01_ERROR_HANDLER_HPP_

namespace com {
#define ON_ERROR_RETURN(x)                               \
  {                                                      \
    types::DriverStatus macro_return_value;              \
    macro_return_value = x;                              \
    if (macro_return_value != types::DriverStatus::OK) { \
      return macro_return_value;                         \
    }                                                    \
  }
}  // namespace com

#endif