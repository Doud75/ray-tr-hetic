#include "Ray.hpp"

Ray::Ray() {}

Ray::Ray(const Vector& origin, const Vector& direction)
    : origin(origin), direction(direction.normalized()) {} 

Ray::~Ray() {}

const Vector& Ray::Origin() const {
    return origin;
}

const Vector& Ray::Direction() const {
    return direction;
}

Vector Ray::at(float t) const {
    return origin + direction * t;
}
