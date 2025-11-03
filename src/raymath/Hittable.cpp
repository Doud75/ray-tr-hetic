#include "Hittable.hpp"

void hit_record::set_face_normal(const Ray& ray, const Vector& outward_normal) {
    float dot_product = ray.Direction().dot(outward_normal);
    
    front_face = (dot_product < 0.0f);
    
    if (front_face) {
        normal = outward_normal;
    } else {
        normal = Vector(0, 0, 0) - outward_normal;
    }
}

