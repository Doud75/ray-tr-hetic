#pragma once

#include <iostream>

class Vector {
private:
    float x = 0;
    float y = 0;
    float z = 0;

public:
    Vector();
    Vector(float x, float y, float z);
    ~Vector();

    float X() const;
    float Y() const;
    float Z() const;

    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(float t) const;
    Vector operator/(float t) const;

    Vector& operator+=(const Vector& other);
    Vector& operator-=(const Vector& other);
    Vector& operator*=(float t);
    Vector& operator/=(float t);

    float length() const;
    float length_squared() const;
    Vector normalized() const;
    float dot(const Vector& other) const;
    Vector cross(const Vector& other) const;

};

std::ostream& operator<<(std::ostream& stream, const Vector& vec);