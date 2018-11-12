#pragma once

#include <memory>

#include "hitable/hitable.h"

class Material;

class Sphere : public Hitable {
public:
    Sphere() = default;
    Sphere(Vec3 cen, float r, const std::shared_ptr<Material>& m);

    bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const override;

private:
    Vec3 center;
    float radius;
    std::shared_ptr<Material> mat;
};
