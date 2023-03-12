#ifndef __KONTO_CORE_INPUT_H__
#define __KONTO_CORE_INPUT_H__

#include <algorithm>
#include <iterator>
#include <string>

namespace Konto
{

namespace Input
{

enum Type
{
    MOUSE,
    GAMEPAD,
    KEYBOARD,
};

enum Action
{
    PRESSED,
    RELEASED,
    REPEATED,
};

namespace Keyboard
{

enum Button
{
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
    NUM_0 = 48,
    NUM_1 = 49,
    NUM_2 = 50,
    NUM_3 = 51,
    NUM_4 = 52,
    NUM_5 = 53,
    NUM_6 = 54,
    NUM_7 = 55,
    NUM_8 = 56,
    NUM_9 = 57,
    SPACE = 32,
    COMMA = 44,
    MINUS = 45,
    SLASH = 47,
    EQUAL = 61,
    UP = 265,
    END = 269,
    TAB = 258,
    HOME = 268,
    LEFT = 263,
    DOWN = 264,
    MENU = 348,
    ENTER = 257,
    RIGHT = 262,
    PAUSE = 284,
    PERIOD = 46,
    INSERT = 260,
    DELETE = 261,
    ESCAPE = 256,
    KP_ADD = 334,
    PAGE_UP = 266,
    WORLD_1 = 161,
    WORLD_2 = 162,
    SEMICOLON = 59,
    BACKSLASH = 92,
    LEFT_ALT = 342,
    KP_ENTER = 335,
    KP_EQUAL = 336,
    NUM_LOCK = 282,
    RIGHT_ALT = 346,
    BACKSPACE = 259,
    KP_DIVIDE = 331,
    PAGE_DOWN = 267,
    APOSTROPHE = 39,
    CAPS_LOCK = 280,
    LEFT_SHIFT = 340,
    LEFT_SUPER = 343,
    KP_DECIMAL = 330,
    RIGHT_SUPER = 347,
    RIGHT_SHIFT = 344,
    SCROLL_LOCK = 281,
    KP_MULTIPLY = 332,
    KP_SUBTRACT = 333,
    LEFT_BRACKET = 91,
    GRAVE_ACCENT = 96,
    PRINT_SCREEN = 283,
    LEFT_CONTROL = 341,
    RIGHT_CONTROL = 345,
    RIGHT_BRACKET = 93,
};

} // namespace Keyboard

namespace Mouse
{

enum Button
{
    LEFT = 0,
    RIGHT = 1,
    MIDDLE = 2
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

    float axis[6]{};
    Action buttons[15]{};

    uint8_t id() const
    {
        return id_;
    }

    const std::string& name() const
    {
        return name_;
    }

    GamePad(GamePad& other) : id_(other.id_), name_(other.name_)
    {
        std::copy(std::begin(other.axis), std::end(other.axis), std::begin(axis));
        std::copy(std::begin(other.buttons), std::end(other.buttons), std::begin(buttons));
    }

    GamePad(uint8_t id, const std::string& name) : id_(id), name_(name){};

  private:
    uint8_t id_{};
    std::string name_{};
};

} // namespace Input

} // namespace Konto

#endif // __KONTO_CORE_INPUT_H__