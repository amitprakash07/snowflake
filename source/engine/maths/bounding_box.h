#ifndef ENGINE_MATHS_BOUNDING_BOX_H_
#define ENGINE_MATHS_BOUNDING_BOX_H_

#include "point.h"
#include "Vector3.h"

namespace engine
{
    class BoundingBox
    {
    public:
        bool DoesCollides(const BoundingBox& other) const;

        // Computes the square distance between a point p and an AABB b
        float SquareDistancePoint(const maths::Vector3& point) const;

        // Given point p, return the point q on or in AABB b that is closest to p
        maths::Vector3 ClosestPtPointAABB(const maths::Vector3& point) const;
        float          SqDistPointAABB(maths::Vector3 point) const;

        maths::Vector3 min;
        maths::Vector3 max;
    };

    namespace geometry
    {
        class AxisAlignedBoundingBox
        {
        public:
            bool    IsInside(Point3D point) const;
            Point3D min;
            Point3D max;
        };
    }  // namespace geometry

}  // namespace engine

#endif
