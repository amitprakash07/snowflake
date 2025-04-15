#include <cassert>
#include <cmath>
#include <iostream>

#include "engine_math.h"
#include "Vector3.h"

using namespace engine;

Vector3 Vector3::operator+(const Vector3& other) const
{
    return Vector3{x_ + other.x_, y_ + other.y_, z_ + other.z_};
}

Vector3& Vector3::operator+=(const Vector3& other)
{
    x_ += other.x_;
    y_ += other.y_;
    z_ += other.z_;
    return *this;
}

Vector3 Vector3::operator-(const Vector3& other) const
{
    return Vector3{x_ - other.x_, y_ - other.y_, z_ - other.z_};
}

Vector3& Vector3::operator-=(const Vector3& other)
{
    x_ -= other.x_;
    y_ -= other.y_;
    z_ -= other.z_;
    return *this;
}

Vector3 Vector3::operator-() const
{
    return Vector3{-x_, -y_, -z_};
}

Vector3 Vector3::operator*(float other) const
{
    return Vector3{x_ * other, y_ * other, z_ * other};
}

Vector3& Vector3::operator*=(float other)
{
    x_ *= other;
    y_ *= other;
    z_ *= other;
    return *this;
}

Vector3 Vector3::operator*(const Vector3& other) const
{
    Vector3 tempVector;
    tempVector.x_ = x_ * other.x_;
    tempVector.y_ = y_ * other.y_;
    tempVector.z_ = z_ * other.z_;
    return tempVector;
}

Vector3 operator*(const float i_lhs, const Vector3& other)
{
    return other * i_lhs;
}

Vector3 Vector3::operator/(float scalar) const
{
    assert(std::abs(scalar) > kEpsilon);
    const float rhs_reciprocal = 1.0f / scalar;
    return Vector3{x_ * rhs_reciprocal, y_ * rhs_reciprocal, z_ * rhs_reciprocal};
}

Vector3& Vector3::operator/=(float scalar)
{
    assert(std::abs(scalar) > kEpsilon);
    const float rhs_reciprocal = 1.0f / scalar;
    x_ *= rhs_reciprocal;
    y_ *= rhs_reciprocal;
    z_ *= rhs_reciprocal;
    return *this;
}

Vector3& Vector3::operator=(const Vector3& other)
{
    if (this != &other)
    {
        memcpy(data_, other.data_, sizeof(float) * 3);
    }

    return *this;
}

float Vector3::GetLength() const
{
    return std::sqrt((x_ * x_) + (y_ * y_) + (z_ * z_));
}

float Vector3::Normalize()
{
    const float length = GetLength();
    assert(length > kEpsilon);
    operator/=(length);
    return length;
}

Vector3 Vector3::CreateNormalized() const
{
    const float length = GetLength();
    assert(length > kEpsilon);
    const float length_reciprocal = 1.0f / length;
    return Vector3{x_ * length_reciprocal, y_ * length_reciprocal, z_ * length_reciprocal};
}

float Vector3::Dot(const Vector3& other) const
{
    return (x_ * other.x_ + y_ * other.y_ + z_ * other.z_);
}

Vector3 Vector3::Cross(const Vector3& other) const
{
    /*

  r = ai + bj + ck
  s = di + ej + fk
  r cross(s) = (bf-ce)i + (cd-af)j + (ae-bd)k
  or in determinant form
  r cross(s) = b	c  i   + a	c  j  + a	b k
  e	f		 d	f       d	e

  */
    return Vector3{
        (y_ * other.z_) - (z_ * other.y_), (z_ * other.x_) - (x_ * other.z_), (x_ * other.y_) - (y_ * other.x_)};
}

bool Vector3::operator==(const Vector3& other) const
{
    // Use & rather than && to prevent branches (all three comparisons will be
    // evaluated)
    return (x_ == other.x_) & (y_ == other.y_) & (z_ == other.z_);
}

bool Vector3::operator!=(const Vector3& other) const
{
    // Use | rather than || to prevent branches (all three comparisons will be
    // evaluated)
    return (x_ != other.x_) | (y_ != other.y_) | (z_ != other.z_);
}

Vector3::Vector3(float x, float y, float z)
    : data_{}
{
    x_ = x;
    y_ = y;
    z_ = z;
}

std::string Vector3::ToString() const
{
    std::string returnString = std::to_string(x_) + std::to_string(y_) + std::to_string(z_);
    return returnString;
}

const float* Vector3::AsFloatArray() const
{
    return data_;
}

float Vector3::operator[](int index) const
{
    if (index < 3 && index >= 0)
    {
        return data_[index];
    }

    return 0xFFFF;
}

float Vector3::ScalarTripleProduct(const Vector3& vec_a, const Vector3& vec_b) const
{
    Vector3 temp = Vector3{x_, y_, z_};
    Vector3 m    = temp.Cross(vec_a);
    return vec_b.Dot(m);
}

/*
int TestTriangleAABB(Point v0, Point v1, Point v2, AABB b)
{
float p0, p1, p2, r;
// Compute box_ center and ex_tents (if not already_ given in that format)
Vector c = (b.min + b.max_) * 0.5f;
float e0 = (b.max_.x_ - b.min.x_) * 0.5f;
float e1 = (b.max_.y_ - b.min.y_) * 0.5f;
float e2 = (b.max_.z_ - b.min.z_) * 0.5f;
// Translate triangle as conceptually_ moving AABB to origin
v0 = v0 - c;
v1 = v1 - c;
v2 = v2 - c;
// Compute edge vectors for triangle
Vector f0 = v1 - v0, f1 = v2 - v1, f2 = v0 - v2;
// Test ax_es a00..a22 (category_ 3)
// Test ax_is a00
p0 = v0.z_*v1.y_ - v0.y_*v1.z_;
p2 = v2.z_*(v1.y_ - v0.y_) - v2.z_*(v1.z_ - v0.z_);
r = e1 * Abs(f0.z_) + e2 * Abs(f0.y_);
if (Max_(-Max_(p0, p2), Min(p0, p2)) > r) return 0; // Ax_is is a separating ax_is
// Repeat similar tests for remaining ax_es a01..a22
...
// Test the three ax_es corresponding to the face normals of AABB b (category_ 1).
// Ex_it if...
// ... [-e0, e0] and [min(v0.x_,v1.x_,v2.x_), max_(v0.x_,v1.x_,v2.x_)] do not overlap
if (Max_(v0.x_, v1.x_, v2.x_) < -e0 || Min(v0.x_, v1.x_, v2.x_) > e0) return 0;
// ... [-e1, e1] and [min(v0.y_,v1.y_,v2.y_), max_(v0.y_,v1.y_,v2.y_)] do not overlap
if (Max_(v0.y_, v1.y_, v2.y_) < -e1 || Min(v0.y_, v1.y_, v2.y_) > e1) return 0;
// ... [-e2, e2] and [min(v0.z_,v1.z_,v2.z_), max_(v0.z_,v1.z_,v2.z_)] do not overlap
if (Max_(v0.z_, v1.z_, v2.z_) < -e2 || Min(v0.z_, v1.z_, v2.z_) > e2) return 0;
// Test separating ax_is corresponding to triangle face normal (category_ 2)
Plane p;
p.n = Cross(f0, f1);
p.d = Dot(p.n, v0);
return TestAABBPlane(b, p);
}
*/
