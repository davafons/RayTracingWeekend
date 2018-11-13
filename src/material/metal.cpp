#include "hitable/hitable.h"
#include "math/math.h"
#include "metal.h"

Metal::Metal(const Vec3 &albedo, float fuzz) : albedo_(albedo)
{
  fuzz_ = (fuzz > 1.0f) ? 1.0f : fuzz;
}

bool Metal::scatter(const Ray &r_in, const HitRecord &rec, Vec3 &attenuation,
                    Ray &scattered) const {
  Vec3 reflected = Math::reflect(unit_vector(r_in.direction()), rec.normal);
  scattered = Ray(rec.p, reflected + fuzz_ * Math::random_in_unit_sphere());
  attenuation = albedo_;

  return (dot(scattered.direction(), rec.normal) > 0);
}
