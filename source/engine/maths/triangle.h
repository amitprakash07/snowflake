#ifndef ENGINE_MATHS_TRIANGLE_H_
#define ENGINE_MATHS_TRIANGLE_H_

#include "bounding_box.h"
#include "point.h"
#include "primitive.h"

namespace engine
{
    namespace geometry
    {
        using Vertex = engine::geometry::Point3D;

        class Triangle : public Primitive
        {
        public:
            // Returns 2 times the signed triangle area. The result is positive if
            // abc is ccw, negative if abc is cw, zero if abc is degenerate.
            float Signed2DTriArea() const;

            Triangle() = delete;

            Triangle(const Vertex& a, const Vertex& b, const Vertex& c)
                : Primitive(PrimitiveType::kTriangle)
                , vert_a_(a)
                , vert_b_(b)
                , vert_c_(c)
            {
            }

            Triangle(const Triangle& other)
                : Primitive(PrimitiveType::kTriangle)
                , vert_a_(other.vert_a_)
                , vert_b_(other.vert_b_)
                , vert_c_(other.vert_c_)
            {
            }

            Triangle& operator=(const Triangle& other)
            {
                vert_a_ = other.vert_a_;
                vert_b_ = other.vert_b_;
                vert_c_ = other.vert_c_;
                return *this;
            }

            inline Vertex Vert_A() const
            {
                return vert_a_;
            }

            inline Vertex Vert_B() const
            {
                return vert_b_;
            }

            inline Vertex Vert_C() const
            {
                return vert_c_;
            }

            AxisAlignedBoundingBox GetBoundingBox() const;

            bool IsInside(const Point3D& point) const;

        private:
            // Counter ClockWise Direction
            Vertex                         vert_a_;
            Vertex                         vert_b_;
            Vertex                         vert_c_;
            mutable AxisAlignedBoundingBox bounding_box_;
            bool                           is_bounding_box_computed_ = false;
        };
    }  // namespace geometry

}  // namespace engine

#endif