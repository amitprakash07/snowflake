
#include <cassert>
#include <cmath>
#include <iostream>

#include "engine_math.h"
#include "Quaternion.h"

using namespace engine;

Quaternion::Quaternion()
    : w_(1.0f)
    , x_(0.0f)
    , y_(0.0f)
    , z_(0.0f)
{
    scalar = 1.0f;
    vector = Vector3(0.0f, 0.0f, 0.0f);
}

Quaternion Quaternion::GetIdentityQuaternion()
{
    return Quaternion{};
}

Quaternion& Quaternion::operator=(const Quaternion& other)
{
    w_     = other.w_;
    x_     = other.x_;
    y_     = other.y_;
    z_     = other.z_;
    scalar = other.scalar;
    vector = other.vector;
    return *this;
}

bool Quaternion::operator!=(const Quaternion& other) const
{
    return !(*this == other);
}

bool Quaternion::operator==(const Quaternion& other) const
{
    bool isEqual = (w_ == other.w_ && x_ == other.x_ && y_ == other.y_ && z_ == other.z_);
    return isEqual;
}

Quaternion Quaternion::Slerp(const Quaternion& from, const Quaternion& to, float interpolation_factor)
{
    /*
    Slerp formulae
    omega  - angular displacement between two quaternions
    Slerp(q1,q2,t) = ((sin(1-t)omega)/sin(omega))* q1 +
                               (sin(t*omega)/sin(omega)) *q2
    */

    Quaternion new_quaternion;

    Quaternion from_quaternion = from;

    // Omega angular displacement between two quaternions
    float cos_omega = from_quaternion.Dot(to);

    // If negative Dot, negate one of the input
    // quaternions to take the shorter 4D "arc"
    if (cos_omega < 0.0f)
    {
        from_quaternion = -from_quaternion;
        cos_omega       = -cos_omega;
    }

    // Checking if they are very close together to protect
    // against divide-by-zero
    float k0, k1;
    if (cos_omega > 0.9999f)
    {
        // Very close - just use linear interpolation
        k0 = 1.0f - interpolation_factor;
        k1 = interpolation_factor;
    }
    else
    {
        float sinOmega = sqrt(1.0f - cos_omega * cos_omega);

        // Computing the angle from_quaternion its sin and cosine
        float omega = atan2(sinOmega, cos_omega);

        // Compute inverse of denominator, so we only have
        // to divide once
        float oneOverSinOmega = 1.0f / sinOmega;

        // Compute interpolation parameters
        k0 = sin((1.0f - interpolation_factor) * omega) * oneOverSinOmega;
        k1 = sin(interpolation_factor * omega) * oneOverSinOmega;
    }

    // Interpolate
    new_quaternion.w_ = from_quaternion.w_ * k0 + to.w_ * k1;
    new_quaternion.x_ = from_quaternion.x_ * k0 + to.x_ * k1;
    new_quaternion.y_ = from_quaternion.y_ * k0 + to.y_ * k1;
    new_quaternion.z_ = from_quaternion.z_ * k0 + to.z_ * k1;
    new_quaternion.SplitToScalarVector();
    return new_quaternion;
}

// Getters
float Quaternion::w() const
{
    return w_;
}

float Quaternion::x() const
{
    return x_;
}

float Quaternion::y() const
{
    return y_;
}

float Quaternion::z() const
{
    return z_;
}

// Cross Product
Quaternion Quaternion::operator*(const Quaternion& other) const
{
    /*
  q1 = [s1, v1]
  q2 = [s2, v2]
  q1*q2 = [s1S2 - v1.v2, s1v2+s2v1+ v1.Cross(v2)]
  */
    return Quaternion((w_ * other.w_) - ((x_ * other.x_) + (y_ * other.y_) + (z_ * other.z_)),
                      (w_ * other.x_) + (x_ * other.w_) + ((y_ * other.z_) - (z_ * other.y_)),
                      (w_ * other.y_) + (y_ * other.w_) + ((z_ * other.x_) - (x_ * other.z_)),
                      (w_ * other.z_) + (z_ * other.w_) + ((x_ * other.y_) - (y_ * other.x_)));
}

// Cross Product
Quaternion Quaternion::cross(const Quaternion& other) const
{
    /*
  q1 = [s1, v1]
  q2 = [s2, v2]
  q1*q2 = [s1S2 - v1.v2, s1v2+s2v1+ v1.Cross(v2)]
  */
    Quaternion tempQuaternion;
    tempQuaternion.scalar = scalar * other.scalar + vector.Dot(other.vector);
    tempQuaternion.vector = vector * other.scalar + other.vector * scalar + vector.Cross(other.vector);
    tempQuaternion.SplitFromScalarVector();
    return tempQuaternion;
}

