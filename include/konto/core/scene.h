#ifndef __KONTO_CORE_SCENE_H__
#define __KONTO_CORE_SCENE_H__

#include <functional>
#include <map>
#include <memory>

#include <box2d/box2d.h>
#include <entt/entt.hpp>
#include <kontomire.h>

#include "konto/core/camera.h"
#include "konto/core/timestep.h"

#define UNTITLED_ENTITY "Untitled Entity"

namespace Konto
{

class Entity;

class Scene
{
  private:
    TimeStep timestep_{};

    b2World* world_;

    entt::registry registry_;
    std::unordered_map<uint64_t, entt::entity> entities_;

    int32 velocity_iterations_{6};
    int32 position_iterations_{2};

    template <typename... Component>
    static void copy(entt::registry& source, entt::registry& destination,
                     std::unordered_map<uint64_t, entt::entity>& entities);

  public:
    Scene() = default;

    void start();
    void update();
    void render();
    void step(float delta);
    void resize(uint32_t width, uint32_t height);
    void render(const glm::mat4& view, const glm::mat4& projection);

    Entity create(const std::string& name);
    Entity create(const std::string& name, uint64_t uuid);

    void destroy(Entity entity);
    void foreach (std::function<void(Entity)> callback);

    std::shared_ptr<Scene> clone();

    friend class Entity;
};

} // namespace Konto

#endif // __KONTOCORE__SCENE_H__