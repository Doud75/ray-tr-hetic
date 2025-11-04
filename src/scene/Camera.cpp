#include "Camera.hpp"
#include <cmath>

Camera::Camera(int width, int height, float vertical_fov_degrees)
    : image_width(width), image_height(height)
{
    const float aspect_ratio = (float)image_width / image_height;
    const float focal_length = 1.0f;

    const float theta = vertical_fov_degrees * (M_PI / 180.0f);

    const float h = tan(theta / 2.0f);
    const float viewport_height = 2.0f * h * focal_length;
    const float viewport_width = viewport_height * aspect_ratio;

    camera_center = Vector(0.0f, 0.0f, -1.0f);

    const Vector viewport_u(viewport_width, 0, 0);
    const Vector viewport_v(0, -viewport_height, 0);

    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    const Vector viewport_upper_left = camera_center - Vector(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v) * 0.5;
}

void Camera::render(const Scene& scene, Image& image) {
    for (int j = 0; j < image_height; ++j) {
        for (int i = 0; i < image_width; ++i) {
            const Vector pixel_center = pixel00_loc + (pixel_delta_u * i) + (pixel_delta_v * j);
            const Vector ray_direction = pixel_center - camera_center;
            Ray r(camera_center, ray_direction);

            Color pixel_color = scene.ray_color(r);

            image.SetPixel(i, j, pixel_color);
        }
    }
}