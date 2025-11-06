#pragma once

#include <vector>
#include <memory>
#include <functional>
#include "../raymath/Ray.hpp"
#include "../raymath/Color.hpp"
#include "../raymath/Hittable.hpp"

using SkyFunction = std::function<Color(const Ray&)>;

class Scene {
public:
    Scene(SkyFunction sky);
    void add(std::shared_ptr<Hittable> object);
    Color ray_color(const Ray& r, int bounce) const;

private:
    std::vector<std::shared_ptr<Hittable>> objects;
    SkyFunction background_sky;

    bool hit_anything(const Ray& r, float t_min, float t_max, hit_record& rec) const;
};