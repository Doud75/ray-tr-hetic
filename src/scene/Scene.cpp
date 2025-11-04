#include "Scene.hpp"

Scene::Scene() {}

void Scene::add(std::shared_ptr<Hittable> object) {
    objects.push_back(object);
}

Color Scene::get_background_color(const Ray& r) const {
    Vector ray_direction = r.Direction();
    float a = 0.5f * (ray_direction.Y() + 1.0f);
    Color start_color = Color(1.0f, 1.0f, 1.0f);
    Color end_color = Color(0.1f, 0.7f, 1.0f);
    return start_color * (1.0f - a) + end_color * a;
}

Color Scene::ray_color(const Ray& r) const {
    hit_record rec;
    hit_record closest_rec;
    float closest_t = 1e30f;
    bool hit_anything = false;

    for (const auto& object : objects) {
        if (object->hit(r, 0.001f, closest_t, rec)) {
            hit_anything = true;
            closest_t = rec.t;
            closest_rec = rec;
        }
    }

    if (hit_anything) {
        return closest_rec.color;
    }

    return get_background_color(r);
}