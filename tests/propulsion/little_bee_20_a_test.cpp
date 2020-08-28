#include "little_bee_20_a.hpp"
#include <memory>
#include <utility>
#include "gtest/gtest.h"
#include "stm32g4xx.h"

namespace {

class LittleBeeEscTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    unit_under_test_ = std::make_unique<propulsion::LittleBee20A>(&mock_timer, 2);
    legal_pulse_duration = 150;
    legal_repetition_period = 2000;
    hal_tim_pwm_stop_mock_values.which_return = 0;
    hal_tim_pwm_init_mock_values.which_return = 0;
  }

  void SetHalOk() {
    hal_tim_pwm_stop_mock_values.return_value[0] = HAL_OK;
    hal_tim_pwm_init_mock_values.return_value[0] = HAL_OK;
    hal_tim_pwm_stop_mock_values.return_value[1] = HAL_OK;
    hal_tim_pwm_init_mock_values.return_value[1] = HAL_OK;
    hal_tim_pwm_config_channel_mock_values.return_value = HAL_OK;
    hal_tim_pwm_start_mock_values.return_value = HAL_OK;
  }

  TIM_HandleTypeDef mock_timer;
  std::uint32_t mock_channel;
  std::unique_ptr<propulsion::LittleBee20A> unit_under_test_;
  int legal_pulse_duration;
  int legal_repetition_period;
};

TEST_F(LittleBeeEscTests, get_max_pulse_duration_in_micro_seconds_return_correct_value) {
  ASSERT_EQ(unit_under_test_->GetMaxPulseDurationInMicroSeconds(), 250);
}

TEST_F(LittleBeeEscTests, get_min_pulse_duration_in_micro_seconds_return_correct_value) {
  ASSERT_EQ(unit_under_test_->GetMinPulseDurationInMicroSeconds(), 125);
}

///The following tests are HAL error reaction tests
TEST_F(LittleBeeEscTests, set_pulse_duration_timer_configuration_error_hal_tim_pwm_stop_failed) {
  hal_tim_pwm_stop_mock_values.return_value[0] = HAL_TIMEOUT;
  auto set_pulse_duration_return = unit_under_test_->SetPulseDuration(legal_pulse_duration, legal_repetition_period);
  ASSERT_EQ(set_pulse_duration_return, types::DriverStatus::HAL_ERROR);
}

TEST_F(LittleBeeEscTests, set_pulse_duration_timer_configuration_hal_tim_pwm_init_failed) {
  hal_tim_pwm_stop_mock_values.return_value[0] = HAL_OK;
  hal_tim_pwm_init_mock_values.return_value[0] = HAL_TIMEOUT;
  auto set_pulse_duration_return = unit_under_test_->SetPulseDuration(legal_pulse_duration, legal_repetition_period);
  ASSERT_EQ(set_pulse_duration_return, types::DriverStatus::HAL_ERROR);
}

TEST_F(LittleBeeEscTests, set_pulse_duration_timer_set_pwm_hal_tim_pwm_stop_failed) {
  hal_tim_pwm_stop_mock_values.return_value[0] = HAL_OK;
  hal_tim_pwm_init_mock_values.return_value[0] = HAL_OK;
  hal_tim_pwm_stop_mock_values.return_value[1] = HAL_TIMEOUT;
  auto set_pulse_duration_return = unit_under_test_->SetPulseDuration(legal_pulse_duration, legal_repetition_period);
  ASSERT_EQ(set_pulse_duration_return, types::DriverStatus::HAL_ERROR);
}

TEST_F(LittleBeeEscTests, set_pulse_duration_set_pwm_hal_tim_pwm_init_failed) {
  hal_tim_pwm_stop_mock_values.return_value[0] = HAL_OK;
  hal_tim_pwm_init_mock_values.return_value[0] = HAL_OK;
  hal_tim_pwm_stop_mock_values.return_value[1] = HAL_OK;
  hal_tim_pwm_init_mock_values.return_value[1] = HAL_TIMEOUT;
  auto set_pulse_duration_return = unit_under_test_->SetPulseDuration(legal_pulse_duration, legal_repetition_period);
  ASSERT_EQ(set_pulse_duration_return, types::DriverStatus::HAL_ERROR);
}

TEST_F(LittleBeeEscTests, set_pulse_duration_set_pwm_hal_tim_pwm_configchannel_failed) {
  hal_tim_pwm_stop_mock_values.return_value[0] = HAL_OK;
  hal_tim_pwm_init_mock_values.return_value[0] = HAL_OK;
  hal_tim_pwm_stop_mock_values.return_value[1] = HAL_OK;
  hal_tim_pwm_init_mock_values.return_value[1] = HAL_OK;
  hal_tim_pwm_config_channel_mock_values.return_value = HAL_TIMEOUT;
  auto set_pulse_duration_return = unit_under_test_->SetPulseDuration(legal_pulse_duration, legal_repetition_period);
  ASSERT_EQ(set_pulse_duration_return, types::DriverStatus::HAL_ERROR);
}

TEST_F(LittleBeeEscTests, set_pulse_duration_set_pwm_hal_tim_pwm_start_failed) {
  hal_tim_pwm_stop_mock_values.return_value[0] = HAL_OK;
  hal_tim_pwm_init_mock_values.return_value[0] = HAL_OK;
  hal_tim_pwm_stop_mock_values.return_value[1] = HAL_OK;
  hal_tim_pwm_init_mock_values.return_value[1] = HAL_OK;
  hal_tim_pwm_config_channel_mock_values.return_value = HAL_OK;
  hal_tim_pwm_start_mock_values.return_value = HAL_TIMEOUT;
  auto set_pulse_duration_return = unit_under_test_->SetPulseDuration(legal_pulse_duration, legal_repetition_period);
  ASSERT_EQ(set_pulse_duration_return, types::DriverStatus::HAL_ERROR);
}

