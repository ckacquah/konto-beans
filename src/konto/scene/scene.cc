#include <imgui/imgui.h>

#include "konto/scene/scene.h"

namespace Konto
{

Scene::Scene() : camera_(Knt::Camera())
{
}

void Scene::stop()
{
}

void Scene::start()
{
}

void Scene::update(float timestep)
{
    auto camera = std::make_shared<Knt::Camera>(camera_);
    update(timestep, camera);
}

void Scene::update(float timestep, const std::shared_ptr<Knt::Camera>& camera)
{
    render_scene(camera);
}

void Scene::resize_viewport(uint32_t width, uint32_t height)
{
    camera_.set_aspect_ratio(static_cast<float>(width) / static_cast<float>(height));
}

void Scene::render_scene(const std::shared_ptr<Knt::Camera>& camera)
{
    Knt::Renderer2D::begin(camera);
    Knt::Renderer2D::draw_quad(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec2(1.0f), glm::vec4(1.0f));
    Knt::Renderer2D::end();
}

} // namespace Konto
