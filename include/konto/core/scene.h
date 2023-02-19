#ifndef __KONTO_SCENE_H__
#define __KONTO_SCENE_H__

#include <functional>
#include <memory>

#include <entt/entt.hpp>
#include <kontomire.h>

#include "konto/core/camera.h"

namespace Konto
{

class Entity;

class Scene
{
  private:
    entt::registry registry_;

    void update_scene();

  public:
    Scene() = default;

    void update();
    void update(const SceneCamera& camera, const glm::mat4& transform);

    void destroy_entity(Entity entity);
    Entity create_entity(const std::string& name);
    void foreach_entity(std::function<void(Entity)> callback);

    void resize_viewport(uint32_t width, uint32_t height);

    friend class Entity;
};

} // namespace Konto

#endif // __KONTO_SCENE_H__