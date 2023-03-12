#ifndef __KONTO_CORE_TIMESTEP_H__
#define __KONTO_CORE_TIMESTEP_H__

#include <chrono>

using namespace std::chrono_literals;

namespace Konto
{

static const std::chrono::nanoseconds second{1s};

class TimeStep
{
  private:
    std::chrono::system_clock::time_point timestep_{};

  public:
    TimeStep() : timestep_(std::chrono::system_clock::now()){};
    TimeStep(const TimeStep& timestep) = default;

    float delta()
    {
        auto prev = timestep_;
        timestep_ = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(timestep_ - prev);
        return static_cast<float>(duration.count()) / second.count();
    }
};

} // namespace Konto

#endif // __KONTOCORE_CORE_TIMESTEP_H__