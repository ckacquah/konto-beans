#include <memory>

#include <kontomire.h>

#include "konto/core/camera.h"
#include "konto/serialization/serialization.h"

namespace Konto
{

Serializable::Camera SceneSerializer::convert(const CameraComponent& component)
{
    return {component.enabled,
            component.primary,
            component.camera.fixed_aspect_ratio,
            component.camera.aspect_ratio(),
            component.camera.perspective_far(),
            component.camera.perspective_near(),
            component.camera.perspective_fov(),
            component.camera.orthographic_far(),
            component.camera.orthographic_near(),
            component.camera.orthographic_size(),
            component.camera.is_perspective() ? Serializable::ProjectionType_PERSPECTIVE
                                              : Serializable::ProjectionType_ORTHOGRAPHIC};
}

Serializable::Transform SceneSerializer::convert(const TransformComponent& component)
{
    return {component.enabled,
            {component.scale.x, component.scale.y, component.scale.z},
            {component.rotation.x, component.rotation.y, component.rotation.z},
            {component.translation.x, component.translation.y, component.translation.z}};
}

flatbuffers::Offset<Serializable::SpriteRenderer> SceneSerializer::convert(flatbuffers::FlatBufferBuilder& buffer,
                                                                           const SpriteRendererComponent& component)
{
    Serializable::Color* color =
        new Serializable::Color{component.color.r, component.color.g, component.color.b, component.color.a};
    return Serializable::CreateSpriteRendererDirect(buffer, component.enabled, component.texture_path.c_str(), color,
                                                    component.tiling_factor);
}

flatbuffers::Offset<Serializable::CircleRenderer> SceneSerializer::convert(flatbuffers::FlatBufferBuilder& buffer,
                                                                           const CircleRendererComponent& component)
{
    Serializable::Color* color =
        new Serializable::Color{component.color.r, component.color.g, component.color.b, component.color.a};
    return Serializable::CreateCircleRendererDirect(buffer, component.enabled, component.texture_path.c_str(), color,
                                                    component.fade, component.thickness);
}

Serializable::RigidBody2D SceneSerializer::convert(const RigidBody2DComponent& component)
{
    return {static_cast<Serializable::RigidBody2DType>(component.definition.type), component.definition.angle,
            component.definition.gravityScale, component.definition.linearDamping, component.definition.angularDamping};
}

Serializable::BoxCollider2D SceneSerializer::convert(const BoxCollider2DComponent& component)
{
    return {{component.size.x, component.size.y},
            component.fixture.density,
            component.fixture.friction,
            component.fixture.restitution};
}

Serializable::CircleCollider2D SceneSerializer::convert(const CircleCollider2DComponent& component)
{
    return {component.radius, component.fixture.density, component.fixture.friction, component.fixture.restitution};
}

CameraComponent SceneSerializer::convert(const Serializable::Camera& component)
{
    CameraComponent camera_component;
    camera_component.enabled = component.enabled();
    camera_component.primary = component.primary();
    camera_component.camera = {Serializable::ProjectionType_PERSPECTIVE ? SceneCamera::ProjectionType::PERSPECTIVE
                                                                        : SceneCamera::ProjectionType::ORTHOGRAPHIC,
                               component.perspective_far(),
                               component.perspective_near(),
                               component.perspective_fov(),
                               component.orthographic_far(),
                               component.orthographic_near(),
                               component.orthographic_size(),
                               component.aspect_ratio()};
    return camera_component;
}

TransformComponent SceneSerializer::convert(const Serializable::Transform& component)
{
    TransformComponent transform_component;
    transform_component.enabled = component.enabled();
    auto scale = component.scale();
    auto rotation = component.rotation();
    auto translation = component.translation();
    transform_component.scale = {scale.x(), scale.y(), scale.z()};
    transform_component.rotation = {rotation.x(), rotation.y(), rotation.z()};
    transform_component.translation = {translation.x(), translation.y(), translation.z()};
    return transform_component;
}

SpriteRendererComponent SceneSerializer::convert(const Serializable::SpriteRenderer& component)
{
    SpriteRendererComponent sprite_component;
    sprite_component.enabled = component.enabled();
    sprite_component.tiling_factor = component.tiling_factor();
    sprite_component.texture_path =
        component.texture_path()->c_str() == nullptr ? "" : component.texture_path()->c_str();
    sprite_component.texture = sprite_component.texture_path.empty()
                                   ? nullptr
                                   : Knt::Texture2D::load(sprite_component.texture_path, "SquareTexture");
    sprite_component.color = {component.color()->r(), component.color()->g(), component.color()->b(),
                              component.color()->a()};
    return sprite_component;
}

CircleRendererComponent SceneSerializer::convert(const Serializable::CircleRenderer& component)
{
    CircleRendererComponent circle_component;
    circle_component.fade = component.fade();
    circle_component.enabled = component.enabled();
    circle_component.thickness = component.thickness();
    circle_component.texture_path =
        component.texture_path()->c_str() == nullptr ? "" : component.texture_path()->c_str();
    circle_component.texture = circle_component.texture_path.empty()
                                   ? nullptr
                                   : Knt::Texture2D::load(circle_component.texture_path, "CircleTexture");
    circle_component.color = {component.color()->r(), component.color()->g(), component.color()->b(),
                              component.color()->a()};
    return circle_component;
}

RigidBody2DComponent SceneSerializer::convert(const Serializable::RigidBody2D& component)
{
    RigidBody2DComponent rigid_body_component;
    rigid_body_component.enabled = true;
    rigid_body_component.definition.type = static_cast<b2BodyType>(component.rigid_body_type());
    rigid_body_component.definition.angle = component.angle();
    rigid_body_component.definition.gravityScale = component.gravity_scale();
    rigid_body_component.definition.linearDamping = component.linear_damping();
    rigid_body_component.definition.angularDamping = component.angular_damping();
    return rigid_body_component;
}

BoxCollider2DComponent SceneSerializer::convert(const Serializable::BoxCollider2D& component)
{
    BoxCollider2DComponent box_collider_component;
    box_collider_component.size = {component.size().x(), component.size().y()};
    box_collider_component.fixture.density = component.density();
    box_collider_component.fixture.friction = component.friction();
    box_collider_component.fixture.restitution = component.restitution();
    return box_collider_component;
}

CircleCollider2DComponent SceneSerializer::convert(const Serializable::CircleCollider2D& component)
{
    CircleCollider2DComponent circle_collider_component;
    circle_collider_component.radius = component.radius();
    circle_collider_component.fixture.density = component.density();
    circle_collider_component.fixture.friction = component.friction();
    circle_collider_component.fixture.restitution = component.restitution();
    return circle_collider_component;
}

} // namespace Konto
