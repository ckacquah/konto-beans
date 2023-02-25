#include "simulation.h"

namespace Konto::Editor
{

SimulationPanelContext SimulationPanel::context_{};

void SimulationPanel::stop()
{
}

void SimulationPanel::play()
{
    context_.scene_active = context_.scene->clone();
}

void SimulationPanel::pause()
{
}

void SimulationPanel::update()
{
    context_.framebuffer->bind();

    Knt::Renderer::set_clear_color(glm::vec4(1.0f));
    Knt::Renderer::clear();

    context_.scene_active->update();
    context_.framebuffer->clear_attachment(1, -1);
    context_.framebuffer->unbind();
}

void SimulationPanel::render()
{
    SimulationPanel::update();
    ImGui::Begin("Simulation", nullptr, ImGuiWindowFlags_MenuBar);
    {
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::Button("Play"))
            {
                SimulationPanel::play();
            }
            if (ImGui::Button("Stop"))
            {
            }
            ImGui::EndMenuBar();
        }

        ImGui::BeginChild("Simulation Viewport");
        {
            ImGui::Image(reinterpret_cast<void*>(context_.framebuffer->color_attachment()), ImGui::GetWindowSize(),
                         ImVec2{0, 1}, ImVec2{1, 0});
        }
        ImGui::EndChild();
    }
    ImGui::End();
}

void SimulationPanel::resize(uint32_t width, uint32_t height)
{
    context_.width = width;
    context_.height = height;
    context_.scene_active->resize(context_.width, context_.height);
}

void SimulationPanel::init(const std::shared_ptr<Scene>& scene, uint32_t width, uint32_t height)
{
    context_.scene = scene;
    context_.scene_active = context_.scene->clone();
    resize(width, height);

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

} // namespace Konto::Editor
