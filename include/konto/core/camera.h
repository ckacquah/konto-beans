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

    bool fixed_aspect_ratio{false};

  private:
    ProjectionType projection_type_{ProjectionType::ORTHOGRAPHIC};

    float perspective_far_{1000.0f};
    float perspective_near_{0.01f};
    float perspective_fov_{glm::radians(45.0f)};

    float orthographic_far_{1.0f};
    float orthographic_near_{-1.0f};
    float orthographic_size_{10.0f};

    float aspect_ratio_{0.0f};

    void recalculate();

  public:
    SceneCamera();
    ~SceneCamera() = default;
    SceneCamera(ProjectionType projection_type, float perspective_far, float perspective_near, float perspective_fov,
                float orthographic_far, float orthographic_near, float orthographic_size, float aspect_ratio)
        : projection_type_(projection_type), perspective_far_(perspective_far), perspective_near_(perspective_near),
          perspective_fov_(perspective_fov), orthographic_far_(orthographic_far), orthographic_near_(orthographic_near),
          orthographic_size_(orthographic_size), aspect_ratio_(aspect_ratio)
    {
        recalculate();
    }

    bool is_perspective() const;
    bool is_orthographic() const;
    void set_projection_type(ProjectionType type);

    float perspective_far() const;
    float perspective_near() const;
    float perspective_fov() const;

    float orthographic_far() const;
    float orthographic_near() const;
    float orthographic_size() const;

    void set_perspective_far(float far);
    void set_perspective_near(float near);
    void set_perspective_fov(float fov);

    void set_orthographic_far(float far);
    void set_orthographic_near(float near);
    void set_orthographic_size(float size);

    float aspect_ratio() const;
    void set_aspect_ratio(float ratio);

    void set_viewport_size(uint32_t width, uint32_t height);
};

} // namespace Konto

#endif // __KONTO_CORE_CAMERA_H__
