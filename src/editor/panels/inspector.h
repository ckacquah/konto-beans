#ifndef __KONTO_INSPECTOR_PANEL_SCENE_H__
#define __KONTO_INSPECTOR_PANEL_SCENE_H__

#include <memory>
#include <string>

#include <imgui/imgui.h>

#include "konto.h"

namespace Konto::Editor
{

struct InspectorPanelContext
{
    Entity entity{};

    InspectorPanelContext() = default;
    InspectorPanelContext(const InspectorPanelContext& other) = default;
};

class InspectorPanel
{
  private:
    static InspectorPanelContext context_;

    static void render_add_component();
    template <typename T> static void render_add_menu_item(const std::string& name);

    template <typename T> static void render(T& component);
    template <typename T> static void render(const std::string& title, bool toggle = true);
    template <typename T> static void render_settings(const std::string& title, T& component);

    template <> void render<TagComponent>(TagComponent& component);
    template <> void render<CameraComponent>(CameraComponent& component);
    template <> void render<TransformComponent>(TransformComponent& component);
    template <> void render<SpriteRendererComponent>(SpriteRendererComponent& component);
    template <> void render<CircleRendererComponent>(CircleRendererComponent& component);

  public:
    static void render();
    static void init(const Entity& entity);
};

} // namespace Konto::Editor

#endif // __KONTO_INSPECTOR_PANEL_SCENE_H__