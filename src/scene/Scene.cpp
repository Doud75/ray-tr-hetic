#include "Scene.hpp"

Scene::Scene() {}

Color Scene::get_background_color(const Ray& r) const
{
    Vector ray_direction = r.Direction();

    float a = 0.5f * (ray_direction.Y() + 1.0f);

    Color start_color = Color(1.0f, 1.0f, 1.0f);
    Color end_color = Color(0.1f, 0.7f, 1.0f);

    return start_color * (1.0f - a) + end_color * a;
}

