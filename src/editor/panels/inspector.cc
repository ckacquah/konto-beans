#include "inspector.h"

namespace Konto::Editor
{

InspectorPanelContext InspectorPanel::context_{};

static const ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed |
                                        ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap |
                                        ImGuiTreeNodeFlags_FramePadding;

void InspectorPanel::init(const Entity& entity)
{
    context_.entity = entity;
}

void InspectorPanel::render()
{
    ImGui::Begin("Inspector");
    {
        if (context_.entity)
        {
            render<TagComponent>("Tag", false);
            render<TransformComponent>("Transform", false);
            render<CameraComponent>("Camera");
            render<SpriteRendererComponent>("Sprite Renderer");
            render<CircleRendererComponent>("Circle Renderer");

            render_add_component();
        }
    }
    ImGui::End();
}

void InspectorPanel::render_add_component()
{
    ImGui::Separator();
    if (ImGui::Button("Add Component"))
    {
        ImGui::OpenPopup("Add");
    }

    if (ImGui::BeginPopup("Add"))
    {
        render_add_menu_item<CameraComponent>("Camera");
        render_add_menu_item<SpriteRendererComponent>("Sprite Renderer");
        render_add_menu_item<CircleRendererComponent>("Circle Renderer");
        ImGui::EndPopup();
    }
}

template <typename T> void InspectorPanel::render_add_menu_item(const std::string& name)
{
    if (!context_.entity.has<T>() && ImGui::MenuItem(name.c_str()))
    {
        context_.entity.add<T>();
    }
}

template <typename T> void InspectorPanel::render_settings(const std::string& title, T& component)
{
    ImGui::Checkbox("Enable", &component.enabled);
    ImGui::SameLine();

    if (ImGui::Button("Delete"))
    {
        ImGui::OpenPopup("Delete?");
    }
    if (ImGui::BeginPopupModal("Delete?", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Do you want to remove the %s component?", title.c_str());
        ImGui::Separator();

        if (ImGui::Button("OK", ImVec2(120, 0)))
        {
            context_.entity.remove<T>();
            ImGui::CloseCurrentPopup();
        }

        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();

        if (ImGui::Button("Cancel", ImVec2(120, 0)))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

template <typename T> void InspectorPanel::render(const std::string& title, bool toggle)
{
    if (context_.entity.has<T>() && ImGui::TreeNodeEx(title.c_str(), flags))
    {
        auto& component = context_.entity.get<T>();
        render<T>(component);
        if (toggle)
        {
            render_settings(title, component);
        }
        ImGui::TreePop();
    }
}

template <> void InspectorPanel::render<TagComponent>(TagComponent& component)
{
    char name[25]{};
    memcpy(name, component.tag.c_str(), 24);
    if (ImGui::InputText("Tag", name, 24))
    {
        component.tag = std::string(name);
    }
}

template <> void InspectorPanel::render<TransformComponent>(TransformComponent& component)
{
    ImGui::DragFloat3("Scale", glm::value_ptr(component.scale), 0.1f, 0.0f, 5.0f, "%.2f");

    glm::vec3 rotation = glm::degrees(component.rotation);
    if (ImGui::DragFloat3("Rotation", glm::value_ptr(rotation), 1.0f, -180.0f, 180.0f, "%.2f"))
    {
        component.rotation = glm::radians(rotation);
    }

    ImGui::DragFloat3("Translation", glm::value_ptr(component.translation), 0.05f, 0.0f, 0.0f, "%.2f");
}

template <> void InspectorPanel::render<CameraComponent>(CameraComponent& component)
{
    if (ImGui::BeginCombo("Projection", component.camera.is_orthographic() ? "Orthographic" : "Perspective"))
    {
        if (ImGui::Selectable("Orthographic", component.camera.is_orthographic()))
        {
            component.camera.set_projection_type(SceneCamera::ProjectionType::ORTHOGRAPHIC);
        }
        if (ImGui::Selectable("Perspective", component.camera.is_perspective()))
        {
            component.camera.set_projection_type(SceneCamera::ProjectionType::PERSPECTIVE);
        }
        ImGui::EndCombo();
    }

    static float far{component.camera.far_clip()};
    static float near{component.camera.near_clip()};
    static float aspect_ratio{component.camera.aspect_ratio()};
    static float perspective_FOV{component.camera.perspective_FOV()};
    static float orthographic_size{component.camera.orthographic_size()};

    if (ImGui::DragFloat("Near", &near, 0.05, 0.0f, 0.0f, "%.2f"))
    {
        component.camera.set_near_clip(near);
    }
    if (ImGui::DragFloat("Far", &far, 0.05, 0.0f, 0.0f, "%.2f"))
    {
        component.camera.set_far_clip(far);
    }

    if (component.camera.is_perspective() &&
        ImGui::DragFloat("Field Of View", &perspective_FOV, 0.5f, 0.0f, 0.0f, "%.1f"))
    {
        component.camera.set_perspective_FOV(near);
    }
    else if (component.camera.is_perspective() &&
             ImGui::DragFloat("Orthographic Size", &orthographic_size, 0.5f, 0.0f, 0.0f, "%.1f"))
    {
        component.camera.set_orthographic_size(orthographic_size);
    }

    if (ImGui::Checkbox("Fixed Aspect Ratio", &component.camera.fixed_aspect_ratio))
    {
        component.camera.set_aspect_ratio(aspect_ratio);
    }
    if (ImGui::DragFloat("Aspect Ratio", &aspect_ratio, 0.05f, 0.0f, 0.0f, "%.1f"))
    {
        component.camera.set_aspect_ratio(aspect_ratio);
    }
}

template <> void InspectorPanel::render<SpriteRendererComponent>(SpriteRendererComponent& component)
{
    ImGui::DragFloat("Tiling Factor", &component.tiling_factor);
    ImGui::ColorEdit3("Color", glm::value_ptr(component.color));
}

template <> void InspectorPanel::render<CircleRendererComponent>(CircleRendererComponent& component)
{
    ImGui::DragFloat("Fade", &component.fade, 0.005f, 0.0f, 0.0f, "%.5f");
    ImGui::DragFloat("Thickness", &component.thickness, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::ColorEdit3("Color", glm::value_ptr(component.color));
}

} // namespace Konto::Editor