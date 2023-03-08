#include "simulation.h"

namespace Konto::Editor
{

SimulationPanelContext SimulationPanel::context_{};

void SimulationPanel::stop()
{
    if (context_.state != SimulationState::STOPPED)
    {
        context_.scene = context_.editor->scene->clone();
        context_.state = SimulationState::STOPPED;
    }
}

void SimulationPanel::play()
{
    switch (context_.state)
    {
    case SimulationState::STOPPED:
        context_.scene = context_.editor->scene->clone();
        context_.scene->start();
    case SimulationState::PAUSED:
        context_.state = SimulationState::PLAYING;
    default:
        break;
    }
}

void SimulationPanel::pause()
{
    context_.state = context_.state == SimulationState::PLAYING ? SimulationState::PAUSED : context_.state;
}

void SimulationPanel::update()
{
    context_.framebuffer->bind();

    Knt::Renderer::set_clear_color(glm::vec4(1.0f));
    Knt::Renderer::clear();

    context_.state == SimulationState::PLAYING ? context_.scene->update() : context_.scene->render_with_camera();

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
            if (ImGui::Button("Pause"))
            {
                SimulationPanel::pause();
            }
            if (ImGui::Button("Stop"))
            {
                SimulationPanel::stop();
            }
            ImGui::EndMenuBar();
        }

        ImGui::BeginChild("Simulation Viewport");
        {
            ImGui::Image(reinterpret_cast<void*>(context_.framebuffer->color_attachment()), ImGui::GetWindowSize(),
                         ImVec2{0, 1}, ImVec2{1, 0});
            context_.scene->resize(ImGui::GetWindowSize().y, ImGui::GetWindowSize().x);
        }
        ImGui::EndChild();
    }
    ImGui::End();
}

void SimulationPanel::init(std::shared_ptr<EditorContext> editor)
{
    context_.editor = editor;
    context_.scene = context_.editor->scene->clone();
    context_.scene->resize(editor->width, editor->height);

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

} // namespace Konto::Editor
