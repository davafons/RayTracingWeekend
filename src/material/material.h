#pragma once

class HitRecord;
class Vec3;
class Ray;

class Material {
public:
  virtual ~Material() = default;

  virtual bool scatter(const Ray &r_in, const HitRecord &rec, Vec3 &attenuation,
                       Ray &scattered) const = 0;
};
