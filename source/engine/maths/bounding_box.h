#ifndef ENGINE_MATHS_BOUNDING_BOX_H_
#define ENGINE_MATHS_BOUNDING_BOX_H_

#include "Vector3.h"

namespace engine
{
    class BoundingBox
    {
    public:
        bool DoesCollides(const BoundingBox& other) const;

        // Computes the square distance between a point p and an AABB b
        float SquareDistancePoint(const Vector3& point) const;

        // Given point p, return the point q on or in AABB b that is closest to p
        Vector3 ClosestPtPointAABB(const Vector3& point) const;
        float   SqDistPointAABB(Vector3 point) const;

        Vector3 min;
        Vector3 max;
    };

}  // namespace engine

#endif
