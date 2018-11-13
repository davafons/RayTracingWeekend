#include <cmath>

#include "vec3.h"


class Math {
public:
  static constexpr double PI = std::atan(1) * 4;

  static double drand48() { return double(rand()) / RAND_MAX; }

  static Vec3 random_in_unit_sphere();

  static Vec3 reflect(const Vec3 &v, const Vec3 &n);
  static bool refract(const Vec3 &v, const Vec3 &n, float ni_over_nt,
                      Vec3 &refracted);
  static float schlick(float cosine, float ref_idx);
};
