#ifndef SRC_PROPULSION_MOTOR_DRIVER_HPP_
#define SRC_PROPULSION_MOTOR_DRIVER_HPP_

#include <array>
#include <cstdint>
#include <memory>
#include "abstract_motor_builder.hpp"
#include "abstract_motor_driver.hpp"
#include "error_types.hpp"
#include "motor.hpp"

#ifndef UNIT_TEST
#include "propulsion_hardware_config.hpp"
#else
#include "propulsion_hardware_config_mock.hpp"
#endif

namespace propulsion {

class MotorDriver : public AbstractMotorDriver {
 public:
  /**
   * @brief Construct a new Motor Driver object and initialize all Motors and ESCs.
   * Hardfaults if something doesn't work.
   * 
   * Hardware configuration is hardcoded and not dynamic for now.
   * @param builder the builder object which can buil the motors
   */
  explicit MotorDriver(std::unique_ptr<AbstractMotorBuilder> builder);

  MotorDriver() = delete;

  /// The default destructor is enough
  ~MotorDriver() = default;

  auto SetMotorSpeed(const MotorPosition which_motor, const float speed) const noexcept -> const types::DriverStatus override;

  auto GetMotorSpeed(const MotorPosition which_motor) const noexcept -> std::pair<float, types::DriverStatus> override;

  auto ArmEscs() const noexcept -> const types::DriverStatus override;

 private:
  std::unique_ptr<AbstractMotorBuilder> motor_builder_;
  static constexpr auto NUMBER_OF_MOTORS_ = 4;
  static constexpr std::uint32_t DELAY_TIME_MS_ = 1000;
  std::array<std::unique_ptr<Motor>, NUMBER_OF_MOTORS_> motors_;

  auto InitializeMotor(MotorPosition position, PropulsionHardwareConfig &config) noexcept -> void;
  auto SetSpeedForAllMotors(const float speed) const noexcept -> const types::DriverStatus;
};
}  // namespace propulsion
#endif