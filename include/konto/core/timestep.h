#ifndef __KONTO_CORE_TIMESTEP_H__
#define __KONTO_CORE_TIMESTEP_H__

#include <chrono>
#include <ctime>

namespace Konto
{

class TimeStep
{
  private:
    std::time_t timestep_{};

  public:
    TimeStep() : timestep_(std::time(nullptr))
    {
    }
    TimeStep(const TimeStep& timestep) = default;

    float delta()
    {
        auto prev = timestep_;
        timestep_ = std::time(nullptr);
        return (prev - timestep_) / 1000;
    }
};

} // namespace Konto

#endif // __KONTOCORE_CORE_TIMESTEP_H__