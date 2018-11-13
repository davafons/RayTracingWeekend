#include "dielectric.h"
#include "hitable/hitable.h"
#include "math/math.h"

Dielectric::Dielectric(float ref_idx) : ref_idx_(ref_idx) {}

bool Dielectric::scatter(const Ray &r_in, const HitRecord &rec,
                         Vec3 &attenuation, Ray &scattered) const {
  Vec3 outward_normal;
  Vec3 reflected = Math::reflect(r_in.direction(), rec.normal);
  float ni_over_nt;
  attenuation = Vec3(1.0f, 1.0f, 1.0f);
  Vec3 refracted;
  float reflect_prob;
  float cosine;

  if (dot(r_in.direction(), rec.normal) > 0) {
    outward_normal = -rec.normal;
    ni_over_nt = ref_idx_;
    cosine =
        ref_idx_ * dot(r_in.direction(), rec.normal) / r_in.direction().length();
  } else {
    outward_normal = rec.normal;
    ni_over_nt = 1.0f / ref_idx_;
    cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
  }

  if (Math::refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
    reflect_prob = Math::schlick(cosine, ref_idx_);
  else
    reflect_prob = 1.0f;

  if (Math::drand48() < reflect_prob)
    scattered = Ray(rec.p, reflected);
  else
    scattered = Ray(rec.p, refracted);

  return true;
}
