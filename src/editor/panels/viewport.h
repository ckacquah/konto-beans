#ifndef __KONTO_EDITOR_PANEL_VIEWPORT_H__
#define __KONTO_EDITOR_PANEL_VIEWPORT_H__

#include <memory>

#include <imgui/imgui.h>

#include "konto.h"

namespace Konto::Editor
{

struct ViewportPanelData
{
    float width{};
    float height{};

    SceneCamera camera{};
    std::shared_ptr<Scene> scene{};

    glm::vec3 camera_scale{1.0f};
    glm::vec3 camera_rotation{0.0f};
    glm::vec3 camera_translation{0.0f};

    glm::vec4 clear_color{0.5f, 0.0f, 1.0f, 1.0f};

    std::shared_ptr<Knt::FrameBuffer> framebuffer{};

    ViewportPanelData() = default;
    ViewportPanelData(const ViewportPanelData& other) = default;

    glm::mat4 camera_transform()
    {
        return glm::translate(glm::mat4(1.0f), camera_translation) * glm::toMat4(glm::quat(camera_rotation)) *
               glm::scale(glm::mat4(1.0f), camera_scale);
    }
};

class ViewportPanel
{
  private:
    static ViewportPanelData context_;

    static void render_viewport();

  public:
    static void render();
    static void resize_viewport(uint32_t width, uint32_t height);
    static void init(std::shared_ptr<Scene> scene, uint32_t width, uint32_t height);

    static ViewportPanelData& viewport_data()
    {
        return context_;
    }
};

} // namespace Konto::Editor

#endif // __KONTO_EDITOR_PANEL_VIEWPORT_H__
