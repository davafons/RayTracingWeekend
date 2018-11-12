#include <cmath>

#include "material.h"
#include "math/vec3.h"

Vec3 Material::random_in_unit_sphere()
{
    Vec3 p;
    do
        p = 2.0f * Vec3(float(rand())/RAND_MAX, float(rand())/RAND_MAX, float(rand())/RAND_MAX) - Vec3(1, 1, 1);
    while (p.squared_length() >= 1.0f);

    return p;
}

Vec3 Material::reflect(const Vec3& v, const Vec3& n)
{
    return v - 2 * dot(v, n) * n;
}

bool Material::refract(const Vec3& v, const Vec3& n, float ni_over_nt, Vec3& refracted)
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

float Material::schlick(float cosine, float ref_idx)
{
    float r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}
