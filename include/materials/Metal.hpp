#pragma once

#include "Material.hpp"

class Metal : public Material {
public:
    Metal(const Color& albedo, float fuzz = 0.0f);

    bool scatter(
        const Ray& ray_in,
        const hit_record& rec,
        Color& attenuation,
        Ray& scattered
    ) const override;

private:
    Color albedo;
    float fuzz;
};

