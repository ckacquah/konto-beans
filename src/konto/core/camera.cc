#include <glm/gtc/type_ptr.hpp>

#include "konto/core/camera.h"

namespace Konto
{

SceneCamera::SceneCamera()
{
    recalculate();
}

SceneCamera::ProjectionType SceneCamera::projection_type() const
{
    return projection_type_;
}

void SceneCamera::set_projection_type(ProjectionType type)
{
    projection_type_ = type;
    recalculate();
}

float SceneCamera::far_clip() const
{
    return (projection_type_ == ProjectionType::ORTHOGRAPHIC) ? orthographic_far_ : perspective_far_;
}

float SceneCamera::near_clip() const
{
    return (projection_type_ == ProjectionType::ORTHOGRAPHIC) ? orthographic_near_ : perspective_near_;
}

void SceneCamera::set_far_clip(float clip)
{
    if (projection_type_ == ProjectionType::ORTHOGRAPHIC)
    {
        orthographic_far_ = clip;
    }
    else
    {
        perspective_far_ = clip;
    }

    recalculate();
}

void SceneCamera::set_near_clip(float clip)
{
    if (projection_type_ == ProjectionType::ORTHOGRAPHIC)
    {
        orthographic_near_ = clip;
    }
    else
    {
        perspective_near_ = clip;
    }

    recalculate();
}

float SceneCamera::perspective_FOV() const
{
    return perspective_FOV_;
}

float SceneCamera::othorgraphic_size() const
{
    return orthographic_size_;
}

void SceneCamera::set_perspective_FOV(float FOV)
{
    perspective_FOV_ = FOV;
    recalculate();
}

void SceneCamera::set_othorgraphic_size(float size)
{
    orthographic_size_ = size;
    recalculate();
}

void SceneCamera::set_viewport_size(uint32_t width, uint32_t height)
{
    aspect_ratio_ = static_cast<float>(width) / height;
    recalculate();
}

void SceneCamera::recalculate()
{
    if (projection_type_ == ProjectionType::PERSPECTIVE)
    {
        projection_ = glm::perspective(perspective_FOV_, aspect_ratio_, perspective_near_, perspective_far_);
    }
    else
    {
        float orthographic_top = orthographic_size_ * 0.5f;
        float orthographic_bottom = -orthographic_size_ * 0.5f;
        float orthographic_left = -orthographic_size_ * aspect_ratio_ * 0.5f;
        float orthographic_right = orthographic_size_ * aspect_ratio_ * 0.5f;

        projection_ = glm::ortho(orthographic_left, orthographic_right, orthographic_bottom, orthographic_top,
                                 orthographic_near_, orthographic_far_);
    }
}

} // namespace Konto
