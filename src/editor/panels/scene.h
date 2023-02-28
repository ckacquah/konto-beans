#ifndef __KONTO_EDITOR_PANEL_SCENE_H__
#define __KONTO_EDITOR_PANEL_SCENE_H__

#include <memory>

#include <imgui/imgui.h>

#include "editor/context.h"
#include "konto.h"

namespace Konto::Editor
{

struct ScenePanelContext
{
    std::shared_ptr<EditorContext> editor{};

    ScenePanelContext() = default;
    ScenePanelContext(const ScenePanelContext& other) = default;
};

class ScenePanel
{
  private:
    static ScenePanelContext context_;

    static void render_entities();
    static void render_entity(Entity entity);

  public:
    static void render();
    static void init(const std::shared_ptr<EditorContext>& editor_context);
};

} // namespace Konto::Editor

#endif // __KONTO_EDITOR_PANEL_SCENE_H__
