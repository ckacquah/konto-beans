#ifndef __KONTO_COMPONENTS_COMMON_H__
#define __KONTO_COMPONENTS_COMMON_H__

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

#include "konto/core/camera.h"

namespace Konto
{

struct UUIDComponent
{
    uint64_t id;

    UUIDComponent() = default;
    UUIDComponent(const UUIDComponent&) = default;
    UUIDComponent(uint64_t uuid) : id(uuid)
    {
    }
};

struct TagComponent
{
    bool enabled{true};

    std::string tag;

    TagComponent() = default;
    TagComponent(const TagComponent&) = default;
    TagComponent(const std::string& title) : tag(title){};
};

struct TransformComponent
{
    bool enabled{true};

    glm::vec3 scale{1.0f, 1.0f, 1.0f};
    glm::vec3 rotation{0.0f, 0.0f, 0.0f};
    glm::vec3 translation{0.0f, 0.0f, 0.0f};

    TransformComponent() = default;
    TransformComponent(const TransformComponent&) = default;

    glm::mat4 transform() const
    {
        glm::mat4 rotation_ = glm::toMat4(glm::quat(rotation));
        return glm::translate(glm::mat4(1.0f), translation) * rotation_ * glm::scale(glm::mat4(1.0f), scale);
    }
};

struct CameraComponent
{
    SceneCamera camera;
    bool enabled{true};
    bool primary{true};

    CameraComponent() = default;
    CameraComponent(const CameraComponent&) = default;
};

} // namespace Konto

#endif // __KONTO_COMPONENTS_COMMON_H__
