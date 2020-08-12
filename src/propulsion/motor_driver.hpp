#ifndef SRC_PROPULSION_MOTOR_DRIVER_HPP_
#define SRC_PROPULSION_MOTOR_DRIVER_HPP_

#include <array>
#include <memory>
#include "basic_types.hpp"
#include "error_types.hpp"
#include "motor.hpp"

namespace propulsion {

enum class MotorPosition : int {
  LEFT_FRONT = 0,
  RIGHT_FRONT = 1,
  LEFT_BACK = 2,
  RIGHT_BACK = 3
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
   * @brief Applies an euclidean vector to the current state of the motors
   * 
   * @param thrust_vector An euclidean vector of float where each coordinate is between -1.0 and +1.0
   * @return const types::DriverStatus if an error occured in applying a thrust vector, DriverStatus::OK if everything
   * is alright
   */
  auto ApplyThrustVector(types::EuclideanVector<float> thrust_vector) const noexcept -> const types::DriverStatus;

  /**
   * @brief Arm all ESCs
   * 
   * @return const types::DriverStatus 
   */
  auto ArmEsc() const noexcept -> const types::DriverStatus;

 private:
  static constexpr auto NUMBER_OF_MOTORS_ = 4;
  std::array<std::unique_ptr<Motor>, NUMBER_OF_MOTORS_> motors_;
};

}  // namespace propulsion
#endif