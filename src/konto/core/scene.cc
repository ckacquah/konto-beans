#include <memory>

#include <box2d/box2d.h>
#include <imgui/imgui.h>

#include "konto/components/common.h"
#include "konto/components/physics.h"
#include "konto/components/renderer2d.h"
#include "konto/core/entity.h"
#include "konto/core/scene.h"
#include "konto/core/uuid.h"

namespace Konto
{

void Scene::start()
{
    world_ = new b2World(b2Vec2(0.0f, -10.0f));
    {
        auto view = registry_.view<TransformComponent, RigidBody2DComponent>();
        for (auto entity : view)
        {
            auto [transform, rigid_body] = view.get<TransformComponent, RigidBody2DComponent>(entity);
            rigid_body.definition.angle = transform.rotation.z;
            rigid_body.definition.enabled = rigid_body.enabled;
            rigid_body.definition.position.Set(transform.translation.x, transform.translation.y);
            rigid_body.body = world_->CreateBody(&rigid_body.definition);
        }
    }
    {
        auto view = registry_.view<RigidBody2DComponent, BoxCollider2DComponent>();
        for (auto entity : view)
        {
            auto& rigid_body = view.get<RigidBody2DComponent>(entity);
            auto& box_collider = view.get<BoxCollider2DComponent>(entity);
            box_collider.shape.SetAsBox(box_collider.size.x / 2, box_collider.size.y / 2);
            box_collider.fixture.shape = &box_collider.shape;
            rigid_body.body->CreateFixture(&box_collider.fixture);
        }
    }
    {
        auto view = registry_.view<RigidBody2DComponent, CircleCollider2DComponent>();
        for (auto entity : view)
        {
            auto& rigid_body = view.get<RigidBody2DComponent>(entity);
            auto& circle_collider = view.get<CircleCollider2DComponent>(entity);
            circle_collider.shape.m_radius = circle_collider.radius;
            circle_collider.fixture.shape = &circle_collider.shape;
            rigid_body.body->CreateFixture(&circle_collider.fixture);
        }
    }
}

void Scene::step(float delta)
{
    world_->Step(1.0f / 60.0f, velocity_iterations_, position_iterations_);
    auto view = registry_.view<TransformComponent, RigidBody2DComponent>();
    for (auto entity : view)
    {
        auto& transform = view.get<TransformComponent>(entity);
        auto& rigid_body = view.get<RigidBody2DComponent>(entity);
        transform.rotation.z = rigid_body.body->GetAngle();
        transform.translation.x = rigid_body.body->GetPosition().x;
        transform.translation.y = rigid_body.body->GetPosition().y;
    }
}

template <typename... Component>
void Scene::copy(entt::registry& source, entt::registry& destination,
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

    copy<TransformComponent, SpriteRendererComponent, CircleRendererComponent, CameraComponent, RigidBody2DComponent,
         BoxCollider2DComponent, CircleCollider2DComponent>(registry_, scene->registry_, scene->entities_);

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
                circle.texture == nullptr
                    ? Knt::Renderer2D::draw_circle(transform.transform(), circle.color, circle.thickness, circle.fade)
                    : Knt::Renderer2D::draw_circle(transform.transform(), circle.texture, circle.color,
                                                   circle.thickness, circle.fade);
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
    step(timestep_.delta());
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
