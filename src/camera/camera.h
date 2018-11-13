#pragma once

#include "math/vec3.h"

class Ray;

class Camera {
public:
  Camera(const Vec3 &lookfrom, const Vec3 &lookat, const Vec3 &vup, float vfov,
         float aspect, float aperture, float focus_dist);

  Ray getRay(float s, float t);

private:
  Vec3 random_in_unit_disk();

private:
  Vec3 origin_;
  Vec3 lower_left_corner_;
  Vec3 horizontal_;
  Vec3 vertical_;
  Vec3 u_, v_, w_;
  float lens_radius_;
};
