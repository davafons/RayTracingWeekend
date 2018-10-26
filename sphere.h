#pragma once

#include "hitable.h"

class Sphere : public Hitable
{
public:
  Sphere() = default;
  Sphere(Vec3 cen, float r) : center(cen), radius(r) {};
  bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const
    override;

private:
  Vec3 center;
  float radius;
};


bool Sphere::hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const
{
  Vec3 oc = r.origin() - center;
  float a = dot(r.direction(), r.direction());
  float b = dot(oc, r.direction());
  float c = dot(oc, oc) - radius*radius;
  float discriminant = b*b - a*c;

  if(discriminant > 0)
  {
    float temp = (-b - sqrt(b*b-a*c))/a;
    if(temp < t_max && temp > t_min)
    {
      rec.t = temp;
      rec.p = r.point_at_parameter(rec.t);
      rec.normal = (rec.p - center) / radius;
      return true;
    }

    temp = (-b + sqrt(b*b-a*c))/a;
    if(temp < t_max && temp > t_min)
    {
      rec.t = temp;
      rec.p = r.point_at_parameter(rec.t);
      rec.normal = (rec.p - center) / radius;
      return true;
    }
  }
  return false;
}
