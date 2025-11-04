#pragma once

#include "Material.hpp"

class Lambertian : public Material {
public:
    Lambertian(const Color& albedo);

    bool scatter(
        const Ray& ray_in,
        const hit_record& rec,
        Color& attenuation,
        Ray& scattered
    ) const override;

private:
    Color albedo;
};

