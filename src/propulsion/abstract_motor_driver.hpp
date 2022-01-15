#ifndef SRC_PROPULSION_ABSTRACT_MOTOR_DRIVER_HPP_
#define SRC_PROPULSION_ABSTRACT_MOTOR_DRIVER_HPP_

#include <array>
#include "error_types.hpp"

namespace propulsion {

enum class MotorPosition : int {
  LEFT_FRONT = 0,
  RIGHT_FRONT = 1,
  LEFT_REAR = 2,
  RIGHT_REAR = 3
};

class AbstractMotorDriver {
 public:
  AbstractMotorDriver() = default;
  virtual ~AbstractMotorDriver() = default;

  /**
   * 
   * @brief Apply speed to a motor
   * 
   * @param which_motor is the chosen motor position
   * @param speed speed between 0 and 100%
   * 
   * @return  DriverStatus::OK on success
   *          DriverStatus::INPUT_ERROR if speed was wrong
   *          DriverStatus::HAL_ERROR if Motor object reports problem
   */
  virtual auto SetMotorSpeed(const MotorPosition which_motor, const float speed) const noexcept -> const types::DriverStatus = 0;

  /**
   * 
   * @brief Get motor speed from one specific motor references by Motorposition
   * 
   * @param which_motor is the chosen motor position
   * 
   * @return  std::pair<speed, DriverStatus::OK> indicates success and returns speed
   *          std::pair<-1, DriverStatus::HAL_ERROR> indicates an error and returns an invalid speed
   */
  virtual auto GetMotorSpeed(const MotorPosition which_motor) const noexcept -> std::pair<types::DriverStatus, float> = 0;

  /**
   * @brief Arm all ESCs (blocking)
   * 
   * @return const types::DriverStatus::OK on success
   *         const types::DriverStatus::HAL_ERROR if ESCs could not be armed
   */
  virtual auto ArmEscs() const noexcept -> const types::DriverStatus = 0;
};

}  // namespace propulsion

#endif