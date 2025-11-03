#pragma once
#include "../raymath/Vector.hpp"
#include "../raymath/Color.hpp"
#include "../raymath/Ray.hpp"

// Infos d'intersection
struct HitInfo {
  float  t;       // distance le long du rayon
  Vector point;   // point d'impact
  Vector normal;  // normale (unitaire)
};

class Sphere {
public:
  Vector center;
  float  radius;
  Color  albedo; // couleur de base

  Sphere(const Vector& c, float r, const Color& a = Color(1.f, 0.f, 0.f))
    : center(c), radius(r), albedo(a) {}

  // Test d'intersection rayon-sphère dans [t_min, t_max]
  bool hit(const Ray& r, float t_min, float t_max, HitInfo& outHit) const;
};
