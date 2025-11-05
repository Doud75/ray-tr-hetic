#pragma once
#include "Material.hpp"
#include "Ray.hpp"
#include "Color.hpp"

class DummyMaterial : public Material {
public:
    virtual bool scatter(
        const Ray& r_in,
        const hit_record& rec,
        Color& attenuation,
        Ray& scattered
    ) const override {
        attenuation = Color(1, 1, 1);       
        scattered = Ray(rec.point, Vector(0, 0, 1)); // rayon arbitraire
        return true;
    }
};