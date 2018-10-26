#pragma once

#include "Ray.h"

struct HitRecord
{
  float t;
  Vec3 p;
  Vec3 normal;
};

class Hitable
{
public:
  virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec)
    const = 0;
};
