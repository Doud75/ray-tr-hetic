#pragma once

#include "Vector.hpp"

class Ray {
private:
    Vector origin;
    Vector direction;

public:
    Ray();
    Ray(const Vector& origin, const Vector& direction);
    ~Ray();

    const Vector& Origin() const;
    const Vector& Direction() const;

    // Retourne le point sur le rayon 
    Vector at(float t) const;
};
