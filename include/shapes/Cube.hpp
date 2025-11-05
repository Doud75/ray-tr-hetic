#pragma once

#include "../raymath/Hittable.hpp"
#include "../raymath/Vector.hpp"
#include "../materials/Material.hpp"

class Cube : public Hittable {
public:
    Cube(const Vector& minCorner, const Vector& maxCorner, std::shared_ptr<Material> m);

    bool hit(const Ray& ray, float t_min, float t_max, hit_record& rec) const override;

private:
    Vector minCorner;
    Vector maxCorner;
    std::shared_ptr<Material> mat;
};
