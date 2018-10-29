#pragma once

#include "ray.h"
#include "hitable.h"

class Material
{
public:
  virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3&
      attenuation, Ray& scattered) const = 0;

protected:
  Vec3 random_in_unit_sphere() const
  {
    Vec3 p;
    do
      p = 2.0f * Vec3(drand48(), drand48(), drand48()) - Vec3(1, 1, 1);
    while(p.squared_length() >= 1.0f);

    return p;
  }

  Vec3 reflect(const Vec3& v, const Vec3& n) const
  {
    return v - 2 * dot(v, n) * n;
  }
};

