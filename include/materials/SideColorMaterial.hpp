#pragma once

#include "Material.hpp"
#include "../raymath/Utils.hpp"
#include <cmath>

class SideColorMaterial : public Material {
public:
    SideColorMaterial(const Color& front_back_color, const Color& other_faces_color)
        : albedo_front_back(front_back_color), albedo_others(other_faces_color) {}

    virtual bool scatter(
        const Ray& r_in,
        const hit_record& rec,
        Color& attenuation,
        Ray& scattered
    ) const override {

        Color chosen_albedo;

        if (std::abs(rec.normal.Z()) > 0.9f) {
            chosen_albedo = albedo_front_back;
        } else {
            chosen_albedo = albedo_others;
        }

        auto scatter_direction = rec.normal + random_unit_vector();

        if (scatter_direction.length_squared() < 1e-8) {
            scatter_direction = rec.normal;
        }

        scattered = Ray(rec.point, scatter_direction);
        attenuation = chosen_albedo;
        return true;
    }

private:
    Color albedo_front_back;
    Color albedo_others;
};