#pragma once

#include "../raymath/Ray.hpp"
#include "../raymath/Color.hpp"
#include "../raymath/Hittable.hpp"

class Material {
public:
    virtual ~Material() = default;
    
    virtual bool scatter(
        const Ray& ray_in,
        const hit_record& rec,
        Color& attenuation,
        Ray& scattered
    ) const = 0;
};

