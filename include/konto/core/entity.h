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
    Scene* scene_ptr_;
    entt::entity handle_{entt::null};

  public:
    Entity() = default;
    Entity(const Entity& other) = default;
    Entity(entt::entity handle, Scene* scene) : handle_(handle), scene_ptr_(scene){};

    template <typename T> T& get()
    {
        return scene_ptr_->registry_.get<T>(handle_);
    }

    template <typename T> bool has()
    {
        auto&& storage = scene_ptr_->registry_.storage<T>();
        return storage.contains(handle_);
    }

    template <typename T> void remove()
    {
        scene_ptr_->registry_.remove<T>(handle_);
    }

    template <typename T, typename... Args> T& add(Args&&... args)
    {
        T& component = scene_ptr_->registry_.emplace<T>(handle_, std::forward<Args>(args)...);
        return component;
    }

    template <typename T, typename... Args> T& add_or_replace(Args&&... args)
    {
        T& component = scene_ptr_->registry_.emplace_or_replace<T>(handle_, std::forward<Args>(args)...);
        return component;
    }

    operator entt::entity() const
    {
        return handle_;
    }

    operator bool() const
    {
        return handle_ != entt::null;
    }
};

} // namespace Konto

#endif // __KONTO_ENTITY_H__