#include <memory>

#include <kontomire.h>

#include "editor.h"
#include "konto.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

using namespace Konto;
using namespace Konto::Editor;

int main()
{
    auto app{std::make_unique<Application>()};
    app->start("Konto Editor", WINDOW_WIDTH, WINDOW_HEIGHT);

    auto context = app->context();

    MainMenu::init(context);
    ScenePanel::init(context);
    ViewportPanel::init(context);
    InspectorPanel::init(context);
    SimulationPanel::init(context);

    while (!app->closed())
    {
        app->begin_frame();

        MainMenu::render();
        ScenePanel::render();
        ViewportPanel::render();
        InspectorPanel::render();
        SimulationPanel::render();

        app->end_frame();
    }

    return 0;
}