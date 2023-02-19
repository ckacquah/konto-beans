#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

#include "scene.h"

namespace Konto::Editor
{

ScenePanelData ScenePanel::context_{};

void ScenePanel::render()
{
    ScenePanel::render_entities();
    ScenePanel::render_properties();
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
        context_.scene->foreach_entity([&](Entity entity) {
            if (entity)
            {
                ScenePanel::render_entity(entity);
            }
        });
    }
    ImGui::End();
}

void ScenePanel::render_properties()
{
    const ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed |
                                     ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap |
                                     ImGuiTreeNodeFlags_FramePadding;

    ImGui::Begin("Properties");
    {
        if (context_.selected_entity)
        {
            {
                auto& component = context_.selected_entity.get<TagComponent>();
                if (ImGui::TreeNodeEx("Tag", flags))
                {
                    char name[25]{};
                    memcpy(name, component.tag.c_str(), 24);
                    if (ImGui::InputText("Tag", name, 24))
                    {
                        component.tag = std::string(name);
                    }
                    ImGui::TreePop();
                }
            }
            if (context_.selected_entity.has<TransformComponent>())
            {
                auto& component = context_.selected_entity.get<TransformComponent>();
                if (ImGui::TreeNodeEx("Transform", flags))
                {
                    ImGui::DragFloat3("Scale", glm::value_ptr(component.scale), 0.1f, 0.0f, 5.0f, "%.2f");

                    glm::vec3 rotation = glm::degrees(component.rotation);
                    if (ImGui::DragFloat3("Rotation", glm::value_ptr(rotation), 1.0f, -180.0f, 180.0f, "%.2f"))
                    {
                        component.rotation = glm::radians(rotation);
                    }

                    ImGui::DragFloat3("Translation", glm::value_ptr(component.translation), 0.05f, 0.0f, 0.0f, "%.2f");
                    ImGui::TreePop();
                }
            }
            if (context_.selected_entity.has<SpriteRendererComponent>())
            {
                auto& component = context_.selected_entity.get<SpriteRendererComponent>();
                if (ImGui::TreeNodeEx("Sprite Renderer", flags))
                {
                    ImGui::DragFloat("Tiling Factor", &component.tiling_factor);
                    ImGui::ColorEdit3("Color", glm::value_ptr(component.color));
                    ImGui::TreePop();
                }
            }
            if (context_.selected_entity.has<CircleRendererComponent>())
            {
                auto& component = context_.selected_entity.get<CircleRendererComponent>();
                if (ImGui::TreeNodeEx("Circle Renderer", flags))
                {
                    ImGui::DragFloat("Fade", &component.fade, 0.005f, 0.0f, 0.0f, "%.5f");
                    ImGui::DragFloat("Thickness", &component.thickness, 0.1f, 0.0f, 0.0f, "%.2f");
                    ImGui::ColorEdit3("Color", glm::value_ptr(component.color));
                    ImGui::TreePop();
                }
            }
        }
    }
    ImGui::End();
}

void ScenePanel::render_entity(Entity entity)
{
    auto component = entity.get<TagComponent>();
    if (ImGui::TreeNode(component.tag == "" ? "Unamed Entity" : component.tag.c_str()))
    {
        if (ImGui::IsItemClicked())
        {
            context_.selected_entity = entity;
        }
        ImGui::TreePop();
    }
}

} // namespace Konto::Editor
