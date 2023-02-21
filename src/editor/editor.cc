#include <kontomire.h>

#include "editor.h"
#include "konto.h"

using namespace Konto;
using namespace Konto::Editor;

int main()
{
    Window::start("Konto Editor", 800, 600);

    auto scene{std::make_shared<Scene>()};

    auto quad = scene->create_entity("Quad Entity");
    auto& quad_sprite = quad.add<SpriteRendererComponent>();
    quad_sprite.color = glm::vec4(0.5f, 1.0f, 0.2f, 1.0f);
    quad_sprite.texture = Knt::Texture2D::load("assets/textures/texture.jpg", "basic-texture");

    auto circle = scene->create_entity("Circle Entity");
    auto& circle_sprite = circle.add<CircleRendererComponent>();
    circle_sprite.color = glm::vec4(0.5f, 0.0f, 0.5f, 1.0f);

    ScenePanel::init(scene);
    ViewportPanel::init(scene, 800, 600);

    while (!Window::is_closed())
    {
        Window::begin();

        MainMenu::render();
        ScenePanel::render();
        ViewportPanel::render();

        Window::end();
    }

    Window::destroy();
    return 0;
}