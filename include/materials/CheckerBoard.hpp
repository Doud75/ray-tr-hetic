#pragma once

#include "Material.hpp"
#include "../raymath/Utils.hpp"
#include <cmath>

class CheckerMaterial : public Material {
public:
    CheckerMaterial(const Color& color1, const Color& color2, float scale = 10.0f)
        : even_color(color1), odd_color(color2), inv_scale(1.0f / scale) {}

    virtual bool scatter(
        const Ray& r_in,
        const hit_record& rec,
        Color& attenuation,
        Ray& scattered
    ) const override {
        float x = rec.point.X() * inv_scale;
        float z = rec.point.Z() * inv_scale;

        int check = static_cast<int>(std::floor(x) + std::floor(z));

        if (check % 2 == 0) {
            attenuation = even_color;
        } else {
            attenuation = odd_color;
        }

        Vector scatter_direction = rec.normal + random_unit_vector();

        if (scatter_direction.length_squared() < 1e-8) {
            scatter_direction = rec.normal;
        }

        scattered = Ray(rec.point, scatter_direction);
        return true;
    }

private:
    Color even_color;
    Color odd_color;
    float inv_scale;
};