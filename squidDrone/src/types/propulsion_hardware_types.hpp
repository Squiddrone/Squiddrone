#ifndef SRC_TYPES_PROPULSION_HARDWARE_TYPES_HPP_
#define SRC_TYPES_PROPULSION_HARDWARE_TYPES_HPP_


namespace types{

  ///
  /// @brief Enum for setting the motor
  ///
  enum class MotorType: int{
    /// Motor is Letodar 2204 brushless DC motor
    LETODAR_2204
  };

  ///
  /// @brief Enum for setting the esc
  ///
  enum class EscType: int{
    /// Little bee esc 20 a ESC with oneshot125 protocol
    LITTLE_BEE_20_A
  };

}

#endif