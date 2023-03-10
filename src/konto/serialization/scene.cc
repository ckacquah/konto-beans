#include <iostream>
#include <vector>

#include "konto/serialization/serialization.h"

namespace Konto
{

flatbuffers::Offset<Serializable::Scene> SceneSerializer::convert(flatbuffers::FlatBufferBuilder& buffer_builder,
                                                                  Scene& scene)
{
    std::vector<flatbuffers::Offset<Serializable::Entity>> entities;
    scene.foreach ([&](auto entity) { entities.push_back(convert(buffer_builder, entity)); });
    auto scene_ = Serializable::CreateSceneDirect(buffer_builder, "", &entities);
    buffer_builder.Finish(scene_);
    return scene_;
}

flatbuffers::Offset<Serializable::Entity> SceneSerializer::convert(flatbuffers::FlatBufferBuilder& buffer_builder,
                                                                   Entity& entity)
{
    auto id = entity.get<UUIDComponent>().id;
    auto tag = entity.get<TagComponent>().tag.c_str();

    std::vector<uint8_t> components_type;
    std::vector<flatbuffers::Offset<void>> components;

    if (entity.has<TransformComponent>())
    {
        auto component = convert(entity.get<TransformComponent>());
        components_type.push_back(Serializable::Component_Transform);
        components.push_back(buffer_builder.CreateStruct(component).Union());
    }
    if (entity.has<CameraComponent>())
    {
        auto component = convert(entity.get<CameraComponent>());
        components_type.push_back(Serializable::Component_Camera);
        components.push_back(buffer_builder.CreateStruct(component).Union());
    }
    if (entity.has<SpriteRendererComponent>())
    {
        auto component = convert(buffer_builder, entity.get<SpriteRendererComponent>());
        components_type.push_back(Serializable::Component_SpriteRenderer);
        components.push_back(component.Union());
    }
    if (entity.has<CircleRendererComponent>())
    {
        auto component = convert(buffer_builder, entity.get<CircleRendererComponent>());
        components_type.push_back(Serializable::Component_CircleRenderer);
        components.push_back(component.Union());
    }
    if (entity.has<RigidBody2DComponent>())
    {
        auto component = convert(entity.get<RigidBody2DComponent>());
        components_type.push_back(Serializable::Component_RigidBody2D);
        components.push_back(buffer_builder.CreateStruct(component).Union());
    }
    if (entity.has<BoxCollider2DComponent>())
    {
        auto component = convert(entity.get<BoxCollider2DComponent>());
        components_type.push_back(Serializable::Component_BoxCollider2D);
        components.push_back(buffer_builder.CreateStruct(component).Union());
    }
    if (entity.has<CircleCollider2DComponent>())
    {
        auto component = convert(entity.get<CircleCollider2DComponent>());
        components_type.push_back(Serializable::Component_CircleCollider2D);
        components.push_back(buffer_builder.CreateStruct(component).Union());
    }
    return Serializable::CreateEntityDirect(buffer_builder, id, tag, &components_type, &components);
}

Scene SceneSerializer::convert(const Serializable::Scene& scene)
{
    Scene _scene;
    for (const auto entity : *scene.entities())
    {
        convert(*entity, _scene);
    }
    return _scene;
}

Entity SceneSerializer::convert(const Serializable::Entity& entity, Scene& scene)
{
    auto _entity = scene.create(entity.name()->c_str(), entity.id());
    auto components = entity.components();
    auto components_type = entity.components_type();
    for (int i = 0; i < components->size(); ++i)
    {
        switch ((*components_type)[i])
        {
        case Serializable::Component_Camera: {
            auto camera = static_cast<const Serializable::Camera*>((*components)[i]);
            auto& component = _entity.add<CameraComponent>();
            component = convert(*camera);
            break;
        }
        case Serializable::Component_Transform: {
            auto transform = static_cast<const Serializable::Transform*>((*components)[i]);
            auto& component = _entity.get<TransformComponent>();
            component = convert(*transform);
            break;
        }
        case Serializable::Component_SpriteRenderer: {
            auto sprite = static_cast<const Serializable::SpriteRenderer*>((*components)[i]);
            auto& component = _entity.add<SpriteRendererComponent>();
            component = convert(*sprite);
            break;
        }
        case Serializable::Component_CircleRenderer: {
            auto circle = static_cast<const Serializable::CircleRenderer*>((*components)[i]);
            auto& component = _entity.add<CircleRendererComponent>();
            component = convert(*circle);
            break;
        }
        case Serializable::Component_RigidBody2D: {
            auto rigid_body = static_cast<const Serializable::RigidBody2D*>((*components)[i]);
            auto& component = _entity.add<RigidBody2DComponent>();
            component = convert(*rigid_body);
            break;
        }
        case Serializable::Component_BoxCollider2D: {
            auto box_collider = static_cast<const Serializable::BoxCollider2D*>((*components)[i]);
            auto& component = _entity.add<BoxCollider2DComponent>();
            component = convert(*box_collider);
            break;
        }
        case Serializable::Component_CircleCollider2D: {
            auto circle_collider = static_cast<const Serializable::CircleCollider2D*>((*components)[i]);
            auto& component = _entity.add<CircleCollider2DComponent>();
            component = convert(*circle_collider);
            break;
        }
        default:
            std::cerr << "Component type not supported" << std::endl;
            exit(1);
        }
    }
    return _entity;
}

} // namespace Konto
