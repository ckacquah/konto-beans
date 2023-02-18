#ifndef __KONTO_SCENE_H__
#define __KONTO_SCENE_H__

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

  public:
    Scene() = default;
    ~Scene() = default;

    void update(float timestep);

    void destroy_entity(Entity entity);
    Entity create_entity(const std::string& name);

    void resize_viewport(uint32_t width, uint32_t height);

    friend class Entity;
};

} // namespace Konto

#endif // __KONTO_SCENE_H__