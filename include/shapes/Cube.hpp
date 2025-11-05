#pragma once

#include "../raymath/Hittable.hpp"
#include "../raymath/Vector.hpp"

class Cube : public Hittable {
public:
    Cube(const Vector& minCorner, const Vector& maxCorner);

    bool hit(const Ray& ray, float t_min, float t_max, hit_record& rec) const override;

private:
    Vector minCorner;  // coin minimal (x-, y-, z-)
    Vector maxCorner;  // coin maximal (x+, y+, z+)
};