// Inverse
void Quaternion::Inverse()
{
    x_ = -x_;
    y_ = -y_;
    z_ = -z_;
}

// Create Inverse
Quaternion Quaternion::CreateInverse() const
{
    Quaternion tempQuartenion = Quaternion(w_, -x_, -y_, -z_);
    tempQuartenion.SplitToScalarVector();
    return tempQuartenion;
}

Quaternion Quaternion::operator-() const
{
    Quaternion negatedQuartenion;
    negatedQuartenion.w_ = -w_;
    negatedQuartenion.x_ = -x_;
    negatedQuartenion.y_ = -y_;
    negatedQuartenion.z_ = -z_;
    negatedQuartenion.SplitToScalarVector();
    return negatedQuartenion;
}

void Quaternion::Conjugate()
{
    x_ = -x_;
    y_ = -y_;
    z_ = -z_;
    SplitToScalarVector();
}

float Quaternion::Magnitude() const
{
    return sqrt(w_ * w_ + x_ * x_ + y_ * y_ + z_ * z_);
}

// NormalimZation
void Quaternion::Normalize()
{
    const float length = Magnitude();
    assert(length > kEpsilon);
    const float length_reciprocal = 1.0f / length;
    w_ *= length_reciprocal;
    x_ *= length_reciprocal;
    y_ *= length_reciprocal;
    z_ *= length_reciprocal;
    SplitToScalarVector();
}

Quaternion Quaternion::CreateNormalized() const
{
    const float length = Magnitude();
    assert(length > kEpsilon);
    const float length_reciprocal = 1.0f / length;
    Quaternion  tempQuaternion    = Quaternion(w_ * length_reciprocal, x_ * length_reciprocal, y_ * length_reciprocal, z_ * length_reciprocal);
    tempQuaternion.SplitToScalarVector();
    return tempQuaternion;
}

// angular Displacement
Quaternion Quaternion::AngularDisplacement(const Quaternion& other) const
{
    // Angular Displacement
    /*
  Given orientations a and b, we can compute the angular displacement
  d which rotates from a to b i.e.
  ad = b => d - difference = inverse(a)b
  */
    Quaternion difference;
    difference = this->CreateInverse() * other;
    difference.SplitToScalarVector();
    return difference;
}

Quaternion Quaternion::operator-(const Quaternion& other) const
{
    // Angular Displacement
    /*
  Given orientations a and b, we can compute the angular displacement
  d which rotates from a to b i.e.
  ad = b => d - difference = inverse(a)b
  */
    Quaternion difference;
    difference = this->CreateInverse() * other;
    difference.SplitToScalarVector();
    return difference;
}

Quaternion& Quaternion::operator-=(const Quaternion& other)
{
    Quaternion difference;
    difference = this->CreateInverse() * other;
    difference.SplitToScalarVector();
    w_ = difference.w_;
    x_ = difference.x_;
    y_ = difference.y_;
    z_ = difference.z_;
    this->SplitToScalarVector();
    return *this;
}

// Dot Product
float Quaternion::Dot(const Quaternion& other) const
{
    return (w_ * other.w_) + (x_ * other.x_) + (y_ * other.y_) + (z_ * other.z_);
}

// Exponent
Quaternion Quaternion::operator^(const float exponent) const
{
    /*
  Quaternion exponentiation is useful because it allows us to
  extract a “fraction” of an angular displacement.
  For example, to compute a quaternion that represents one-third
  of the angular displacement represented by the quaternion q,
  we would compute q1/3.

  The caveat we here is this: a quaternion represents angular displacements
  using the shortest arc. “Multiple spins” cannot be represented.
  For our example from above, q4 is not a 240º clockwise rotation about the
  x-axis as expected; it is an 80º counterclockwise rotation.
  */

    // Quaternion (input and output)
    Quaternion exponentResult;

    // Check for the case of an identity quaternion.
    // This will protect against divide by zero
    if (fabs(w_) < .9999f)
    {
        // Extracting the half angle alpha (alpha = theta/2)
        float alpha = acos(w_);
        // Compute new alpha value
        float newAlpha = alpha * exponent;
        // Compute new w value
        exponentResult.w_ = cos(newAlpha);
        // Compute new xyz values
        float mult        = sin(newAlpha) / sin(alpha);
        exponentResult.x_ = mult;
        exponentResult.y_ = mult;
        exponentResult.z_ = mult;
    }
    return exponentResult;
}

