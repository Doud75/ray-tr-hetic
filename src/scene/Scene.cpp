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

    if (hit_anything(r, 0.001f, 1e30f, rec)) {
        Vector N = rec.normal;
        return Color(
            0.5f * (N.X() + 1.0f),
            0.5f * (N.Y() + 1.0f),
            0.5f * (N.Z() + 1.0f)
        );
    }

    return get_background_color(r);
}



bool Scene::hit_anything(const Ray& r, float t_min, float t_max, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    float closest_so_far = t_max;

    for (const auto& object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    if (hit_anything) {
        return closest_rec.color;
    }

    return hit_anything;
}