#ifndef __KONTO_CORE_CAMERA_H__
#define __KONTO_CORE_CAMERA_H__

#include <kontomire.h>

namespace Konto
{

class SceneCamera : public Knt::Camera
{
  public:
    enum class ProjectionType
    {
        PERSPECTIVE = 0,
        ORTHOGRAPHIC = 1
    };

  private:
    ProjectionType projection_type_{ProjectionType::PERSPECTIVE};

    float perspective_far_{1000.0f};
    float perspective_near_{0.01f};
    float perspective_FOV_{glm::radians(45.0f)};

    float orthographic_far_{1.0f};
    float orthographic_near_{-1.0f};
    float orthographic_size_{10.0f};

    float aspect_ratio_{0.0f};

    void recalculate();

  public:
    SceneCamera();
    ~SceneCamera() = default;

    ProjectionType projection_type() const;
    void set_projection_type(ProjectionType type);

    float far_clip() const;
    float near_clip() const;

    void set_far_clip(float clip);
    void set_near_clip(float clip);

    float perspective_FOV() const;
    float othorgraphic_size() const;

    void set_perspective_FOV(float FOV);
    void set_othorgraphic_size(float size);

    void set_viewport_size(uint32_t width, uint32_t height);
};

} // namespace Konto

#endif // __KONTO_CORE_CAMERA_H__
