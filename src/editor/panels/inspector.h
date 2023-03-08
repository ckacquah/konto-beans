#ifndef __KONTO_INSPECTOR_PANEL_SCENE_H__
#define __KONTO_INSPECTOR_PANEL_SCENE_H__

#include <memory>
#include <string>

#include <imgui/imgui.h>

#include "editor/context.h"
#include "konto.h"

namespace Konto::Editor
{

struct InspectorPanelContext
{
    std::shared_ptr<EditorContext> editor{};

    InspectorPanelContext() = default;
    InspectorPanelContext(const InspectorPanelContext& other) = default;
};

class InspectorPanel
{
  private:
    static InspectorPanelContext context_;

    static void render_add_component();
    template <typename T> static void render_add_menu_item(const std::string& name);

    template <typename T> static void render(const std::string& title, bool toggle = true);
    template <typename T> static void render_settings(const std::string& title, T& component);

    static void render(TagComponent& component);
    static void render(CameraComponent& component);
    static void render(TransformComponent& component);
    static void render(SpriteRendererComponent& component);
    static void render(CircleRendererComponent& component);
    static void render(RigidBody2DComponent& component);
    static void render(BoxCollider2DComponent& component);
    static void render(CircleCollider2DComponent& component);

  public:
    static void render();
    static void init(std::shared_ptr<EditorContext> editor);
};

} // namespace Konto::Editor

#endif // __KONTO_INSPECTOR_PANEL_SCENE_H__