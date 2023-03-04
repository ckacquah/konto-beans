#ifndef __KONTO_SERIALIZATION_H__
#define __KONTO_SERIALIZATION_H__

#include <memory>
#include <tuple>

#include <flatbuffers/flatbuffers.h>

#include "konto/components/common.h"
#include "konto/components/physics.h"
#include "konto/components/renderer2d.h"
#include "konto/core/camera.h"
#include "konto/core/entity.h"
#include "konto/core/scene.h"
#include "konto/serialization/components.h"
#include "konto/serialization/scene.h"

namespace Konto
{

class SceneSerializer
{
  private:
    static flatbuffers::Offset<Serializable::Scene> convert(flatbuffers::FlatBufferBuilder& buffer_builder,
                                                            Scene& scene);
    static flatbuffers::Offset<Serializable::Entity> convert(flatbuffers::FlatBufferBuilder& buffer_builder,
                                                             Entity& entity);

    static Serializable::Camera convert(const CameraComponent& component);
    static Serializable::Transform convert(const TransformComponent& component);

    static flatbuffers::Offset<Serializable::SpriteRenderer> convert(flatbuffers::FlatBufferBuilder& buffer_builder,
                                                                     const SpriteRendererComponent& component);
    static flatbuffers::Offset<Serializable::CircleRenderer> convert(flatbuffers::FlatBufferBuilder& buffer_builder,
                                                                     const CircleRendererComponent& component);

    static Serializable::RigidBody2D convert(const RigidBody2DComponent& component);
    static Serializable::BoxCollider2D convert(const BoxCollider2DComponent& component);
    static Serializable::CircleCollider2D convert(const CircleCollider2DComponent& component);

    static Scene convert(const Serializable::Scene& scene);
    static Entity convert(const Serializable::Entity& entity, Scene& scene);

    static CameraComponent convert(const Serializable::Camera& component);
    static TransformComponent convert(const Serializable::Transform& component);
    static SpriteRendererComponent convert(const Serializable::SpriteRenderer& component);
    static CircleRendererComponent convert(const Serializable::CircleRenderer& component);

    static RigidBody2DComponent convert(const Serializable::RigidBody2D& component);
    static BoxCollider2DComponent convert(const Serializable::BoxCollider2D& component);
    static CircleCollider2DComponent convert(const Serializable::CircleCollider2D& component);

  public:
    static std::shared_ptr<Scene> deserialize(const uint8_t* buffer, size_t size);
    static std::tuple<std::shared_ptr<uint8_t[]>, size_t> serialize(Scene& scene);
};

} // namespace Konto

#endif // __KONTO_SERIALIZATION_H__
