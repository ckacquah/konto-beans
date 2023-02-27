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

Serializable::SpriteRenderer SceneSerializer::convert(const SpriteRendererComponent& component)
{
    return {component.enabled,
            {component.color.r, component.color.g, component.color.b, component.color.a},
            component.tiling_factor};
}

Serializable::CircleRenderer SceneSerializer::convert(const CircleRendererComponent& component)
{
    return {component.enabled,
            {component.color.r, component.color.g, component.color.b, component.color.a},
            component.fade,
            component.thickness};
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
    auto color = component.color();
    sprite_component.color = {color.r(), color.g(), color.b(), color.a()};
    return sprite_component;
}

CircleRendererComponent SceneSerializer::convert(const Serializable::CircleRenderer& component)
{
    CircleRendererComponent circle_component;
    circle_component.fade = component.fade();
    circle_component.enabled = component.enabled();
    circle_component.thickness = component.thickness();
    auto color = component.color();
    circle_component.color = {color.r(), color.g(), color.b(), color.a()};
    return circle_component;
}

} // namespace Konto
