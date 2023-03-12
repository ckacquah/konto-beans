#include <algorithm>

#include "konto/core/event.h"

namespace Konto
{

void Dispatcher::post(const Event& event)
{
    auto type = event.type();
    if (observers_.find(type) == observers_.end())
    {
        return;
    }

    auto&& observers = observers_.at(type);

    for (auto&& observer : observers)
    {
        observer(event);
    }
}

void Dispatcher::subscribe(const Event::Type& descriptor, EventCallback&& callback)
{
    observers_[descriptor].push_back(callback);
}

} // namespace Konto
