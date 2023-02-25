#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

#include "inspector.h"
#include "scene.h"

namespace Konto::Editor
{

ScenePanelContext ScenePanel::context_{};

void ScenePanel::render()
{
    ScenePanel::render_entities();
    InspectorPanel::render();
}

void ScenePanel::init(const std::shared_ptr<Scene>& scene)
{
    context_.scene = scene;
    context_.selected_entity = Entity();
}

void ScenePanel::render_entities()
{
    ImGui::Begin("Scene Hierarchy");
    {
        context_.scene->foreach ([&](Entity entity) {
            if (entity)
            {
                ScenePanel::render_entity(entity);
            }
        });
    }
    ImGui::End();
}

void ScenePanel::render_entity(Entity entity)
{
    auto component = entity.get<TagComponent>();
    if (ImGui::TreeNode(component.tag == "" ? UNTITLED_ENTITY : component.tag.c_str()))
    {
        if (ImGui::IsItemClicked())
        {
            context_.selected_entity = entity;
            InspectorPanel::init(entity);
        }
        ImGui::TreePop();
    }
}

} // namespace Konto::Editor
