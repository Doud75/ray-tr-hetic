#include "Plane.hpp"
#include "Color.hpp"
#include <cmath>

Plane::Plane(float y, float scale) 
    : y_position(y), checker_scale(scale) {}

bool Plane::hit(const Ray& ray, 
                float t_min, 
                float t_max, 
                hit_record& rec) const {
    
    const float ray_dir_y = ray.Direction().Y();
    if (std::abs(ray_dir_y) < 1e-8f) {
        return false;
    }

    const float t = (y_position - ray.Origin().Y()) / ray_dir_y;

    if (t <= t_min || t >= t_max) {
        return false;
    }

    rec.t = t;
    rec.point = ray.at(t);

    const Vector outward_normal(0.0f, 1.0f, 0.0f);
    rec.set_face_normal(ray, outward_normal);

    if (isWhiteSquare(rec.point.X(), rec.point.Z())) {
        rec.color = Color(0.9f, 0.9f, 0.9f);
    } else {
        rec.color = Color(0.2f, 0.2f, 0.2f);
    }

    return true;
}

bool Plane::isWhiteSquare(float x, float z) const {
    const int xi = static_cast<int>(std::floor(x / checker_scale));
    const int zi = static_cast<int>(std::floor(z / checker_scale));
    
    return ((xi + zi) % 2) == 0;
}

