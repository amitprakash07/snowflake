#ifndef CORE_MATHS_BOUNDING_BOX_H_
#define CORE_MATHS_BOUNDING_BOX_H_

#include <array>

#include "point.h"
#include "Vector3.h"

namespace amit
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
            AxisAlignedBoundingBox() = default;
            AxisAlignedBoundingBox(const Point3D& min, const Point3D& max)
                : min_(min)
                , max_(max)
            {
                vertices_[0] = Point3D(min_.x, min_.y, min_.z);
                vertices_[1] = Point3D(max_.x, min_.y, min_.z);
                vertices_[2] = Point3D(max_.x, max_.y, min_.z);
                vertices_[3] = Point3D(min_.x, max_.y, min_.z);
            }

            bool                          IsInside(Point3D point) const;
            const std::array<Point3D, 4>& GetVertices() const;
            
            Point3D                       GetMin() const
            {
                return min_;
            }

            Point3D GetMax() const
            {
                return max_;
            }

        private:
            std::array<Point3D, 4> vertices_;
            Point3D                min_;
            Point3D                max_;
        };
    }  // namespace geometry

}  // namespace engine

#endif
