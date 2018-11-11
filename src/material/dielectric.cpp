#include "dielectric.h"

Dielectric::Dielectric(float ri)
    : ref_idx(ri)
{
}

bool Dielectric::scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const
{
    Vec3 outward_normal;
    Vec3 reflected = reflect(r_in.direction(), rec.normal);
    float ni_over_nt;
    attenuation = Vec3(1.0f, 1.0f, 1.0f);
    Vec3 refracted;
    float reflect_prob;
    float cosine;

    if (dot(r_in.direction(), rec.normal) > 0) {
        outward_normal = -rec.normal;
        ni_over_nt = ref_idx;
        cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
    } else {
        outward_normal = rec.normal;
        ni_over_nt = 1.0f / ref_idx;
        cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
    }

    if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
        reflect_prob = schlick(cosine, ref_idx);
    else
        reflect_prob = 1.0f;

    if (drand48() < reflect_prob)
        scattered = Ray(rec.p, reflected);
    else
        scattered = Ray(rec.p, refracted);

    return true;
}
