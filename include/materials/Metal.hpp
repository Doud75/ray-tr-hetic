#pragma once

#include "Material.hpp"
#include "../raymath/Utils.hpp"

class Metal : public Material {
public:
    Metal(const Color& a, float f)
        : albedo(a), fuzz(f < 1 ? f : 1) {} 

    virtual bool scatter(
        const Ray& r_in,
        const hit_record& rec,
        Color& attenuation,
        Ray& scattered
    ) const override 
    {
        
        Vector reflected = reflect(r_in.Direction().normalized(), rec.normal);

        scattered = Ray(rec.point, reflected + random_in_unit_sphere() * fuzz);

        attenuation = albedo;

        return (scattered.Direction().dot(rec.normal) > 0);
    }

private:
    Color albedo;  
    float fuzz;   
};
