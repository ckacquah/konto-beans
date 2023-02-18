#include <memory>

#include <imgui/imgui.h>

#include "konto.h"
#include "konto/components/common.h"
#include "konto/core/scene.h"

namespace Konto
{

Scene::Scene() : camera_(SceneCamera())
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
    auto view = registry_.view<TransformComponent, CameraComponent>();
    for (auto entity : view)
    {
        auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

        if (camera.primary)
        {
            Knt::Renderer2D::begin(transform.transform() * camera.camera.projection());
            Knt::Renderer2D::draw_quad(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec2(1.0f), glm::vec4(1.0f));
            Knt::Renderer2D::end();
            break;
        }
    }
}

void Scene::update(float timestep, const std::shared_ptr<SceneCamera>& camera)
{
    render_scene(camera);
}

void Scene::destroy_entity(Entity entity)
{
    registry_.destroy(entity);
}

Entity Scene::create_entity(const std::string& name)
{
    Entity entity = {registry_.create(), std::shared_ptr<Scene>(this)};
    entity.add<TransformComponent>();
    auto& tag = entity.add<TagComponent>();
    tag.tag = name.empty() ? "Entity" : name;
    return entity;
}

void Scene::resize_viewport(uint32_t width, uint32_t height)
{
    camera_.set_viewport_size(width, height);
}

void Scene::render_scene(const std::shared_ptr<SceneCamera>& camera)
{
    Knt::Renderer2D::begin(camera->projection());
    Knt::Renderer2D::draw_quad(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec2(1.0f), glm::vec4(1.0f));
    Knt::Renderer2D::end();
}

} // namespace Konto
