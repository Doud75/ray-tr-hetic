#pragma once

#include <vector>
#include <memory>
#include "../raymath/Ray.hpp"
#include "../raymath/Color.hpp"
#include "../raymath/Hittable.hpp"

class Scene {
public:
    Scene();
    void add(std::shared_ptr<Hittable> object);
    Color ray_color(const Ray& r, int depth) const;

private:
    std::vector<std::shared_ptr<Hittable>> objects;
    Color get_background_color(const Ray& r) const;
};