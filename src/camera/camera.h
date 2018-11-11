#pragma once

#include "hitable/ray.h"

class Camera {
public:
    Camera(const Vec3& lookfrom, const Vec3& lookat, const Vec3& vup, float vfov, float aspect, float aperture,
        float focus_dist);

    Ray getRay(float s, float t);

private:
    Vec3 random_in_unit_disk();

private:
    Vec3 origin;
    Vec3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 u, v, w;
    float lens_radius;
};
