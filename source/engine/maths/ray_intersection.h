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
        engine::maths::Vector3 hit_point;
        engine::maths::Vector3 normal;
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

        engine::maths::Vector3 origin;
        engine::maths::Vector3 direction;
    };

}  // namespace engine

template <>
bool engine::Ray::Intersect<engine::geometry::Plane>(const geometry::Plane& primitive, HitInfo& hit_info) const;

template <>
bool engine::Ray::Intersect<engine::geometry::Sphere>(const geometry::Sphere& primitive, HitInfo& hit_info) const;

template <>
bool engine::Ray::Intersect<engine::BoundingBox>(const BoundingBox& primitive, HitInfo& hit_info) const;

template <>
bool engine::Ray::Intersect<engine::geometry::Triangle>(const geometry::Triangle& primitive, HitInfo& hit_info) const;

#endif
