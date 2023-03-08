#ifndef __KONTO_CORE_INPUT_H__
#define __KONTO_CORE_INPUT_H__

#include <algorithm>
#include <tuple>
#include <vector>

namespace Konto
{

namespace Input
{

enum Type
{
    KEY,
    MOUSE,
    GAMEPAD,
    JOYSTICK,
};

enum Joystick
{
    ID_01 = 0,
    ID_02 = 1,
    ID_03 = 2,
    ID_04 = 3,
    ID_05 = 4,
    ID_06 = 5,
    ID_07 = 6,
    ID_08 = 7,
    ID_09 = 8,
    ID_10 = 9,
    ID_11 = 10,
    ID_12 = 11,
    ID_13 = 12,
    ID_14 = 13,
    ID_15 = 14,
    ID_16 = 15,
    MIN_ID = ID_01,
    MAX_ID = ID_16,
    CENTERED = 0,
    UP = 1,
    DOWN = 4,
    LEFT = 8,
    RIGHT = 2,
    LEFT_UP = (LEFT | UP),
    RIGHT_UP = (RIGHT | UP),
    LEFT_DOWN = (LEFT | DOWN),
    RIGHT_DOWN = (RIGHT | DOWN),
};

namespace Keyboard
{

enum Button
{
    SPACE = 32,
    APOSTROPHE = 39,
    COMMA = 44,
    MINUS = 45,
    PERIOD = 46,
    SLASH = 47,
    ZERO = 48,
    ONE = 49,
    TWO = 50,
    THREE = 51,
    FOUR = 52,
    FIVE = 53,
    SIX = 54,
    SEVEN = 55,
    EIGHT = 56,
    NINE = 57,
    SEMICOLON = 59,
    EQUAL = 61,
    A = 65,
    B = 66,
    C = 67,
    D = 68,
    E = 69,
    F = 70,
    G = 71,
    H = 72,
    I = 73,
    J = 74,
    K = 75,
    L = 76,
    M = 77,
    N = 78,
    O = 79,
    P = 80,
    Q = 81,
    R = 82,
    S = 83,
    T = 84,
    U = 85,
    V = 86,
    W = 87,
    X = 88,
    Y = 89,
    Z = 90,
    LEFT_BRACKET = 91,
    BACKSLASH = 92,
    RIGHT_BRACKET = 93,
    GRAVE_ACCENT = 96,
    WORLD_1 = 161,
    WORLD_2 = 162,
    ESCAPE = 256,
    ENTER = 257,
    TAB = 258,
    BACKSPACE = 259,
    INSERT = 260,
    DELETE = 261,
    RIGHT = 262,
    LEFT = 263,
    DOWN = 264,
    UP = 265,
    PAGE_UP = 266,
    PAGE_DOWN = 267,
    HOME = 268,
    END = 269,
    CAPS_LOCK = 280,
    SCROLL_LOCK = 281,
    NUM_LOCK = 282,
    PRINT_SCREEN = 283,
    PAUSE = 284,
    F1 = 290,
    F2 = 291,
    F3 = 292,
    F4 = 293,
    F5 = 294,
    F6 = 295,
    F7 = 296,
    F8 = 297,
    F9 = 298,
    F10 = 299,
    F11 = 300,
    F12 = 301,
    F13 = 302,
    F14 = 303,
    F15 = 304,
    F16 = 305,
    F17 = 306,
    F18 = 307,
    F19 = 308,
    F20 = 309,
    F21 = 310,
    F22 = 311,
    F23 = 312,
    F24 = 313,
    F25 = 314,
    KP_0 = 320,
    KP_1 = 321,
    KP_2 = 322,
    KP_3 = 323,
    KP_4 = 324,
    KP_5 = 325,
    KP_6 = 326,
    KP_7 = 327,
    KP_8 = 328,
    KP_9 = 329,
    KP_DECIMAL = 330,
    KP_DIVIDE = 331,
    KP_MULTIPLY = 332,
    KP_SUBTRACT = 333,
    KP_ADD = 334,
    KP_ENTER = 335,
    KP_EQUAL = 336,
    LEFT_SHIFT = 340,
    LEFT_CONTROL = 341,
    LEFT_ALT = 342,
    LEFT_SUPER = 343,
    RIGHT_SHIFT = 344,
    RIGHT_CONTROL = 345,
    RIGHT_ALT = 346,
    RIGHT_SUPER = 347,
    MENU = 348,
    MAX = MENU,
};

class State
{
  private:
    uint8_t buttons[Keyboard::MAX + 1]{};

