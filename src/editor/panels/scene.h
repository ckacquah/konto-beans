#ifndef __KONTO_EDITOR_PANEL_SCENE_H__
#define __KONTO_EDITOR_PANEL_SCENE_H__

#include <memory>

#include <imgui/imgui.h>

#include "konto.h"

namespace Konto::Editor
{

struct ScenePanelContext
{
    Entity selected_entity{};
    std::shared_ptr<Scene> scene{};

    ScenePanelContext() = default;
    ScenePanelContext(const ScenePanelContext& other) = default;
};

class ScenePanel
{
  private:
    static ScenePanelContext context_;

    static void render_entities();
    static void render_properties();
    static void render_entity(Entity entity);

  public:
    static void render();
    static void init(const std::shared_ptr<Scene>& scene);
};

} // namespace Konto::Editor

#endif // __KONTO_EDITOR_PANEL_SCENE_H__
