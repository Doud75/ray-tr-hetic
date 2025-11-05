#include "Cube.hpp"
#include <cmath>
#include <algorithm>
#include <limits>

Cube::Cube(const Vector& minCorner, const Vector& maxCorner)
    : minCorner(minCorner), maxCorner(maxCorner) {}

bool Cube::hit(const Ray& ray, float t_min, float t_max, hit_record& rec) const {
    // Méthode des "slabs" pour un cube aligné sur les axes
    const Vector& O = ray.Origin();
    const Vector& D = ray.Direction();

    float t0 = t_min;
    float t1 = t_max;

    for (int i = 0; i < 3; i++) {
        float origin = (i == 0) ? O.X() : (i == 1) ? O.Y() : O.Z();
        float direction = (i == 0) ? D.X() : (i == 1) ? D.Y() : D.Z();
        float minC = (i == 0) ? minCorner.X() : (i == 1) ? minCorner.Y() : minCorner.Z();
        float maxC = (i == 0) ? maxCorner.X() : (i == 1) ? maxCorner.Y() : maxCorner.Z();

        if (std::fabs(direction) < 1e-8f) {
            // Rayon parallèle à cet axe → aucune intersection si en dehors des limites
            if (origin < minC || origin > maxC)
                return false;
        } else {
            float invD = 1.0f / direction;
            float tNear = (minC - origin) * invD;
            float tFar  = (maxC - origin) * invD;
            if (tNear > tFar) std::swap(tNear, tFar);

            t0 = std::max(tNear, t0);
            t1 = std::min(tFar, t1);

            if (t1 <= t0) return false;
        }
    }

    rec.t = t0;
    rec.point = ray.at(rec.t);

    // Calculer la normale de la face touchée
    const float eps = 1e-4f;
    Vector outward_normal(0.f, 0.f, 0.f);
    if (std::fabs(rec.point.X() - minCorner.X()) < eps) outward_normal = Vector(-1, 0, 0);
    else if (std::fabs(rec.point.X() - maxCorner.X()) < eps) outward_normal = Vector(1, 0, 0);
    else if (std::fabs(rec.point.Y() - minCorner.Y()) < eps) outward_normal = Vector(0, -1, 0);
    else if (std::fabs(rec.point.Y() - maxCorner.Y()) < eps) outward_normal = Vector(0, 1, 0);
    else if (std::fabs(rec.point.Z() - minCorner.Z()) < eps) outward_normal = Vector(0, 0, -1);
    else if (std::fabs(rec.point.Z() - maxCorner.Z()) < eps) outward_normal = Vector(0, 0, 1);

    rec.set_face_normal(ray, outward_normal);
    return true;
}
