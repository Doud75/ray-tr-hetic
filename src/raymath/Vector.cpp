#include "Vector.hpp"
#include <cmath>

Vector::Vector() {}

Vector::Vector(float x, float y, float z) : x(x), y(y), z(z) {}

Vector::~Vector() {}

float Vector::X() const { return x; }
float Vector::Y() const { return y; }
float Vector::Z() const { return z; }

Vector Vector::operator+(const Vector& other) const {
    return Vector(x + other.x, y + other.y, z + other.z);
}

Vector Vector::operator-(const Vector& other) const {
    return Vector(x - other.x, y - other.y, z - other.z);
}

Vector Vector::operator*(float t) const {
    return Vector(x * t, y * t, z * t);
}

Vector Vector::operator/(float t) const {
    return Vector(x / t, y / t, z / t);
}

Vector& Vector::operator+=(const Vector& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector& Vector::operator-=(const Vector& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vector& Vector::operator*=(float t) {
    x *= t;
    y *= t;
    z *= t;
    return *this;
}

Vector& Vector::operator/=(float t) {
    return *this *= 1/t;
}

float Vector::length_squared() const {
    return x*x + y*y + z*z;
}

float Vector::length() const {
    return std::sqrt(length_squared());
}

Vector Vector::normalized() const {
    float len_squared = length_squared();

    if (len_squared > 1e-8f) {
        float len = std::sqrt(len_squared);
        return Vector(x / len, y / len, z / len);
    }

    return Vector(0, 0, 0);
}

float Vector::dot(const Vector& other) const {
    return x * other.x + y * other.y + z * other.z;
}

Vector Vector::cross(const Vector& other) const {
    return Vector(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

std::ostream& operator<<(std::ostream& stream, const Vector& vec) {
    stream << "Vector(" << vec.X() << ", " << vec.Y() << ", " << vec.Z() << ")";
    return stream;
}