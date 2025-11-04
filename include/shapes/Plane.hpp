#pragma once

#include "../raymath/Hittable.hpp"
#include "../raymath/Vector.hpp"
#include "../materials/Material.hpp"
#include <memory>

class Plane : public Hittable {
public:
    Plane(float y, 
          std::shared_ptr<Material> mat1, 
          std::shared_ptr<Material> mat2,
          float scale = 1.0f);

    bool hit(const Ray& ray, 
             float t_min, 
             float t_max, 
             hit_record& rec) const override;

    bool isWhiteSquare(float x, float z) const;

private:
    float y_position;
    float checker_scale;
    std::shared_ptr<Material> material1;
    std::shared_ptr<Material> material2;
};

