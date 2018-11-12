#pragma once

#include <memory>
#include <vector>

#include "hitable.h"

class HitableList : public Hitable {
public:
  HitableList() = default;
  explicit HitableList(const std::vector<std::shared_ptr<Hitable>> &l);

  bool hit(const Ray &r, float t_min, float t_max,
           HitRecord &rec) const override;

  void push_back(std::shared_ptr<Hitable> obj) { list.push_back(obj); }
  void pop_back() { list.pop_back(); }

private:
  std::vector<std::shared_ptr<Hitable>> list;
};
