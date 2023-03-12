#ifndef __KONTO_EDITOR_PANEL_VIEWPORT_H__
#define __KONTO_EDITOR_PANEL_VIEWPORT_H__

#include <memory>

#include <imgui/imgui.h>

#include "editor/context.h"
#include "konto.h"

namespace Konto::Editor
{

struct ViewportPanelContext
{
    SceneCamera camera{};
    std::shared_ptr<EditorContext> editor{};

    glm::vec3 camera_scale{1.0f};
    glm::vec3 camera_rotation{0.0f};
    glm::vec3 camera_translation{0.0f};

    glm::vec4 clear_color{0.5f, 0.0f, 1.0f, 1.0f};

    std::shared_ptr<Knt::FrameBuffer> framebuffer{};

    ViewportPanelContext() = default;
    ViewportPanelContext(const ViewportPanelContext& other) = default;

    glm::mat4 camera_transform()
    {
        return glm::translate(glm::mat4(1.0f), camera_translation) * glm::toMat4(glm::quat(camera_rotation)) *
               glm::scale(glm::mat4(1.0f), camera_scale);
    }
};

class ViewportPanel
{
  private:
    static ViewportPanelContext context_;

    static void render_viewport();

  public:
    static void render();
    static void resize(uint32_t width, uint32_t height);
    static void init(std::shared_ptr<EditorContext> editor);

    static ViewportPanelContext& viewport_data()
    {
        return context_;
    }
};

class KeyboardButtonObserver
{
  private:
    ViewportPanelContext* context_{nullptr};

  public:
    KeyboardButtonObserver(ViewportPanelContext* context) : context_(context){};

    void handle(const Event& event)
    {
        auto action = static_cast<const KeyboardButtonEvent&>(event).action();
        auto button = static_cast<const KeyboardButtonEvent&>(event).button();

        if (event.type() == KeyboardButtonEvent::descriptor && action != Input::Action::RELEASED)
        {
            switch (button)
            {
            case Input::Keyboard::Button::UP:
                context_->camera_translation.y -= 0.05f;
                break;
            case Input::Keyboard::Button::DOWN:
                context_->camera_translation.y += 0.05f;
                break;
            case Input::Keyboard::Button::RIGHT:
                context_->camera_translation.x -= 0.05f;
                break;
            case Input::Keyboard::Button::LEFT:
                context_->camera_translation.x += 0.05f;
                break;

            default:
                break;
            }
        }
    }
};

class MouseCursorEventObserver
{
  private:
    ViewportPanelContext* context_{nullptr};

  public:
    MouseCursorEventObserver(ViewportPanelContext* context) : context_(context){};

    void handle(const Event& event)
    {
        auto [x, y] = static_cast<const MouseCursorEvent&>(event).position();

        if (event.type() == MouseCursorEvent::descriptor)
        {
            // context_->camera_translation.x = 0.001 * x;
            // context_->camera_translation.y = 0.001 * y;
        }
    }
};
class ScrollInputEventObserver
{
  private:
    ViewportPanelContext* context_{nullptr};

  public:
    ScrollInputEventObserver(ViewportPanelContext* context) : context_(context){};

    void handle(const Event& event)
    {
        auto [x, y] = static_cast<const ScrollInputEvent&>(event).offset();

        if (event.type() == ScrollInputEvent::descriptor)
        {
            context_->camera.set_orthographic_size(context_->camera.orthographic_size() + (-1 * y));
        }
    }
};

class MouseButtonObserver
{
  private:
    ViewportPanelContext* context_{nullptr};

  public:
    MouseButtonObserver(ViewportPanelContext* context) : context_(context){};

    void handle(const Event& event)
    {
        auto action = static_cast<const MouseButtonEvent&>(event).action();
        auto button = static_cast<const MouseButtonEvent&>(event).button();

        if (event.type() == MouseButtonEvent::descriptor && action != Input::Action::RELEASED)
        {
            switch (button)
            {
            case Input::Mouse::Button::LEFT:
                context_->camera.set_orthographic_size(context_->camera.orthographic_size() + 0.05f);
                break;
            case Input::Mouse::Button::RIGHT:
                context_->camera.set_orthographic_size(context_->camera.orthographic_size() - 0.05f);
                break;

            default:
                break;
            }
        }
    }
};

} // namespace Konto::Editor

#endif // __KONTO_EDITOR_PANEL_VIEWPORT_H__
