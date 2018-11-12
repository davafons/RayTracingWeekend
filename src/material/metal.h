#pragma once

#include "material.h"
#include "math/vec3.h"

class Metal : public Material {
public:
  Metal(const Vec3 &a, float f);

  bool scatter(const Ray &r_in, const HitRecord &rec, Vec3 &attenuation,
               Ray &scattered) const override;

private:
  Vec3 albedo;
  float fuzz;
};
