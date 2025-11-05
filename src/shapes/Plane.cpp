#include "Plane.hpp"
#include "Color.hpp"
#include <cmath>

Plane::Plane(float y, std::shared_ptr<Material> m)
    : y_position(y), mat(m) {}

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
    rec.mat = mat;

    return true;
}

