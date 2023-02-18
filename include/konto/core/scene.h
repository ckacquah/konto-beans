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
    SceneCamera camera_;
    entt::registry registry_;

    void render_scene(const std::shared_ptr<SceneCamera>& camera);

  public:
    Scene();
    ~Scene() = default;

    void stop();
    void start();
    void update(float timestep);
    void update(float timestep, const std::shared_ptr<SceneCamera>& camera);

    void destroy_entity(Entity entity);
    Entity create_entity(const std::string& name);

    void resize_viewport(uint32_t width, uint32_t height);

    friend class Entity;
};

} // namespace Konto

#endif // __KONTO_SCENE_H__