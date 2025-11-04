#pragma once

#include "../image/Image.hpp"
#include "../scene/Scene.hpp"

class Camera {
public:
    Camera(int image_width, int image_height);

    void render(const Scene& scene, Image& image);

private:
    int image_width;
    int image_height;

    Vector camera_center;
    Vector pixel00_loc;
    Vector pixel_delta_u;
    Vector pixel_delta_v;
};