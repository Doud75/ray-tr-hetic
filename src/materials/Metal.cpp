#include "Metal.hpp"
#include "../raymath/Vector.hpp"

Metal::Metal(const Color& a, float f) : albedo(a), fuzz(f < 1.0f ? f : 1.0f) {}

Vector reflect(const Vector& v, const Vector& n) {
    return v - n * (2.0f * v.dot(n));
}

Vector random_in_unit_sphere() {
    Vector p;
    do {
        p = Vector(
            ((float)rand() / RAND_MAX) * 2.0f - 1.0f,
            ((float)rand() / RAND_MAX) * 2.0f - 1.0f,
            ((float)rand() / RAND_MAX) * 2.0f - 1.0f
        );
    } while (p.length_squared() >= 1.0f);
    return p;
}

bool Metal::scatter(
    const Ray& ray_in,
    const hit_record& rec,
    Color& attenuation,
    Ray& scattered
) const {
    // ray_in.Direction() is already normalized by Ray constructor
    Vector reflected = reflect(ray_in.Direction(), rec.normal);
    scattered = Ray(rec.point, reflected + random_in_unit_sphere() * fuzz);
    attenuation = albedo;
    return (scattered.Direction().dot(rec.normal) > 0);
}

