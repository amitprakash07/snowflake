#ifndef ENGINE_MATHS_PLANE_H_
#define ENGINE_MATHS_PLANE_H_

#include "primitive.h"
#include "vector3.h"

namespace engine::geometry
{
    class Plane : public Primitive
    {
    public:
        static Plane   ComputePlane(const maths::Vector3& vec_a,
                                    const maths::Vector3& vec_b,
                                    const maths::Vector3& vec_c);
        maths::Vector3 ClosestPointFromPointOnPlane(const maths::Vector3& point_on_plane) const;

        Plane(const maths::Vector3& normal, const maths::Vector3& point_on_plane);
        Plane()
            : Primitive(geometry::PrimitiveType::kPlane)
            , normal_(geometry::kYAxis)
            , distance_(0.0f)
        {
        }

        inline maths::Vector3 Normal() const
        {
            return normal_;
        }

        inline float Distance() const
        {
            return distance_;
        }

    private:
        maths::Vector3 normal_;    //< Unit vector representing the normal of the plane
        float          distance_;  //< distance from the origin to the plane in the direction of the normal
    };
}  // namespace engine::geometry

#endif