#pragma once

#include "Hittable.hpp"
#include "Vector.hpp"
#include "Color.hpp"

class Plane : public Hittable {
public:
    Plane(float y, float scale = 1.0f);

    bool hit(const Ray& ray, 
             float t_min, 
             float t_max, 
             hit_record& rec) const override;

    bool isWhiteSquare(float x, float z) const;

private:
    float y_position;
    float checker_scale;
};

