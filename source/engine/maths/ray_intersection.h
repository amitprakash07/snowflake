#ifndef ENGINE_MATHS_RAY_INTERSECTION_H_
#define ENGINE_MATHS_RAY_INTERSECTION_H_

#include "sphere.h"
#include "plane.h"
#include "vector3.h"
#include "bounding_box.h"
#include "Triangle.h"

namespace engine
{
    struct HitInfo
    {
        Vector3 hit_point;
        Vector3 normal;
        float   distance;
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

        Vector3 origin;
        Vector3 direction;
    };

}  // namespace engine

template <>
bool engine::Ray::Intersect<engine::Plane>(const Plane& primitive, HitInfo& hit_info) const;

template <>
bool engine::Ray::Intersect<engine::Sphere>(const Sphere& primitive, HitInfo& hit_info) const;

template <>
bool engine::Ray::Intersect<engine::BoundingBox>(const BoundingBox& primitive, HitInfo& hit_info) const;

template <>
bool engine::Ray::Intersect<engine::geometry::Triangle>(const geometry::Triangle& primitive, HitInfo& hit_info) const;

#endif
