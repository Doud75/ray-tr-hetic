#pragma once

#include "../raymath/Hittable.hpp"
#include "../raymath/Vector.hpp"
#include <memory>

class Sphere : public Hittable {
public:
    Sphere(const Vector& center, float radius), std::shared_ptr<Material> m;

    bool hit(const Ray& ray, float t_min, float t_max, hit_record& rec) const override;

private:
    Vector center;
    float radius;
    std::shared_ptr<Material> mat;
};