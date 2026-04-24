#ifndef CORE_MATHS_GEOMETRY_TRIANGLE_H_
#define CORE_MATHS_GEOMETRY_TRIANGLE_H_

#include "line_segment.h"
#include "point.h"
#include "primitive.h"

namespace amit::geometry
{
    struct ImplicitLineCoefficients;

    struct TriangleEdge
    {
        Point3D start;
        Point3D end;

        LineSegment ToLineSegment() const
        {
            return LineSegment{start, end};
        }
    };

    float CalculateSigned2DTriAreaCCW(const Point3D& a, const Point3D& b, const Point3D& c);

    class Triangle : public Primitive
    {
    public:
        // Returns 2 times the signed triangle area. The result is positive if
        // abc is ccw, negative if abc is cw, zero if abc is degenerate.
        float Signed2DTriArea() const;

        Triangle() = delete;

        Triangle(const Point3D& a, const Point3D& b, const Point3D& c)
            : Primitive(PrimitiveType::kTriangle)
            , vert_a_position_(a)
            , vert_b_position_(b)
            , vert_c_position_(c)
        {
            object_label_.SetName("Triangle");
        }

        Triangle(const Triangle& other)
            : Primitive(PrimitiveType::kTriangle)
            , vert_a_position_(other.vert_a_position_)
            , vert_b_position_(other.vert_b_position_)
            , vert_c_position_(other.vert_c_position_)
        {
        }

        Triangle& operator=(const Triangle& other)
        {
            vert_a_position_ = other.vert_a_position_;
            vert_b_position_ = other.vert_b_position_;
            vert_c_position_ = other.vert_c_position_;
            return *this;
        }

        TriangleEdge Edge_0() const
        {
            return TriangleEdge{.start = vert_a_position_, .end = vert_b_position_};
        }

        TriangleEdge Edge_1() const
        {
            return TriangleEdge{.start = vert_b_position_, .end = vert_c_position_};
        }

        TriangleEdge Edge_2() const
        {
            return TriangleEdge{.start = vert_c_position_, .end = vert_a_position_};
        }

        const Point3D& VertA() const
        {
            return vert_a_position_;
        }

        const Point3D& VertB() const
        {
            return vert_b_position_;
        }

        const Point3D& VertC() const
        {
            return vert_c_position_;
        }

    private:
        // CounterClockwise Direction
        Point3D vert_a_position_;
        Point3D vert_b_position_;
        Point3D vert_c_position_;
    };
}  // namespace amit::geometry

#endif