TEST_F(LittleBeeEscTests, set_pulse_duration_no_hal_errors) {
  SetHalOk();
  auto set_pulse_duration_return = unit_under_test_->SetPulseDuration(legal_pulse_duration, legal_repetition_period);
  ASSERT_EQ(set_pulse_duration_return, types::DriverStatus::OK);
}

///The following tests, test the illegal bounds of SetPulseDuration
TEST_F(LittleBeeEscTests, set_pulse_duration_lower_illegal_pulse_duration) {
  auto min_allowed_pulse_duration = unit_under_test_->GetMinPulseDurationInMicroSeconds();
  auto set_pulse_duration_return = unit_under_test_->SetPulseDuration(min_allowed_pulse_duration - 1, legal_repetition_period);
  ASSERT_EQ(set_pulse_duration_return, types::DriverStatus::INPUT_ERROR);
}

TEST_F(LittleBeeEscTests, set_pulse_duration_upper_illegal_pulse_duration) {
  auto max_allowed_pulse_duration = unit_under_test_->GetMaxPulseDurationInMicroSeconds();
  auto set_pulse_duration_return = unit_under_test_->SetPulseDuration(max_allowed_pulse_duration + 1, legal_repetition_period);
  ASSERT_EQ(set_pulse_duration_return, types::DriverStatus::INPUT_ERROR);
}

TEST_F(LittleBeeEscTests, set_pulse_duration_lower_illegal_repitition_period) {
  auto min_allowed_repetition_period = legal_pulse_duration;
  auto set_pulse_duration_return = unit_under_test_->SetPulseDuration(legal_pulse_duration, min_allowed_repetition_period - 1);
  ASSERT_EQ(set_pulse_duration_return, types::DriverStatus::INPUT_ERROR);
}

TEST_F(LittleBeeEscTests, set_pulse_duration_upper_illegal_repitition_period) {
  auto max_allowed_repetition_period = 20000;
  auto set_pulse_duration_return = unit_under_test_->SetPulseDuration(legal_pulse_duration, max_allowed_repetition_period + 1);
  ASSERT_EQ(set_pulse_duration_return, types::DriverStatus::INPUT_ERROR);
}

TEST_F(LittleBeeEscTests, set_pulse_duration_double_parameter_error) {
  auto max_allowed_pulse_duration = unit_under_test_->GetMaxPulseDurationInMicroSeconds();
  auto min_allowed_repetition_period = legal_pulse_duration;
  auto set_pulse_duration_return = unit_under_test_->SetPulseDuration(max_allowed_pulse_duration + 1, min_allowed_repetition_period - 1);
  ASSERT_EQ(set_pulse_duration_return, types::DriverStatus::INPUT_ERROR);
}

/// The following tests, test the legal bounds of SetPulseDuration
TEST_F(LittleBeeEscTests, set_pulse_duration_min_legal_lower_pulse_duration) {
  SetHalOk();
  auto min_allowed_pulse_duration = unit_under_test_->GetMinPulseDurationInMicroSeconds();
  auto set_pulse_duration_return = unit_under_test_->SetPulseDuration(min_allowed_pulse_duration, legal_repetition_period);
  ASSERT_EQ(set_pulse_duration_return, types::DriverStatus::OK);
}

TEST_F(LittleBeeEscTests, set_pulse_duration_max_legal_upper_pulse_duration) {
  SetHalOk();
  auto max_allowed_pulse_duration = unit_under_test_->GetMaxPulseDurationInMicroSeconds();
  auto set_pulse_duration_return = unit_under_test_->SetPulseDuration(max_allowed_pulse_duration, legal_repetition_period);
  ASSERT_EQ(set_pulse_duration_return, types::DriverStatus::OK);
}

TEST_F(LittleBeeEscTests, set_pulse_duration_min_legal_repetition_period) {
  SetHalOk();
  auto min_allowed_repetition_period = legal_pulse_duration;
  auto set_pulse_duration_return = unit_under_test_->SetPulseDuration(legal_pulse_duration, min_allowed_repetition_period);
  ASSERT_EQ(set_pulse_duration_return, types::DriverStatus::OK);
}

TEST_F(LittleBeeEscTests, set_pulse_duration_max_legal_repetition_period) {
  SetHalOk();
  auto max_allowed_repetition_period = 20000;
  auto set_pulse_duration_return = unit_under_test_->SetPulseDuration(legal_pulse_duration, max_allowed_repetition_period);
  ASSERT_EQ(set_pulse_duration_return, types::DriverStatus::OK);
}

TEST_F(LittleBeeEscTests, set_pulse_duration_both_parameters_lower_bounds) {
  SetHalOk();
  auto min_allowed_pulse_duration = unit_under_test_->GetMinPulseDurationInMicroSeconds();
  auto min_allowed_repitition_period = min_allowed_pulse_duration;
  auto set_pulse_duration_return = unit_under_test_->SetPulseDuration(min_allowed_pulse_duration, min_allowed_repitition_period);
  ASSERT_EQ(set_pulse_duration_return, types::DriverStatus::OK);
}

TEST_F(LittleBeeEscTests, set_pulse_duration_both_parameters_upper_bounds) {
  SetHalOk();
  auto max_allowed_pulse_duration = unit_under_test_->GetMaxPulseDurationInMicroSeconds();
  auto max_allowed_repitition_period = 20000;
  auto set_pulse_duration_return = unit_under_test_->SetPulseDuration(max_allowed_pulse_duration, max_allowed_repitition_period);
  ASSERT_EQ(set_pulse_duration_return, types::DriverStatus::OK);
}
}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}