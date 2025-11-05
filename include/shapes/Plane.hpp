#pragma once

#include "Hittable.hpp"
#include "Vector.hpp"
#include "Color.hpp"
#include <memory>

class Plane : public Hittable {
public:
    Plane(float y, std::shared_ptr<Material> m);

    bool hit(const Ray& ray, 
             float t_min, 
             float t_max, 
             hit_record& rec) const override;

private:
    float y_position;
    std::shared_ptr<Material> mat;
};

