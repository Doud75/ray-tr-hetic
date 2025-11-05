#pragma once

#include "Material.hpp"
#include "../raymath/Utils.hpp"

class Lambertian : public Material {
public:
    Lambertian(const Color& a) : albedo(a) {}

    virtual bool scatter(
        const Ray& r_in,
        const hit_record& rec,
        Color& attenuation,
        Ray& scattered
    ) const override {
        auto scatter_direction = rec.normal + random_unit_vector();

        if (scatter_direction.length_squared() < 1e-8) {
            scatter_direction = rec.normal;
        }

        scattered = Ray(rec.point, scatter_direction);
        attenuation = albedo;
        return true;
    }

private:
    Color albedo;
};