#ifndef __KONTO_EDITOR_APPLICATION_H__
#define __KONTO_EDITOR_APPLICATION_H__

#include <memory>
#include <tuple>

#include "context.h"
#include "window.h"

namespace Konto::Editor
{

class Application
{
  private:
    std::unique_ptr<Window> window_{};
    static std::shared_ptr<EditorContext> context_;

    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void cursor_position_callback(GLFWwindow* window, double x, double y);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void keyboard_button_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

  public:
    Application() = default;
    ~Application();

    std::shared_ptr<EditorContext> context()
    {
        return context_;
    }

    void start(const std::string& name, uint32_t width, uint32_t height);

    bool closed();
    void destroy();
    void end_frame();
    void begin_frame();
};

} // namespace Konto::Editor

#endif // __KONTO_EDITOR_APPLICATION_H__