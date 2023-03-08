#ifndef __KONTO_EDITOR_WINDOW_H__
#define __KONTO_EDITOR_WINDOW_H__

#include <string>

#include <GLFW/glfw3.h>

namespace Konto::Editor
{

class Window
{
  private:
    uint32_t width_{};
    uint32_t height_{};

    std::string name_{};

    GLFWwindow* handle_{};

  public:
    Window(const std::string& title, uint32_t width, uint32_t height);
    ~Window();

    void update();
    void destroy();
    bool is_closed() const;

    GLFWwindow* handle()
    {
        return handle_;
    }

    uint32_t width()
    {
        return width_;
    }

    uint32_t height()
    {
        return height_;
    }
};

} // namespace Konto::Editor

#endif // __KONTO_EDITOR_WINDOW_H__
