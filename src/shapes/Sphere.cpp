#include <cmath>
#include "Sphere.hpp"

// ||O + tD - C||^2 = R^2
// a = dot(D,D)
// half_b = dot(OC, D) avec OC = O - C
// c = dot(OC,OC) - R^2
// Δ = half_b^2 - a*c
bool Sphere::hit(const Ray& r, float t_min, float t_max, HitInfo& outHit) const {
  const Vector oc     = r.Origin() - center;
  const float  a      = r.Direction().dot(r.Direction()); // <-- a.dot(b)
  const float  half_b = oc.dot(r.Direction());            // <-- a.dot(b)
  const float  c      = oc.dot(oc) - radius * radius;     // <-- a.dot(b)

  const float discriminant = half_b * half_b - a * c;
  if (discriminant < 0.f) return false;

  const float sqrtD = std::sqrt(discriminant);

  // plus petite racine valide
  float root = (-half_b - sqrtD) / a;
  if (root < t_min || root > t_max) {
    root = (-half_b + sqrtD) / a;
    if (root < t_min || root > t_max) return false;
  }

  outHit.t      = root;
  outHit.point  = r.at(root);
  outHit.normal = (outHit.point - center).normalized(); // ou Normalize() selon ta classe
  return true;
}
