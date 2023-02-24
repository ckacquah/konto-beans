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

    auto scene{std::make_shared<Scene>()};

    auto quad = scene->create("Quad Entity");
    auto& quad_sprite = quad.add<SpriteRendererComponent>();
    quad_sprite.color = glm::vec4(0.5f, 1.0f, 0.2f, 1.0f);
    quad_sprite.texture = Knt::Texture2D::load("assets/textures/texture.jpg", "basic-texture");

    auto circle = scene->create("Circle Entity");
    auto& circle_sprite = circle.add<CircleRendererComponent>();
    circle_sprite.color = glm::vec4(0.5f, 0.0f, 0.5f, 1.0f);

    auto camera = scene->create("Camera Entity");
    camera.add<CameraComponent>();

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

    Window::destroy();
    return 0;
}