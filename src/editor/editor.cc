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

    std::string scene_path = FileDialog::open("", {{"Konto Scene File", "konto"}});

    if (!scene_path.empty())
    {
        std::ifstream example_file;
        example_file.open(scene_path, std::ios::binary | std::ios::in);
        example_file.seekg(0, std::ios::end);
        int length = example_file.tellg();
        example_file.seekg(0, std::ios::beg);
        char* data = new char[length];
        example_file.read(data, length);
        example_file.close();

        auto scene = SceneSerializer::deserialize((uint8_t*)data, length);

        ScenePanel::init(scene);
        ViewportPanel::init(scene, WINDOW_WIDTH, WINDOW_HEIGHT);
        SimulationPanel::init(scene, WINDOW_WIDTH, WINDOW_HEIGHT);

        while (!Window::is_closed())
        {
            Window::begin();

            MainMenu::render();
            ScenePanel::render();
            ViewportPanel::render();
            SimulationPanel::render();

            Window::end();
        }
    }

    Window::destroy();
    return 0;
}