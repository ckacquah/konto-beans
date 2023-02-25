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
        if (ImGui::BeginPopupContextItem("Hierarchy Menu", ImGuiMouseButton_Right))
        {
            if (ImGui::MenuItem("New Entity"))
            {
                context_.scene->create("");
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Save Scene"))
            {
            }
            if (ImGui::MenuItem("Open Scene"))
            {
            }
            ImGui::EndPopup();
        }
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
    auto& tag = entity.get<TagComponent>();
    auto title = std::to_string(entity.get<UUIDComponent>().id);

    if (ImGui::TreeNode(tag.tag.empty() ? UNTITLED_ENTITY : tag.tag.c_str()))
    {
        if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
        {
            context_.selected_entity = entity;
            InspectorPanel::init(entity);
        }
        if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
        {
            ImGui::OpenPopupOnItemClick(title.c_str());
        }
        ImGui::TreePop();
    }
    if (ImGui::BeginPopupContextItem(title.c_str()))
    {
        if (ImGui::MenuItem("Delete"))
        {
            context_.scene->destroy(entity);
            context_.selected_entity = Entity();
            InspectorPanel::init(Entity());
            ImGui::CloseCurrentPopup();
        }
        if (ImGui::MenuItem("Edit"))
        {
            context_.selected_entity = entity;
            InspectorPanel::init(entity);
        }
        if (ImGui::MenuItem("Duplicate"))
        {
        }
        ImGui::EndPopup();
    }
}

} // namespace Konto::Editor
