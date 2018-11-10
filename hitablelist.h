#pragma once

#include <memory>
#include <vector>

#include "hitable.h"

class HitableList : public Hitable {
public:
    HitableList() = default;
    explicit HitableList(const std::vector<std::shared_ptr<Hitable>>& l)
        : list(l)
    {
    }
    bool hit(
        const Ray& r, float t_min, float t_max, HitRecord& rec) const override;

    void push_back(std::shared_ptr<Hitable> obj) { list.push_back(obj); }
    void pop_back() { list.pop_back(); }

private:
    std::vector<std::shared_ptr<Hitable>> list;
};

bool HitableList::hit(
    const Ray& r, float t_min, float t_max, HitRecord& rec) const
{
    HitRecord temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;

    for (const auto& object : list) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}
