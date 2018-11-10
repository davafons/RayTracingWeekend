#pragma once

#include <cmath>

#include "hitable.h"
#include "ray.h"

class Material {
public:
    virtual ~Material() = default;
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const = 0;

protected:
    Vec3 random_in_unit_sphere() const
    {
        Vec3 p;
        do
            p = 2.0f * Vec3(drand48(), drand48(), drand48()) - Vec3(1, 1, 1);
        while (p.squared_length() >= 1.0f);

        return p;
    }

    Vec3 reflect(const Vec3& v, const Vec3& n) const
    {
        return v - 2 * dot(v, n) * n;
    }

    bool refract(const Vec3& v, const Vec3& n, float ni_over_nt, Vec3& refracted)
        const
    {
        Vec3 uv = unit_vector(v);
        float dt = dot(uv, n);
        float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1 - dt * dt);
        if (discriminant > 0) {
            refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
            return true;
        } else
            return false;
    }

    float schlick(float cosine, float ref_idx) const
    {
        float r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }
};
