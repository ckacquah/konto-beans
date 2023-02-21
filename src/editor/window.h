#ifndef __KONTO_EDITOR_WINDOW_H__
#define __KONTO_EDITOR_WINDOW_H__

#include <string>

#include <GLFW/glfw3.h>

namespace Konto::Editor
{

struct WindowData
{
    uint32_t width{};
    uint32_t height{};

    std::string name{};

    GLFWwindow* handle{};
};

class Window
{
  private:
    static WindowData context_;

  public:
    static void end();
    static void begin();
    static void destroy();
    static bool is_closed();
    static void start(const std::string& title, uint32_t width, uint32_t height);

    static uint32_t width()
    {
        return context_.width;
    }

    static uint32_t height()
    {
        return context_.height;
    }
};

} // namespace Konto::Editor

#endif // __KONTO_EDITOR_WINDOW_H__
