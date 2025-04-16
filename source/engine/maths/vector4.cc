#include <cassert>
#include <cmath>
#include <iostream>

#include "vector4.h"

#include "engine_math.h"

using namespace engine;

Vector4 Vector4::operator+(const Vector4& other) const
{
    return Vector4{x_ + other.x_, y_ + other.y_, z_ + other.z_, w_ + other.w_};
}

Vector4& Vector4::operator+=(const Vector4& other)
{
    x_ += other.x_;
    y_ += other.y_;
    z_ += other.z_;
    w_ += other.w_;
    return *this;
}

Vector4 Vector4::operator-(const Vector4& other) const
{
    return Vector4{x_ - other.x_, y_ - other.y_, z_ - other.z_, w_ - other.w_};
}

Vector4& Vector4::operator-=(const Vector4& other)
{
    x_ -= other.x_;
    y_ -= other.y_;
    z_ -= other.z_;
    w_ -= other.w_;
    return *this;
}

Vector4 Vector4::operator-() const
{
    return Vector4{-x_, -y_, -z_, -w_};
}

Vector4 Vector4::operator*(float scalar) const
{
    return Vector4{x_ * scalar, y_ * scalar, z_ * scalar, w_ * scalar};
}

Vector4& Vector4::operator*=(float scalar)
{
    x_ *= scalar;
    y_ *= scalar;
    z_ *= scalar;
    w_ *= scalar;
    return *this;
}

Vector4 operator*(const float i_lhs, const Vector4& other)
{
    return other * i_lhs;
}

Vector4 Vector4::operator/(float scalar) const
{
    assert(std::abs(scalar) > kEpsilon);
    const float rhs_reciprocal = 1.0f / scalar;
    return Vector4{x_ * rhs_reciprocal, y_ * rhs_reciprocal, z_ * rhs_reciprocal, w_ * rhs_reciprocal};
}

Vector4& Vector4::operator/=(float scalar)
{
    assert(std::abs(scalar) > kEpsilon);
    const float rhs_reciprocal = 1.0f / scalar;
    x_ *= rhs_reciprocal;
    y_ *= rhs_reciprocal;
    z_ *= rhs_reciprocal;
    w_ *= rhs_reciprocal;
    return *this;
}

Vector4& Vector4::operator=(const Vector4& other)
{
    if (this != &other)
    {
        memcpy(data_, other.data_, sizeof(float) * 4);
    }

    return *this;
}

float Vector4::GetLength() const
{
    return std::sqrt((x_ * x_) + (y_ * y_) + (z_ * z_) + (w_ * w_));
}

void Vector4::Normalize()
{
    const float length = GetLength();
    assert(length > kEpsilon);
    operator/=(length);
}

Vector4 Vector4::GetNormalizedVec() const
{
    const float length = GetLength();
    assert(length > kEpsilon);
    const float length_reciprocal = 1.0f / length;
    return Vector4{x_ * length_reciprocal, y_ * length_reciprocal, z_ * length_reciprocal, w_ * length_reciprocal};
}

float Vector4::Dot(const Vector4& other) const
{
    return (x_ * other.x_ + y_ * other.y_ + z_ * other.z_ + w_ * other.w_);
}

bool Vector4::operator==(const Vector4& other) const
{
    return (x_ == other.x_) & (y_ == other.y_) & (z_ == other.z_) & (z_ == other.w_);
}

bool Vector4::operator!=(const Vector4& other) const
{
    return (x_ != other.x_) | (y_ != other.y_) | (z_ != other.z_) | (w_ != other.w_);
}

Vector4::Vector4(float x, float y, float z, float w)
    : data_{}
{
    x_ = x;
    y_ = y;
    z_ = z;
    w_ = w;
}

std::string Vector4::ToString() const
{
    std::string returnString = std::to_string(x_) + std::to_string(y_) + std::to_string(z_);
    return returnString;
}

const float* Vector4::AsFloatArray() const
{
    return data_;
}
