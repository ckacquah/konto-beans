#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

#include "konto.h"
#include "viewport.h"

namespace Konto::Editor
{

ViewportPanelContext ViewportPanel::context_{};

void ViewportPanel::render()
{
    context_.framebuffer->bind();

    Knt::Renderer::set_clear_color(context_.clear_color);
    Knt::Renderer::clear();

    context_.editor->scene->render(context_.camera.projection(), context_.camera_transform());
    context_.framebuffer->clear_attachment(1, -1);
    context_.framebuffer->unbind();

    ViewportPanel::render_viewport();
}

void ViewportPanel::init(std::shared_ptr<EditorContext> editor)
{
    context_.editor = editor;
    resize(editor->width, editor->height);

    Knt::FramebufferSpecification framebuffer_specs{};
    framebuffer_specs.width = editor->width;
    framebuffer_specs.height = editor->height;
    framebuffer_specs.attachments = {Knt::FramebufferTextureFormat::DEPTH, Knt::FramebufferTextureFormat::RGBA8,
                                     Knt::FramebufferTextureFormat::RED_INTEGER};

    context_.framebuffer = Knt::FrameBuffer::create(framebuffer_specs);

    auto library = std::make_shared<Knt::ShaderLibrary>();
    library->add("line", "assets/shaders/2D/line.glsl");
    library->add("quad", "assets/shaders/2D/quad.glsl");
    library->add("circle", "assets/shaders/2D/circle.glsl");

    Knt::Renderer::set_line_width(1.0f);
    Knt::Renderer2D::init(library);
}

void ViewportPanel::resize(uint32_t width, uint32_t height)
{
    context_.editor->scene->resize(width, height);
    context_.camera.set_viewport_size(width, height);
}

void ViewportPanel::render_viewport()
{
    ImGui::Begin("Viewport");
    {
        if (ImGui::BeginCombo("Projection", context_.camera.is_orthographic() ? "Orthographic" : "Perspective"))
        {
            if (ImGui::Selectable("Orthographic", context_.camera.is_orthographic()))
            {
                context_.camera.set_projection_type(SceneCamera::ProjectionType::ORTHOGRAPHIC);
            }
            if (ImGui::Selectable("Perspective", context_.camera.is_perspective()))
            {
                context_.camera.set_projection_type(SceneCamera::ProjectionType::PERSPECTIVE);
            }
            ImGui::EndCombo();
        }

        ImGui::BeginChild(context_.camera.is_orthographic() ? "Orthographic Viewport" : "Perspective Viewport");
        {
            if (ImGui::IsWindowFocused())
            {
                if (context_.editor->input.keyboard.is_pressed(Input::Keyboard::Button::UP))
                {
                    context_.camera_translation.y -= 0.05f;
                }

                if (context_.editor->input.keyboard.is_pressed(Input::Keyboard::Button::DOWN))
                {
                    context_.camera_translation.y += 0.05f;
                }

                if (context_.editor->input.keyboard.is_pressed(Input::Keyboard::Button::LEFT))
                {
                    context_.camera_translation.x += 0.05f;
                }

                if (context_.editor->input.keyboard.is_pressed(Input::Keyboard::Button::RIGHT))
                {
                    context_.camera_translation.x -= 0.05f;
                }
            }

            ImGui::Image(reinterpret_cast<void*>(context_.framebuffer->color_attachment()), ImGui::GetWindowSize(),
                         ImVec2{0, 1}, ImVec2{1, 0});
            resize(ImGui::GetWindowSize().y, ImGui::GetWindowSize().x);
        }
        ImGui::EndChild();
    }
    ImGui::End();
}

} // namespace Konto::Editor
