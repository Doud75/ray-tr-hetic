#include "Camera.hpp"
#include <cmath>
#include "Utils.hpp"
#include <iostream>
#include <thread>
#include <vector>
#include <functional>

Camera::Camera(int width, int height, int samples, float vertical_fov_degrees)
    : image_width(width), image_height(height), samples_per_pixel(samples)
{
    const float aspect_ratio = (float)image_width / image_height;
    const float focal_length = 1.0f;

    const float theta = vertical_fov_degrees * (M_PI / 180.0f);

    const float h = tan(theta / 2.0f);
    const float viewport_height = 2.0f * h * focal_length;
    const float viewport_width = viewport_height * aspect_ratio;

    camera_center = Vector(0.0f, 1.0f, 1.0f);

    const Vector viewport_u(viewport_width, 0, 0);
    const Vector viewport_v(0, -viewport_height, 0);

    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    const Vector viewport_upper_left = camera_center - Vector(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v) * 0.5;
}

void Camera::render_lines(const Scene& scene, Image& image, std::atomic<int>& next_line) {
    const int max_bounce = 10;

    while (true) {
        int j = next_line++;

        if (j >= image_height) return;

        for (int i = 0; i < image_width; ++i) {
            Color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                const Vector pixel_center = pixel00_loc + (pixel_delta_u * i) + (pixel_delta_v * j);
                const auto px_offset = (pixel_delta_u * (random_double() - 0.5)) + (pixel_delta_v * (random_double() - 0.5));
                const Vector sample_point = pixel_center + px_offset;
                const Vector ray_direction = sample_point - camera_center;
                Ray r(camera_center, ray_direction);

                pixel_color += scene.ray_color(r, max_bounce);
            }

            image.SetPixel(i, j, pixel_color / samples_per_pixel);
        }
    }
}

void Camera::render(const Scene& scene, Image& image) {
    const unsigned int num_threads = std::thread::hardware_concurrency();
    std::cout << "Utilisation de " << num_threads << " threads." << std::endl;

    std::vector<std::thread> threads;
    std::atomic<int> next_line(0);

    for (unsigned int t = 0; t < num_threads; ++t) {
        threads.emplace_back(
            &Camera::render_lines, this,
            std::cref(scene),
            std::ref(image),
            std::ref(next_line)
        );
    }

    for (auto& thread : threads) {
        thread.join();
    }
}