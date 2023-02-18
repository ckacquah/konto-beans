#include <memory>

#include <imgui/imgui.h>

#include "konto.h"
#include "konto/components/common.h"
#include "konto/components/renderer2d.h"
#include "konto/core/scene.h"

namespace Konto
{

void Scene::update(float timestep)
{
    {
        auto view = registry_.view<TransformComponent, CameraComponent>();
        for (auto entity : view)
        {
            auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
            if (camera.primary)
            {
                Knt::Renderer2D::begin(transform.transform() * camera.camera.projection());
                break;
            }
        }
    }

    {
        auto view = registry_.view<TransformComponent, SpriteRendererComponent>();
        for (auto entity : view)
        {
            auto [transform, sprite] = view.get<TransformComponent, SpriteRendererComponent>(entity);
            Knt::Renderer2D::draw_quad(transform.transform(), sprite.texture, sprite.color);
        }
    }

    {
        auto view = registry_.view<TransformComponent, CircleRendererComponent>();
        for (auto entity : view)
        {
            auto [transform, circle] = view.get<TransformComponent, CircleRendererComponent>(entity);
            Knt::Renderer2D::draw_circle(transform.transform(), circle.color);
        }
    }

    Knt::Renderer2D::end();
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
    auto view = registry_.view<TransformComponent, CameraComponent>();
    for (auto entity : view)
    {
        auto& component = view.get<CameraComponent>(entity);
        component.camera.set_viewport_size(width, height);
    }
}

} // namespace Konto
