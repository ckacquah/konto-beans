#ifndef __KONTO_COMPONENTS_RENDERER_2D_H__
#define __KONTO_COMPONENTS_RENDERER_2D_H__

#include <memory>

#include <kontomire.h>

namespace Konto
{

struct SpriteRendererComponent
{
    float tiling_factor{1.0f};
    glm::vec4 color{1.0f, 1.0f, 1.0f, 1.0f};
    std::shared_ptr<Knt::Texture2D> texture{nullptr};

    SpriteRendererComponent() = default;
    SpriteRendererComponent(const SpriteRendererComponent&) = default;
};

struct CircleRendererComponent
{
    float fade{0.005f};
    float thickness{1.0f};
    glm::vec4 color{1.0f, 1.0f, 1.0f, 1.0f};

    CircleRendererComponent() = default;
    CircleRendererComponent(const CircleRendererComponent&) = default;
};

} // namespace Konto

#endif // __KONTO_COMPONENTS_RENDERER_2D_H__
