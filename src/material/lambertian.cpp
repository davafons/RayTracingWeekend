#include "hitable/hitable.h"
#include "lambertian.h"
#include "math/math.h"

Lambertian::Lambertian(const Vec3 &albedo) : albedo_(albedo) {}

bool Lambertian::scatter(const Ray &r_in, const HitRecord &rec,
                         Vec3 &attenuation, Ray &scattered) const {
  Vec3 target = rec.p + rec.normal + Math::random_in_unit_sphere();
  scattered = Ray(rec.p, target - rec.p);
  attenuation = albedo_;

  return true;
}
