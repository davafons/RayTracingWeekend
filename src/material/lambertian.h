#pragma once

#include "material.h"
#include "math/vec3.h"

class Lambertian : public Material {
public:
    explicit Lambertian(const Vec3& a);

    bool scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const override;

private:
    Vec3 albedo;
};
