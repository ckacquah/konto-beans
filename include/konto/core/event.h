#ifndef __KONTO_CORE_EVENT_H__
#define __KONTO_CORE_EVENT_H__

#include <functional>
#include <map>
#include <tuple>
#include <typeinfo>
#include <vector>

#include "input.h"

namespace Konto
{

class Event
{
  public:
    virtual ~Event(){};

    using Type = const char*;

    virtual Type type() const = 0;
};

class Dispatcher
{
  public:
    using EventCallback = std::function<void(const Event&)>;

  private:
    std::map<Event::Type, std::vector<EventCallback>> observers_;

  public:
    void post(const Event& event);
    void subscribe(const Event::Type& descriptor, EventCallback&& callback);
};

class KeyboardButtonEvent : public Event
{
  private:
    Input::Action action_{};
    Input::Keyboard::Button button_{};

  public:
    ~KeyboardButtonEvent(){};
    KeyboardButtonEvent() = default;
    KeyboardButtonEvent(Input::Keyboard::Button button, Input::Action action) : button_(button), action_(action){};

    static constexpr Event::Type descriptor = "KeyboardButtonEvent";

    Input::Action action() const
    {
        return action_;
    }

    Input::Keyboard::Button button() const
    {
        return button_;
    }

    Event::Type type() const override
    {
        return descriptor;
    }
};

class MouseButtonEvent : public Event
{
  private:
    Input::Action action_{};
    Input::Mouse::Button button_{};

  public:
    ~MouseButtonEvent(){};
    MouseButtonEvent() = default;
    MouseButtonEvent(Input::Mouse::Button button, Input::Action action) : button_(button), action_(action){};

    static constexpr Event::Type descriptor = "MouseButtonEvent";

    Input::Action action() const
    {
        return action_;
    }

    Input::Mouse::Button button() const
    {
        return button_;
    }

    Event::Type type() const override
    {
        return descriptor;
    }
};

class MouseCursorEvent : public Event
{
  private:
    double x_{};
    double y_{};

  public:
    ~MouseCursorEvent(){};
    MouseCursorEvent() = default;
    MouseCursorEvent(double _x, double _y) : x_(_x), y_(_y){};

    static constexpr Event::Type descriptor = "MouseCursorEvent";

    std::tuple<double, double> position() const
    {
        return std::make_tuple(x_, y_);
    }

    Event::Type type() const override
    {
        return descriptor;
    }
};

class ScrollInputEvent : public Event
{
  private:
    double xoffset{};
    double yoffset{};

  public:
    ~ScrollInputEvent(){};
    ScrollInputEvent() = default;
    ScrollInputEvent(double _xoffset, double _yoffset) : xoffset(_xoffset), yoffset(_yoffset){};

    static constexpr Event::Type descriptor = "ScrollInputEvent";

    std::tuple<double, double> offset() const
    {
        return std::make_tuple(xoffset, yoffset);
    }

    Event::Type type() const override
    {
        return descriptor;
    }
};

} // namespace Konto

#endif // __KONTO_CORE_EVENT_H__
