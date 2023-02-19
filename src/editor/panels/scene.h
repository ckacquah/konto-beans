#ifndef __KONTO_EDITOR_PANEL_SCENE_H__
#define __KONTO_EDITOR_PANEL_SCENE_H__

#include <memory>

#include <imgui/imgui.h>

#include "konto.h"

namespace Konto::Editor
{

struct ScenePanelData
{
    Entity selected_entity{};
    std::shared_ptr<Scene> scene{};

    ScenePanelData() = default;
    ScenePanelData(const ScenePanelData& other) = default;
};

class ScenePanel
{
  private:
    static ScenePanelData context_;

    static void render_entities();
    static void render_properties();
    static void render_entity(Entity entity);

  public:
    static void render();
    static void init(const std::shared_ptr<Scene>& scene);
};

} // namespace Konto::Editor

#endif // __KONTO_EDITOR_PANEL_SCENE_H__
