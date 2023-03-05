#ifndef __KONTO_COMPONENTS_PHYSICS_H__
#define __KONTO_COMPONENTS_PHYSICS_H__

#include <memory>

#include <box2d/box2d.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Konto
{

struct RigidBody2DComponent
{
    b2Body* body{};
    b2BodyDef definition{};

    bool enabled{true};

    RigidBody2DComponent() = default;
    RigidBody2DComponent(const RigidBody2DComponent&) = default;
};

struct BoxCollider2DComponent
{
    b2FixtureDef fixture{};
    b2PolygonShape shape{};

    bool enabled{true};
    glm::vec2 size{1.0f, 1.0f};

    BoxCollider2DComponent() = default;
    BoxCollider2DComponent(const BoxCollider2DComponent&) = default;
};

struct CircleCollider2DComponent
{
    b2FixtureDef fixture{};
    b2CircleShape shape{};

    bool enabled{true};
    float radius{0.5f};

    CircleCollider2DComponent() = default;
    CircleCollider2DComponent(const CircleCollider2DComponent&) = default;
};

} // namespace Konto

#endif // __KONTO_COMPONENTS_PHYSICS_H__