#pragma once

#include "Vector.hpp"
#include "Ray.hpp"
#include "Color.hpp"
#include <memory>

class Material; 

struct hit_record {
    Vector point;
    Vector normal;
    float t;
    bool front_face;
    std::shared_ptr<Material> mat; 
    

    void set_face_normal(const Ray& ray, const Vector& outward_normal);
};

class Hittable {
public:
    virtual ~Hittable() = default;
    
    virtual bool hit(const Ray& ray,
                     float t_min,
                     float t_max,
                     hit_record& rec) const = 0;
};

