namespace propulsion{
  class Esc{
    public:
      auto GetMaxPulseDurationInMicroSeconds() const noexcept -> decltype(auto){
        return 100;
      }

      auto GetMinPulseDurationInMicroSeconds() const noexcept -> decltype(auto){
        return 10;
      }

      auto SetPulseDuration(int pulse_duration, int repetition_period) noexcept -> types::HalError;
  };
}