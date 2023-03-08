#ifndef __KONTO_EDITOR_PANEL_SIMULATION_H__
#define __KONTO_EDITOR_PANEL_SIMULATION_H__

#include <memory>

#include <imgui/imgui.h>

#include "editor/context.h"
#include "konto.h"

namespace Konto::Editor
{

enum SimulationState
{
    PLAYING,
    STOPPED,
    PAUSED,
};

struct SimulationPanelContext
{
    SimulationState state{SimulationState::STOPPED};

    std::shared_ptr<Scene> scene{};
    std::shared_ptr<EditorContext> editor{};
    std::shared_ptr<Knt::FrameBuffer> framebuffer{};

    SimulationPanelContext() = default;
    SimulationPanelContext(const SimulationPanelContext& other) = default;
};

class SimulationPanel
{
  private:
    static SimulationPanelContext context_;

  public:
    static void stop();
    static void play();
    static void pause();
    static void update();
    static void render();
    static void init(std::shared_ptr<EditorContext> editor);
};

} // namespace Konto::Editor

#endif // __KONTO_EDITOR_PANEL_SIMULATION_H__