  public:
    State() = default;
    State(const State&) = default;

    void press(Keyboard::Button button)
    {
        buttons[static_cast<int>(button)] = 1;
    }

    void release(Keyboard::Button button)
    {
        buttons[static_cast<int>(button)] = 0;
    }

    bool is_pressed(Keyboard::Button button) const
    {
        return buttons[static_cast<int>(button)] == 1;
    }
};

} // namespace Keyboard

namespace Mouse
{

enum Button
{
    _1 = 0,
    _2 = 1,
    _3 = 2,
    _4 = 3,
    _5 = 4,
    _6 = 5,
    _7 = 6,
    _8 = 7,
    LEFT = _1,
    RIGHT = _2,
    MIDDLE = _3,
    MIN = _1,
    MAX = _8,
};

class State
{
  private:
    std::tuple<double, double> position_;
    uint8_t buttons[Mouse::Button::MAX + 1]{};

  public:
    State() = default;
    State(const State&) = default;

    void press(Mouse::Button button)
    {
        buttons[static_cast<int>(button)] = 1;
    }

    void release(Mouse::Button button)
    {
        buttons[static_cast<int>(button)] = 0;
    }

    bool is_pressed(Mouse::Button button) const
    {
        return buttons[static_cast<int>(button)] == 1;
    }

    std::tuple<double, double> position() const
    {
        return position_;
    }

    void set_position(double x, double y)
    {
        position_ = std::tuple<double, double>(x, y);
    }
};

} // namespace Mouse

struct GamePad
{
    enum Button
    {
        A = 0,
        B = 1,
        X = 2,
        Y = 3,
        LEFT_BUMPER = 4,
        RIGHT_BUMPER = 5,
        BACK = 6,
        START = 7,
        GUIDE = 8,
        LEFT_THUMB = 9,
        RIGHT_THUMB = 10,
        DPAD_UP = 11,
        DPAD_RIGHT = 12,
        DPAD_DOWN = 13,
        DPAD_LEFT = 14,
        CROSS = A,
        CIRCLE = B,
        SQUARE = X,
        TRIANGLE = Y,
        MAX = DPAD_LEFT,
    };

    enum Axis
    {
        LEFT_X = 0,
        LEFT_Y = 1,
        RIGHT_X = 2,
        RIGHT_Y = 3,
        LEFT_TRIGGER = 4,
        RIGHT_TRIGGER = 5,
    };

    class State
    {
      private:
        float axes_[6]{};
        uint8_t buttons[GamePad::Button::MAX + 1]{};

      public:
        State() = default;
        State(const State&) = default;

        void press(GamePad::Button button)
        {
            buttons[static_cast<int>(button)] = 1;
        }

        void release(GamePad::Button button)
        {
            buttons[static_cast<int>(button)] = 0;
        }

        bool is_pressed(GamePad::Button button) const
        {
            return buttons[static_cast<int>(button)] == 1;
        }

        float axes(GamePad::Axis axis) const
        {
            return axes_[axis];
        }

        void set_axes(GamePad::Axis axis, float value)
        {
            axes_[axis] = value;
        }
    };

    std::string name;
    Input::Joystick id;
    Input::GamePad::State state;
};

} // namespace Input

struct InputContext
{
    Input::Mouse::State mouse{};
    Input::Keyboard::State keyboard{};
    Input::GamePad gamepads[Input::Joystick::MAX_ID + 1]{};

    InputContext() = default;
    InputContext(const InputContext&) = default;
};

} // namespace Konto

#endif // __KONTO_CORE_INPUT_H__