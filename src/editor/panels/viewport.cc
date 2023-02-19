#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

#include "konto.h"
#include "viewport.h"

namespace Konto::Editor
{

ViewportPanelData ViewportPanel::context_{};

void ViewportPanel::render()
{
    context_.scene->resize_viewport(context_.width, context_.height);
    context_.framebuffer->bind();

    Knt::Renderer::set_clear_color(context_.clear_color);
    Knt::Renderer::clear();

    context_.scene->update(context_.camera, context_.camera_transform());
    context_.framebuffer->clear_attachment(1, -1);
    context_.framebuffer->unbind();

    ViewportPanel::render_viewport();
}

void ViewportPanel::init(std::shared_ptr<Scene> scene, uint32_t width, uint32_t height)
{
    context_.scene = scene;
    resize_viewport(width, height);

    Knt::FramebufferSpecification framebuffer_specs{};
    framebuffer_specs.width = width;
    framebuffer_specs.height = height;
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

void ViewportPanel::resize_viewport(uint32_t width, uint32_t height)
{
    context_.width = width;
    context_.height = height;
    context_.camera.set_viewport_size(width, height);
}

void ViewportPanel::render_viewport()
{
    if (ImGui::Begin("Editor Viewport"))
    {
        if (ImGui::BeginCombo("Camera", context_.camera.projection_type() == SceneCamera::ProjectionType::ORTHOGRAPHIC
                                            ? "Orthographic"
                                            : "Perspective"))
        {
            ImGui::PushID((void*)&context_.camera);
            if (ImGui::Selectable("Orthographic"))
            {
                context_.camera.set_projection_type(SceneCamera::ProjectionType::ORTHOGRAPHIC);
                context_.scene->update(context_.camera, context_.camera_transform());
            }
            if (ImGui::Selectable("Perspective"))
            {
                context_.camera.set_projection_type(SceneCamera::ProjectionType::PERSPECTIVE);
                context_.scene->update(context_.camera, context_.camera_transform());
            }
            ImGui::PopID();
            ImGui::EndCombo();
        }
        if (ImGui::BeginChild("Viewport"))
        {
            ImGui::Image(reinterpret_cast<void*>(context_.framebuffer->color_attachment()), ImGui::GetWindowSize(),
                         ImVec2{0, 1}, ImVec2{1, 0});
            ImGui::EndChild();
        }
        ImGui::End();
    }
}

} // namespace Konto::Editor
