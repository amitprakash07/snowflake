#ifndef ENGINE_MATH_PLANE_H_
#define ENGINE_MATH_PLANE_H_

#include "vector3.h"

namespace engine
{
    class Plane
    {
    public:
        static Plane ComputePlane(const Vector3& vec_a, const Vector3& vec_b, const Vector3& vec_c);
        Vector3      ClosestPointFromPointOnPlane(const Vector3& point_on_plane) const;
        Vector3      GetNormal() const;
        float        GetDistanceFromOrigin() const;
        Plane(const Vector3& normal, const Vector3& point_on_plane);
        Plane() = default;

    private:
        Vector3 normal_;
        float   distance_;
    };
}  // namespace engine

#endif