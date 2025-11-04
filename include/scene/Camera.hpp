#pragma once

#include "../image/Image.hpp"
#include "../scene/Scene.hpp"

class Camera {
public:
    Camera(int image_width, int image_height, int samples = 10);

    void render(const Scene& scene, Image& image);

private:
    int image_width;
    int image_height;
    int samples_per_pixel;

    Vector camera_center;
    Vector pixel00_loc;
    Vector pixel_delta_u;
    Vector pixel_delta_v;

    // Helper function to generate random offset within pixel
    Vector get_ray_direction(int i, int j) const;
};