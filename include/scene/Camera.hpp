#pragma once

#include "../image/Image.hpp"
#include "../scene/Scene.hpp"
#include <atomic>

class Camera {
public:
    Camera(int image_width, int image_height, int samples_per_pixel, float vertical_fov_degrees = 90.0f);

    void render(const Scene& scene, Image& image);

    int image_width;
    int image_height;
private:
    int samples_per_pixel;

    Vector camera_center;
    Vector pixel00_loc;
    Vector pixel_delta_u;
    Vector pixel_delta_v;

    void render_row(const Scene& scene, Image& image, int start, int end, std::atomic<int>& progress_counter);
};