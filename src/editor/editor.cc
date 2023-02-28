#include <fstream>
#include <iostream>

#include <kontomire.h>

#include "editor.h"
#include "konto.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

using namespace Konto;
using namespace Konto::Editor;

int main()
{
    Window::start("Konto Editor", WINDOW_WIDTH, WINDOW_HEIGHT);

    auto context = std::make_shared<EditorContext>();
    context->width = WINDOW_WIDTH;
    context->height = WINDOW_HEIGHT;
    context->scene = std::make_shared<Scene>();

    MainMenu::init(context);
    ScenePanel::init(context);
    ViewportPanel::init(context);
    InspectorPanel::init(context);
    SimulationPanel::init(context);

    while (!Window::is_closed())
    {
        Window::begin();

        MainMenu::render();
        ScenePanel::render();
        ViewportPanel::render();
        InspectorPanel::render();
        SimulationPanel::render();

        Window::end();
    }

    Window::destroy();
    return 0;
}