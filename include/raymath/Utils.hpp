#pragma once

#include <random>
#include "Vector.hpp"

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline Vector random_vector() {
    return Vector(random_double() * 2 - 1, random_double() * 2 - 1, random_double() * 2 - 1);
}

inline Vector random_in_unit_sphere() {
    while (true) {
        auto p = random_vector();
        if (p.length_squared() < 1) {
            return p;
        }
    }
}

inline Vector random_unit_vector() {
    return random_in_unit_sphere().normalized();
}