Quaternion::Quaternion(float angle_in_radians, const Vector3& axis_of_rotation)
{
    /*
  q = [cos(θ /2)+sin(θ /2) ˆu].
  mWhere u is the normalimZed arbitrary axis vector
  */
    if (axis_of_rotation.GetLength() > 0)
    {
        Vector3 axisOfRotation_normalized = axis_of_rotation.CreateNormalized();

        const float theta_half     = angle_in_radians * 0.5f;
        w_                         = std::cos(theta_half);
        const float sin_theta_half = std::sin(theta_half);
        x_                         = axisOfRotation_normalized.x() * sin_theta_half;
        y_                         = axisOfRotation_normalized.y() * sin_theta_half;
        z_                         = axisOfRotation_normalized.z() * sin_theta_half;
        SplitToScalarVector();
    }
    else
    {
        w_ = 1.0f;
        x_ = y_ = z_ = 0.0f;
        scalar       = 1.0f;
        vector       = Vector3(0.0f, 0.0f, 0.0f);
    }
}

// About rightVector(x-axis)
Quaternion Quaternion::GetPitch(float angle_in_radians)
{
    return Quaternion{angle_in_radians, Vector3(1.0f, 0.0f, 0.0f)};
}

// About forwardAxis (z-axis)
Quaternion Quaternion::GetRoll(float angle_in_radians)
{
    return Quaternion{angle_in_radians, Vector3(0.0f, 0.0f, 1.0f)};
}

// About upVector (y-axis)
Quaternion Quaternion::GetYaw(float angle_in_radians)
{
    return Quaternion{angle_in_radians, Vector3(0.0f, 1.0f, 0.0f)};
}

Quaternion Quaternion::GetYawPitchRoll(float yaw, float pitch, float roll)
{
    /*
  q = q(yaw)q(pitch)q(roll) = [s+xi+yj+zk]
  s = cos(yaw/2)cos(pitch/2)cos(roll/2) + sin(yaw/2) sin(pitch/2) sin(roll/2)
  x = cos(yaw/2) sin(pitch/2)cos(roll/2) + sin(yaw/2)cos(pitch/2) sin(roll/2)
  y = sin(yaw/2)cos(pitch/2)cos(roll/2) − cos(yaw/2) sin(pitch/2) sin(roll/2)
  z = cos(yaw/2)cos(pitch/2) sin(roll/2) − sin(yaw/2) sin(pitch/2)cos(roll/2)
  */
    Quaternion yawPitchRoll;
    yawPitchRoll.w_ = cos(yaw / 2) * cos(pitch / 2) * cos(roll / 2) + sin(yaw / 2) * sin(pitch / 2) * sin(roll / 2);
    yawPitchRoll.x_ = cos(yaw / 2) * sin(pitch / 2) * cos(roll / 2) + sin(yaw / 2) * cos(pitch / 2) * sin(roll / 2);
    yawPitchRoll.y_ = sin(yaw / 2) * cos(pitch / 2) * cos(roll / 2) - cos(yaw / 2) * sin(pitch / 2) * sin(roll / 2);
    yawPitchRoll.z_ = cos(yaw / 2) * cos(pitch / 2) * sin(roll / 2) - sin(yaw / 2) * sin(pitch / 2) * cos(roll / 2);
    yawPitchRoll.SplitToScalarVector();
    return yawPitchRoll;
}

Quaternion::Quaternion(float w, float x, float y, float z)
    : w_(w)
    , x_(x)
    , y_(y)
    , z_(z)
{
    SplitToScalarVector();
}

void Quaternion::SplitToScalarVector()
{
    scalar    = w_;
    vector[0] = x_;
    vector[1] = y_;
    vector[2] = z_;
}

void Quaternion::SplitFromScalarVector()
{
    w_ = scalar;
    x_ = vector.x();
    y_ = vector.y();
    z_ = vector.z();
}

std::string Quaternion::ToString() const
{
    return (std::to_string(w_) + std::to_string(x_) + std::to_string(y_) + std::to_string(z_));
}

Vector3 Quaternion::operator*(const Vector3& other)
{
    Quaternion tempQuaternion   = Quaternion(0.0f, other.x(), other.y(), other.z());
    Quaternion crossQuaternion  = (*(this)) * tempQuaternion;
    Quaternion final_quaternion = crossQuaternion * this->CreateInverse();
    return (Vector3{final_quaternion.x(), final_quaternion.y(), final_quaternion.z()});
}
