#pragma once

#include <memory>

#include "hitable/hitable.h"

class Material;

class Sphere : public Hitable {
public:
  Sphere() = default;
  Sphere(Vec3 center, float radius, const std::shared_ptr<Material> &mat);

  bool hit(const Ray &r, float t_min, float t_max,
           HitRecord &rec) const override;

private:
  Vec3 center_;
  float radius_;
  std::shared_ptr<Material> mat_;
};
