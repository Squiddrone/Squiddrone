#ifndef SRC_PROPULSION_MOTOR_DRIVER_HPP_
#define SRC_PROPULSION_MOTOR_DRIVER_HPP_

#include <array>
#include <memory>
#include "error_types.hpp"
#include "propulsion_hardware_config.hpp"

#ifndef UNIT_TEST
#include "motor.hpp"
#else
#include "motor_mock.hpp"
#endif

namespace propulsion {

enum class MotorPosition : int {
  LEFT_FRONT = 0,
  RIGHT_FRONT = 1,
  LEFT_REAR = 2,
  RIGHT_REAR = 3
};

class MotorDriver {
 public:
  /**
   * @brief Construct a new Motor Driver object and initialize all Motors and ESCs.
   * Hardfaults if something doesn't work.
   * 
   * Hardware configuration is hardcoded and not dynamic for now.
   * 
   */
  MotorDriver();

  /// The default destructor is enough
  ~MotorDriver() = default;

  /**
   * 
   * @brief Apply speed to all motors
   * 
   * @param which_motor is the chosen motor position
   * @param speed speed between 0 and 100%
   * 
   * @return  DriverStatus::OK on success
   *          DriverStatus::INPUT_ERROR if speed was wrong
   *          DriverStatus::HAL_ERROR if Motor object reports problem
   */
  auto SetMotorSpeed(const MotorPosition which_motor, const float speed) const noexcept -> const types::DriverStatus;

  auto GetMotorSpeed(const MotorPosition which_motor) const noexcept -> std::pair<float, types::DriverStatus>;

  /**
   * @brief Arm all ESCs (blocking)
   * 
   * @return const types::DriverStatus 
   */
  auto ArmEsc() const noexcept -> const types::DriverStatus;

 private:
  static constexpr auto NUMBER_OF_MOTORS_ = 4;
  std::array<std::unique_ptr<Motor>, NUMBER_OF_MOTORS_> motors_;

  auto InitializeMotor(MotorPosition position, PropulsionHardwareConfig &config) noexcept -> void;
};

}  // namespace propulsion
#endif