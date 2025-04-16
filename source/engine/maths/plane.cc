
#include "plane.h"

using namespace engine;

Plane::Plane(const Vector3& normal, const Vector3& point_on_plane)
{
    normal_   = normal;
    float a   = normal.x();
    float b   = normal.y();
    float c   = normal.z();
    distance_ = a * point_on_plane.x() + b * point_on_plane.y() + c * point_on_plane.z();
}

Vector3 Plane::ClosestPointFromPointOnPlane(const Vector3& point_on_plane) const
{
    float t = (normal_.Dot(point_on_plane) - distance_) / normal_.Dot(normal_);
    return (point_on_plane - (normal_ * t));
}

Plane Plane::ComputePlane(const Vector3& vec_a, const Vector3& vec_b, const Vector3& vec_c)
{
    Plane p;
    p.normal_   = (vec_b - vec_a).Cross(vec_c - vec_a).CreateNormalized();
    p.distance_ = p.normal_.Dot(vec_a);
    return p;
}