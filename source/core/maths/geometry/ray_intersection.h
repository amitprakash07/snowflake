#ifndef CORE_MATHS_GEOMETRY_RAY_INTERSECTION_H_
#define CORE_MATHS_GEOMETRY_RAY_INTERSECTION_H_

#include "core/maths/linear_algebra/vector3.h"

#include "sphere.h"
#include "plane.h"
#include "bounding_box.h"
#include "triangle.h"

namespace amit
{
    struct HitInfo
    {
        amit::maths::Vector3 hit_point;
        amit::maths::Vector3 normal;
        float                  distance;
        HitInfo();
    };

    class Ray
    {
    public:
        template <class Primitive>
        bool Intersect(const Primitive& primitive, HitInfo& hit_info) const
        {
            return false;
        }

        amit::maths::Vector3 origin;
        amit::maths::Vector3 direction;
    };

}  // namespace engine

template <>
bool amit::Ray::Intersect<amit::geometry::Plane>(const geometry::Plane& primitive, HitInfo& hit_info) const;

template <>
bool amit::Ray::Intersect<amit::geometry::Sphere>(const geometry::Sphere& primitive, HitInfo& hit_info) const;

template <>
bool amit::Ray::Intersect<amit::BoundingBox>(const BoundingBox& primitive, HitInfo& hit_info) const;

template <>
bool amit::Ray::Intersect<amit::geometry::Triangle>(const geometry::Triangle& primitive, HitInfo& hit_info) const;

#endif
