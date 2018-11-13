#include "sphere.h"

Sphere::Sphere(Vec3 center, float radius, const std::shared_ptr<Material> &mat)
    : center_(center), radius_(radius), mat_(mat) {}

bool Sphere::hit(const Ray &r, float t_min, float t_max, HitRecord &rec) const {
  Vec3 oc = r.origin() - center_;
  float a = dot(r.direction(), r.direction());
  float b = dot(oc, r.direction());
  float c = dot(oc, oc) - radius_ * radius_;
  float discriminant = b * b - a * c;

  if (discriminant > 0) {
    float temp = (-b - sqrt(discriminant)) / a;
    if (temp < t_max && temp > t_min) {
      rec.t = temp;
      rec.p = r.point_at_parameter(rec.t);
      rec.normal = (rec.p - center_) / radius_;
      rec.mat = mat_;
      return true;
    }

    temp = (-b + sqrt(discriminant)) / a;
    if (temp < t_max && temp > t_min) {
      rec.t = temp;
      rec.p = r.point_at_parameter(rec.t);
      rec.normal = (rec.p - center_) / radius_;
      rec.mat = mat_;
      return true;
    }
  }
  return false;
}
