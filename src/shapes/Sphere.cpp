#include "Sphere.hpp"
#include <cmath>

Sphere::Sphere(const Vector& center, float r, std::shared_ptr<Material> mat)
    : center(center), radius(r), material(mat) {}

bool Sphere::hit(const Ray& ray, float t_min, float t_max, hit_record& rec) const {
    const Vector oc = ray.Origin() - center;
    const float a = ray.Direction().length_squared();
    const float half_b = oc.dot(ray.Direction());
    const float c = oc.length_squared() - radius * radius;

    const float discriminant = half_b * half_b - a * c;
    if (discriminant < 0) {
        return false;
    }

    const float sqrtD = std::sqrt(discriminant);

    float root = (-half_b - sqrtD) / a;
    if (root <= t_min || root >= t_max) {
        root = (-half_b + sqrtD) / a;
        if (root <= t_min || root >= t_max) {
            return false;
        }
    }

    rec.t = root;
    rec.point = ray.at(rec.t);
    Vector outward_normal = (rec.point - center) / radius;
    rec.set_face_normal(ray, outward_normal);
    rec.material = material;

    return true;
}