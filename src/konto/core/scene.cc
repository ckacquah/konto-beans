#include <memory>

#include <imgui/imgui.h>

#include "konto/components/common.h"
#include "konto/components/renderer2d.h"
#include "konto/core/entity.h"
#include "konto/core/scene.h"
#include "konto/core/uuid.h"

#define ALL_COMPONENTS TransformComponent, SpriteRendererComponent, CircleRendererComponent, CameraComponent

namespace Konto
{

template <typename... Component>
void Scene::clone(entt::registry& source, entt::registry& destination,
                  std::unordered_map<uint64_t, entt::entity>& entities)
{
    (
        [&]() {
            for (auto old_entity : source.view<Component>())
            {
                entt::entity new_entity{entities.at(source.get<UUIDComponent>(old_entity).id)};
                destination.emplace_or_replace<Component>(new_entity, source.get<Component>(old_entity));
            }
        }(),
        ...);
}

std::shared_ptr<Scene> Scene::clone()
{
    auto scene{std::make_shared<Scene>()};

    for (auto& old_entity : registry_.view<UUIDComponent>())
    {
        auto [tag_component, uuid_component] = registry_.get<TagComponent, UUIDComponent>(old_entity);
        auto new_entity = scene->create(tag_component.tag, uuid_component.id);
    }

    clone<ALL_COMPONENTS>(registry_, scene->registry_, scene->entities_);

    return scene;
}

void Scene::render()
{
    {
        auto view = registry_.view<TransformComponent, SpriteRendererComponent>();
        for (auto entity : view)
        {
            auto [transform, sprite] = view.get<TransformComponent, SpriteRendererComponent>(entity);
            if (sprite.enabled)
            {
                sprite.texture == nullptr
                    ? Knt::Renderer2D::draw_quad(transform.transform(), sprite.color)
                    : Knt::Renderer2D::draw_quad(transform.transform(), sprite.texture, sprite.color);
            }
        }
    }
    {
        auto view = registry_.view<TransformComponent, CircleRendererComponent>();
        for (auto entity : view)
        {
            auto [transform, circle] = view.get<TransformComponent, CircleRendererComponent>(entity);
            if (circle.enabled)
            {
                Knt::Renderer2D::draw_circle(transform.transform(), circle.color, circle.thickness, circle.fade);
            }
        }
    }

    Knt::Renderer2D::end();
}

void Scene::render(const glm::mat4& view, const glm::mat4& projection)
{
    Knt::Renderer2D::begin(projection * view);
    render();
}

void Scene::update()
{
    auto view = registry_.view<TransformComponent, CameraComponent>();
    for (auto entity : view)
    {
        auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
        if (camera.primary && camera.enabled)
        {
            render(transform.transform(), camera.camera.projection());
            break;
        }
    }
}

void Scene::destroy(Entity entity)
{
    registry_.destroy(entity);
}

Entity Scene::create(const std::string& name)
{
    return create(name, UUID::generate());
}

Entity Scene::create(const std::string& name, uint64_t uuid)
{
    Entity entity = {registry_.create(), this};

    entity.add<TransformComponent>();
    entity.add<UUIDComponent>(uuid);
    entity.add<TagComponent>(name.empty() ? UNTITLED_ENTITY : name);

    entities_[uuid] = entity;
    return entity;
}

void Scene::foreach (std::function<void(Entity)> callback)
{
    registry_.each([&](auto entity_id) { callback({entity_id, this}); });
}

void Scene::resize(uint32_t width, uint32_t height)
{
    auto view = registry_.view<TransformComponent, CameraComponent>();
    for (auto entity : view)
    {
        auto& component = view.get<CameraComponent>(entity);
        component.camera.set_viewport_size(width, height);
    }
}

} // namespace Konto
