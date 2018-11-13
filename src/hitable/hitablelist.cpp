#include "hitablelist.h"

HitableList::HitableList(const std::vector<std::shared_ptr<Hitable>> &l)
    : list_(l) {}

bool HitableList::hit(const Ray &r, float t_min, float t_max,
                      HitRecord &rec) const {
  HitRecord temp_rec;
  bool hit_anything = false;
  double closest_so_far = t_max;

  for (const auto &obj: list_) {
    if (obj->hit(r, t_min, closest_so_far, temp_rec)) {
      hit_anything = true;
      closest_so_far = temp_rec.t;
      rec = std::move(temp_rec);
    }
  }

  return hit_anything;
}
