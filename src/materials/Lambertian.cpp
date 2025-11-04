#include "Lambertian.hpp"
#include "../raymath/Vector.hpp"

Lambertian::Lambertian(const Color& a) : albedo(a) {}

bool Lambertian::scatter(
    const Ray& ray_in,
    const hit_record& rec,
    Color& attenuation,
    Ray& scattered
) const {
    Vector scatter_direction = rec.normal + Vector(
        ((float)rand() / RAND_MAX) * 2.0f - 1.0f,
        ((float)rand() / RAND_MAX) * 2.0f - 1.0f,
        ((float)rand() / RAND_MAX) * 2.0f - 1.0f
    ).normalized();
    
    if (scatter_direction.length_squared() < 1e-8f) {
        scatter_direction = rec.normal;
    }
    
    scattered = Ray(rec.point, scatter_direction);
    attenuation = albedo;
    return true;
}

