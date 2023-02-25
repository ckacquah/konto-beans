#ifndef __KONTO_EDITOR_PANEL_SIMULATION_H__
#define __KONTO_EDITOR_PANEL_SIMULATION_H__

#include <memory>

#include <imgui/imgui.h>

#include "konto.h"

namespace Konto::Editor
{

struct SimulationPanelContext
{
    std::shared_ptr<Scene> scene{};
    std::shared_ptr<Scene> scene_active{};
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
    static void init(const std::shared_ptr<Scene>& scene, uint32_t width, uint32_t height);
};

} // namespace Konto::Editor

#endif // __KONTO_EDITOR_PANEL_SIMULATION_H__
