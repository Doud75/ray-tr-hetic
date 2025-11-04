#include "Camera.hpp"
#include <cstdlib>

Camera::Camera(int width, int height, int samples)
    : image_width(width), image_height(height), 
      samples_per_pixel(samples)
{
    const float aspect_ratio = (float)image_width / image_height;

    const float viewport_height = 2.0f;
    const float viewport_width = viewport_height * aspect_ratio;
    const float focal_length = 1.0f;

    camera_center = Vector(0.0f, 0.0f, 0.0f);

    const Vector viewport_u(viewport_width, 0, 0);
    const Vector viewport_v(0, -viewport_height, 0);

    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    const Vector viewport_upper_left = camera_center - Vector(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v) * 0.5;
}

Vector Camera::get_ray_direction(int i, int j) const {
    // Generate random offset within the pixel for anti-aliasing
    float random_u = ((float)rand() / RAND_MAX) - 0.5f;
    float random_v = ((float)rand() / RAND_MAX) - 0.5f;
    
    const Vector pixel_sample = pixel00_loc 
                               + (pixel_delta_u * (i + random_u)) 
                               + (pixel_delta_v * (j + random_v));
    
    return pixel_sample - camera_center;
}

void Camera::render(const Scene& scene, Image& image) {
    const int max_depth = 50;
    
    for (int j = 0; j < image_height; ++j) {
        for (int i = 0; i < image_width; ++i) {
            Color accumulated_color(0.0f, 0.0f, 0.0f);
            
            // Shoot multiple rays per pixel for anti-aliasing
            for (int sample = 0; sample < samples_per_pixel; ++sample) {
                Vector ray_direction = get_ray_direction(i, j);
                Ray r(camera_center, ray_direction);
                
                Color sample_color = scene.ray_color(r, max_depth);
                accumulated_color += sample_color;
            }
            
            // Average the samples
            Color pixel_color = accumulated_color / samples_per_pixel;
            
            image.SetPixel(i, j, pixel_color);
        }
    }
}