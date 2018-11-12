#pragma once

#include "material.h"

class Dielectric : public Material {
public:
  explicit Dielectric(float ri);
  virtual ~Dielectric() = default;

  bool scatter(const Ray &r_in, const HitRecord &rec, Vec3 &attenuation,
               Ray &scattered) const override;

private:
  float ref_idx;
};
