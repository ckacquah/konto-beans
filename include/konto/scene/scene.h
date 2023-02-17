#ifndef __KONTO_SCENE_H__
#define __KONTO_SCENE_H__

#include <kontomire.h>

namespace Konto
{

class Scene
{
  private:
    Knt::Camera camera_;

    void render_scene(const std::shared_ptr<Knt::Camera>& camera);

  public:
    Scene();
    ~Scene() = default;

    void stop();
    void start();
    void update(float timestep);
    void update(float timestep, const std::shared_ptr<Knt::Camera>& camera);

    void resize_viewport(uint32_t width, uint32_t height);
};

} // namespace Konto

#endif // __KONTO_SCENE_H__