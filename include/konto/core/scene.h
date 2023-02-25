#ifndef __KONTO_SCENE_H__
#define __KONTO_SCENE_H__

#include <functional>
#include <map>
#include <memory>

#include <entt/entt.hpp>
#include <kontomire.h>

#include "konto/core/camera.h"

#define UNTITLED_ENTITY "Untitled Entity"

namespace Konto
{

class Entity;

class Scene
{
  private:
    entt::registry registry_;
    std::unordered_map<uint64_t, entt::entity> entities_;

    template <typename... Component>
    static void clone(entt::registry& source, entt::registry& destination,
                      std::unordered_map<uint64_t, entt::entity>& entities);

  public:
    Scene() = default;

    void update();
    void render();
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

#endif // __KONTO_SCENE_H__