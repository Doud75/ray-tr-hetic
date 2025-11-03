#pragma once

#include "../raymath/Ray.hpp"
#include "../raymath/Color.hpp"

class Scene{
public:
    Scene();

    Color get_background_color(const Ray& r) const;
};
