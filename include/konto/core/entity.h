#ifndef __KONTO_ENTITY_H__
#define __KONTO_ENTITY_H__

#include <memory>

#include <entt/entt.hpp>

#include "konto/core/scene.h"

namespace Konto
{

class Entity
{
  private:
    entt::entity handle_{entt::null};
    std::shared_ptr<Scene> scene_{nullptr};

  public:
    Entity() = default;
    Entity(const Entity& other) = default;
    Entity(entt::entity handle, const std::shared_ptr<Scene>& scene) : handle_(handle), scene_(scene)
    {
    }

    template <typename T> T& get()
    {
        return scene_->registry_.get<T>(handle_);
    }

    template <typename T> bool has()
    {
        return scene_->registry_.has<T>(handle_);
    }

    template <typename T> void remove()
    {
        scene_->registry_.remove<T>(handle_);
    }

    template <typename T, typename... Args> T& add(Args&&... args)
    {
        T& component = scene_->registry_.emplace<T>(handle_, std::forward<Args>(args)...);
        return component;
    }

    template <typename T, typename... Args> T& add_or_replace(Args&&... args)
    {
        T& component = scene_->registry_.emplace_or_replace<T>(handle_, std::forward<Args>(args)...);
        return component;
    }

    operator entt::entity() const
    {
        return handle_;
    }
};

} // namespace Konto

#endif // __KONTO_ENTITY_H__