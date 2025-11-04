#include <iostream>
#include <cmath>
#include "Color.hpp"

Color:: Color() : r(0), b(0), g(0)
{  
}

Color:: Color(float iR, float iG, float iB) : r(iR), g(iG), b(iB)
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

Color Color::operator+(Color const& col) {
  // For accumulation during sampling, don't clamp yet
  Color c;
  c.r = r + col.r;
  c.g = g + col.g;
  c.b = b + col.b;
  return c;
}

Color& Color::operator+=(Color const& col) {
  r += col.r;
  g += col.g;
  b += col.b;
  return *this;
}

Color& Color::operator=(Color const& col) {
  r = col.r;
  g = col.g;
  b = col.b;
  return *this;
}

Color Color::operator*(float t) const
{
  return Color(r * t, g * t, b * t);
}

Color Color::operator/(float t) const
{
  // Division for averaging samples
  return Color(r / t, g / t, b / t);
}

std::ostream & operator<<(std::ostream & _stream, Color const & col) {  
  return _stream << "(" << col.r << "," << col.g << "," << col.b << ")";
}