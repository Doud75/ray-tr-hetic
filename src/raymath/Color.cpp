#include <iostream>
#include <cmath>
#include "Color.hpp"

Color::Color() : r(0), b(0), g(0)
{
}

Color::Color(float iR, float iG, float iB) : r(iR), g(iG), b(iB)
{
}

Color::~ Color()
{
}

float Color::R()
{
    return r;
}

float Color::G()
{
    return g;
}

float Color::B()
{
    return b;
}

Color Color::operator+(Color const& col) const
{
    return Color(r + col.r, g + col.g, b + col.b);
}

Color& Color::operator+=(const Color& other)
{
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
}

Color& Color::operator=(Color const& col)
{
    r = col.r;
    g = col.g;
    b = col.b;
    return *this;
}

Color Color::operator*(float t) const
{
    return Color(r * t, g * t, b * t);
}

Color Color::operator*(const Color& other) const {
    return Color(r * other.r, g * other.g, b * other.b);
}

Color Color::operator/(float t) const
{
    return Color(r / t, g / t, b / t);
}

std::ostream& operator<<(std::ostream& _stream, Color const& col)
{
    return _stream << "(" << col.r << "," << col.g << "," << col.b << ")";
}
