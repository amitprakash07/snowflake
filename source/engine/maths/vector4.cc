// Header Files
//=============

#include <cassert>
#include <cmath>
#include <iostream>

#include "Vec4.h"

// Static Data Initialization
//===========================

namespace {
const float s_epsilon = 1.0e-9f;
}

// Interface
//==========

// Addition
Math::Vector4 Math::Vector4::operator+(
    const Vector4& i_rhs) const {
  return Vector4(x + i_rhs.x, y + i_rhs.y, z + i_rhs.z, w + i_rhs.w);
}

Math::Vector4& Math::Vector4::operator+=(const Vector4& i_rhs) {
  x += i_rhs.x;
  y += i_rhs.y;
  z += i_rhs.z;
  w += i_rhs.w;
  return *this;
}

// Subtraction / Negation
Math::Vector4 Math::Vector4::operator-(
    const Vector4& i_rhs) const {
  return Vector4(x - i_rhs.x, y - i_rhs.y, z - i_rhs.z, w - i_rhs.w);
}

Math::Vector4& Math::Vector4::operator-=(const Vector4& i_rhs) {
  x -= i_rhs.x;
  y -= i_rhs.y;
  z -= i_rhs.z;
  w -= i_rhs.w;
  return *this;
}

Math::Vector4 Math::Vector4::operator-() const {
  return Vector4(-x, -y, -z, -w);
}

// Multiplication
Math::Vector4 Math::Vector4::operator*(
    const float i_rhs) const {
  return Vector4(x * i_rhs, y * i_rhs, z * i_rhs, w * i_rhs);
}

Math::Vector4& Math::Vector4::operator*=(const float i_rhs) {
  x *= i_rhs;
  y *= i_rhs;
  z *= i_rhs;
  w *= i_rhs;
  return *this;
}

Math::Vector4 operator*(const float i_lhs,
                                const Math::Vector4& i_rhs) {
  return i_rhs * i_lhs;
}

// Division
Math::Vector4 Math::Vector4::operator/(
    const float i_rhs) const {
  assert(std::abs(i_rhs) > s_epsilon);
  const float rhs_reciprocal = 1.0f / i_rhs;
  return Vector4(x * rhs_reciprocal, y * rhs_reciprocal, z * rhs_reciprocal,
                 w * rhs_reciprocal);
}

Math::Vector4& Math::Vector4::operator/=(const float i_rhs) {
  assert(std::abs(i_rhs) > s_epsilon);
  const float rhs_reciprocal = 1.0f / i_rhs;
  x *= rhs_reciprocal;
  y *= rhs_reciprocal;
  z *= rhs_reciprocal;
  w *= rhs_reciprocal;
  return *this;
}

// Length / Normalization
float Math::Vector4::GetLength() const {
  return std::sqrt((x * x) + (y * y) + (z * z) + (w * w));
}

float Math::Vector4::Normalize() {
  const float length = GetLength();
  assert(length > s_epsilon);
  operator/=(length);
  return length;
}

Math::Vector4 Math::Vector4::CreateNormalized() const {
  const float length = GetLength();
  assert(length > s_epsilon);
  const float length_reciprocal = 1.0f / length;
  return Vector4(x * length_reciprocal, y * length_reciprocal,
                 z * length_reciprocal, w * length_reciprocal);
}

// Products
float Math::Vector4::dot(const Vector4& i_rhs) const {
  return (x * i_rhs.x + y * i_rhs.y + z * i_rhs.z, w * i_rhs.w);
}

// Comparison
bool Math::Vector4::operator==(const Vector4& i_rhs) const {
  // Use & rather than && to prevent branches (all three comparisons will be
  // evaluated)
  return (x == i_rhs.x) & (y == i_rhs.y) & (z == i_rhs.z) & (z == i_rhs.w);
}

bool Math::Vector4::operator!=(const Vector4& i_rhs) const {
  // Use | rather than || to prevent branches (all three comparisons will be
  // evaluated)
  return (x != i_rhs.x) | (y != i_rhs.y) | (z != i_rhs.z) | (w != i_rhs.w);
}

// Initialization / Shut Down
//---------------------------

Math::Vector4::Vector4(const float i_x, const float i_y,
                               const float i_z, const float i_w)
    : x(i_x), y(i_y), z(i_z), w(i_w) {}

std::string Math::Vector4::toString() const {
  std::string returnString;
  returnString = std::to_string(x) + std::to_string(y) + std::to_string(z);
  return returnString;
}

float* Math::Vector4::toFloatArray() const {
  float floatArray[4];
  floatArray[0] = x;
  floatArray[1] = y;
  floatArray[2] = z;
  floatArray[3] = w;
  return floatArray;
}

void Math::Vector4::printVector() const {
  std::cout << "x = " << x << ", y = " << y << ", z= " << z;
  std::cout << std::endl;
}
