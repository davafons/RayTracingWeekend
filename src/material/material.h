#pragma once

class HitRecord;
class Vec3;
class Ray;

class Material {
public:
    virtual ~Material() = default;
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const = 0;

    static Vec3 random_in_unit_sphere();
    static Vec3 reflect(const Vec3& v, const Vec3& n);
    static bool refract(const Vec3& v, const Vec3& n, float ni_over_nt, Vec3& refracted);
    static float schlick(float cosine, float ref_idx);
};
