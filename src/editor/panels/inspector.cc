#include "inspector.h"
#include "editor/menus/dialogs.h"

#include <kontomire.h>

namespace Konto::Editor
{

InspectorPanelContext InspectorPanel::context_{};

static const ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed |
                                        ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap |
                                        ImGuiTreeNodeFlags_FramePadding;

void InspectorPanel::init(const std::shared_ptr<EditorContext>& editor)
{
    context_.editor = editor;
}

void InspectorPanel::render()
{
    ImGui::Begin("Inspector");
    {
        if (context_.editor->active_entity)
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
    if (!context_.editor->active_entity.has<T>() && ImGui::MenuItem(name.c_str()))
    {
        context_.editor->active_entity.add<T>();
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
            context_.editor->active_entity.remove<T>();
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
    if (context_.editor->active_entity.has<T>() && ImGui::TreeNodeEx(title.c_str(), flags))
    {
        auto& component = context_.editor->active_entity.get<T>();
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
    ImGui::DragFloat3("Scale", glm::value_ptr(component.scale), 0.1f, 0.0f, 0.0f, "%.2f");

    glm::vec3 rotation = glm::degrees(component.rotation);
    if (ImGui::DragFloat3("Rotation", glm::value_ptr(rotation), 1.0f, -180.0f, 180.0f, "%.2f"))
    {
        component.rotation = glm::radians(rotation);
    }

    ImGui::DragFloat3("Translation", glm::value_ptr(component.translation), 0.05f, 0.0f, 0.0f, "%.2f");
}

template <> void InspectorPanel::render<CameraComponent>(CameraComponent& component)
{
    static float perspective_far{component.camera.perspective_far()};
    static float perspective_near{component.camera.perspective_near()};
    static float perspective_fov{component.camera.perspective_fov()};

    static float orthographic_far{component.camera.orthographic_far()};
    static float orthographic_near{component.camera.orthographic_near()};
    static float orthographic_size{component.camera.orthographic_size()};

    static float aspect_ratio{component.camera.aspect_ratio()};

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

    if (component.camera.is_perspective())
    {
        if (ImGui::DragFloat("Far", &perspective_far, 0.05, 0.0f, 0.0f, "%.2f"))
        {
            component.camera.set_perspective_far(perspective_far);
        }
        if (ImGui::DragFloat("Near", &perspective_near, 0.05, 0.0f, 0.0f, "%.2f"))
        {
            component.camera.set_perspective_near(perspective_near);
        }
        if (ImGui::DragFloat("Field Of View", &perspective_fov, 0.5f, 0.0f, 0.0f, "%.1f"))
        {
            component.camera.set_perspective_fov(perspective_fov);
        }
    }
    else
    {
        if (ImGui::DragFloat("Far", &orthographic_far, 0.05, 0.0f, 0.0f, "%.2f"))
        {
            component.camera.set_orthographic_far(orthographic_far);
        }
        if (ImGui::DragFloat("Near", &orthographic_near, 0.05, 0.0f, 0.0f, "%.2f"))
        {
            component.camera.set_orthographic_near(orthographic_near);
        }
        if (ImGui::DragFloat("Orthographic Size", &orthographic_size, 0.5f, 0.0f, 0.0f, "%.1f"))
        {
            component.camera.set_orthographic_size(orthographic_size);
        }
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
    ImGui::TextDisabled("%s", component.texture_path.c_str());
    if (ImGui::Button("Select texture image"))
    {
        component.texture_path = FileDialog::open("", {{"Texture Images", "png,jpg,JPEG,PNG,jpg,jpeg"}});
        component.texture = Knt::Texture2D::load(component.texture_path, "SquareTexture");
    }
}

template <> void InspectorPanel::render<CircleRendererComponent>(CircleRendererComponent& component)
{
    ImGui::DragFloat("Fade", &component.fade, 0.005f, 0.0f, 0.0f, "%.5f");
    ImGui::DragFloat("Thickness", &component.thickness, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::ColorEdit3("Color", glm::value_ptr(component.color));
    ImGui::TextDisabled("%s", component.texture_path.c_str());
    if (ImGui::Button("Select texture image"))
    {
        component.texture_path = FileDialog::open("", {{"Texture Images", "png,jpg,JPEG,PNG,jpg,jpeg"}});
        component.texture = Knt::Texture2D::load(component.texture_path, "CircleTexture");
    }
}

} // namespace Konto::Editor