#include "editor/panels/inspector.h"
#include "editor/menus/dialogs.h"
#include "konto.h"

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
            render<RigidBody2DComponent>("Rigid Body 2D");
            render<BoxCollider2DComponent>("Box Collider 2D");
            render<CircleCollider2DComponent>("Circle Collider 2D");

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
        render_add_menu_item<RigidBody2DComponent>("Rigid Body 2D");
        render_add_menu_item<BoxCollider2DComponent>("Box Collider 2D");
        render_add_menu_item<CircleCollider2DComponent>("Circle Collider 2D");
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
        render(component);
        if (toggle)
        {
            render_settings(title, component);
        }
        ImGui::TreePop();
    }
}

void InspectorPanel::render(TagComponent& component)
{
    char name[25]{};
    memcpy(name, component.tag.c_str(), 24);
    if (ImGui::InputText("Tag", name, 24))
    {
        component.tag = std::string(name);
    }
}

const char* body_types_name[] = {"Static", "Kinematic", "Dynamic"};

void InspectorPanel::render(RigidBody2DComponent& component)
{
    if (ImGui::BeginCombo("Body Type", body_types_name[component.definition.type]))
    {
        if (ImGui::Selectable("Static", component.definition.type == b2_staticBody))
        {
            component.definition.type = b2_staticBody;
        }
        if (ImGui::Selectable("Kinematic", component.definition.type == b2_kinematicBody))
        {
            component.definition.type = b2_kinematicBody;
        }
        if (ImGui::Selectable("Dynamic", component.definition.type == b2_dynamicBody))
        {
            component.definition.type = b2_dynamicBody;
        }
        ImGui::EndCombo();
    }
    ImGui::DragFloat("Angle", &component.definition.angle, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::DragFloat("Gravity Scale", &component.definition.gravityScale, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::DragFloat("Linear Damping", &component.definition.linearDamping, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::DragFloat("Anglular Damping", &component.definition.angularDamping, 0.1f, 0.0f, 0.0f, "%.2f");
}

void InspectorPanel::render(BoxCollider2DComponent& component)
{
    ImGui::DragFloat2("Size", glm::value_ptr(component.size), 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::DragFloat("Density", &component.fixture.density, 0.05f, 0.0f, 1.0f, "%.2f");
    ImGui::DragFloat("Friction", &component.fixture.friction, 0.05f, 0.0f, 1.0f, "%.2f");
    ImGui::DragFloat("Restitution", &component.fixture.restitution, 0.05f, 0.0f, 1.0f, "%.2f");
}

void InspectorPanel::render(CircleCollider2DComponent& component)
{
    ImGui::DragFloat("Raduis", &component.radius, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::DragFloat("Density", &component.fixture.density, 0.05f, 0.0f, 1.0f, "%.2f");
    ImGui::DragFloat("Friction", &component.fixture.friction, 0.05f, 0.0f, 1.0f, "%.2f");
    ImGui::DragFloat("Restitution", &component.fixture.restitution, 0.05f, 0.0f, 1.0f, "%.2f");
}

void InspectorPanel::render(TransformComponent& component)
{
    ImGui::DragFloat3("Scale", glm::value_ptr(component.scale), 0.1f, 0.0f, 0.0f, "%.2f");

    glm::vec3 rotation = glm::degrees(component.rotation);
    if (ImGui::DragFloat3("Rotation", glm::value_ptr(rotation), 1.0f, -180.0f, 180.0f, "%.2f"))
    {
        component.rotation = glm::radians(rotation);
    }

    ImGui::DragFloat3("Translation", glm::value_ptr(component.translation), 0.05f, 0.0f, 0.0f, "%.2f");
}

void InspectorPanel::render(CameraComponent& component)
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

void InspectorPanel::render(SpriteRendererComponent& component)
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

void InspectorPanel::render(CircleRendererComponent& component)
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