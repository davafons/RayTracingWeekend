#pragma once

#include "material.h"

class Lambertian : public Material {
public:
    explicit Lambertian(const Vec3& a)
        : albedo(a)
    {
    }

    bool scatter(const Ray& r_in,
        const HitRecord& rec,
        Vec3& attenuation,
        Ray& scattered) const override
    {
        Vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        scattered = Ray(rec.p, target - rec.p);
        attenuation = albedo;
        return true;
    }

private:
    Vec3 albedo;
};
