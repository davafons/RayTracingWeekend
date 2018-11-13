#include "camera.h"
#include "hitable/ray.h"
#include "math/math.h"

Camera::Camera(const Vec3 &lookfrom, const Vec3 &lookat, const Vec3 &vup,
               float vfov, float aspect, float aperture, float focus_dist) {

  lens_radius_ = aperture / 2;
  float theta = vfov * Math::PI / 180;
  float half_height = tan(theta / 2);
  float half_width = aspect * half_height;

  origin_ = lookfrom;
  w_ = unit_vector(lookfrom - lookat);
  u_ = unit_vector(cross(vup, w_));
  v_ = cross(w_, u_);

  lower_left_corner_ = origin_ - half_width * focus_dist * u_ -
                      half_height * focus_dist * v_ - focus_dist * w_;
  horizontal_ = 2 * half_width * focus_dist * u_;
  vertical_ = 2 * half_height * focus_dist * v_;
}

Ray Camera::getRay(float s, float t) {
  Vec3 rd = lens_radius_ * random_in_unit_disk();
  Vec3 offset = u_ * rd.x() + v_ * rd.y();

  return Ray(origin_ + offset, lower_left_corner_ + s * horizontal_ +
                                  t * vertical_ - origin_ - offset);
}

Vec3 Camera::random_in_unit_disk() {
  Vec3 p;
  do
    p = 2.0f * Vec3(Math::drand48(), Math::drand48(), 0) - Vec3(1, 1, 0);
  while (dot(p, p) >= 1.0f);

  return p;
}
