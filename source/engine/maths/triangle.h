#ifndef ENGINE_MATHS_TRIANGLE_H_
#define ENGINE_MATHS_TRIANGLE_H_

#include "bounding_box.h"
#include "point.h"
#include "primitive.h"

namespace engine
{
    namespace geometry
    {
        struct ImplicitLineCoefficients;
        using Vertex = engine::geometry::Point3D;

        struct TriangleEdge
        {
            Point3D start;
            Point3D end;
        };

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

            TriangleEdge Edge_0() const
            {
                return TriangleEdge{.start = vert_a_, .end = vert_b_};
            }

            TriangleEdge Edge_1() const
            {
                return TriangleEdge{.start = vert_b_, .end = vert_c_};
            }

            TriangleEdge Edge_2() const
            {
                return TriangleEdge{.start = vert_c_, .end = vert_a_};
            }

            AxisAlignedBoundingBox GetBoundingBox() const;

        private:
            // CounterClockwise Direction
            Vertex                         vert_a_;
            Vertex                         vert_b_;
            Vertex                         vert_c_;
            mutable AxisAlignedBoundingBox bounding_box_;
            bool                           is_bounding_box_computed_ = false;
        };
    }  // namespace geometry

}  // namespace engine

#endif