#ifndef CORE_MATHS_GEOMETRY_GEOMETRY_H_
#define CORE_MATHS_GEOMETRY_GEOMETRY_H_

#include "geometry_primitives.h"

namespace amit::geometry
{
    inline ImplicitLineCoefficients MakeImplicitLineCoefficients(const Point3D& a, const Point3D& b)
    {
        ImplicitLineCoefficients temp_coefficients;
        temp_coefficients.a = a.y - b.y;
        temp_coefficients.b = b.x - a.x;
        temp_coefficients.c = -1 * ((temp_coefficients.a * a.x) + (temp_coefficients.b * a.y));
        return temp_coefficients;
    }

    inline float Orient2D(const ImplicitLineCoefficients& coefficient, const Point3D& point)
    {
        float edge_function_value = (coefficient.a * point.x) + (coefficient.b * point.y) + coefficient.c;
        return edge_function_value;
    }

    inline float Orient2D(const Point3D& a, const Point3D& b, const Point3D& point)
    {
        /*
         * vector AB = b - a
         * vector AP = point - a          
         * edge_function = AB x AP = (b - a) x (point - a), i.e. the cross product
         * matrix representation of cross product of two 2D vectors (x1, y1) and (x2, y2) 
         * is given by the determinant of the following matrix:
         * | b.x - a.x    point.x - a.x |
         * | b.y - a.y    point.y - a.y |
         */

        ImplicitLineCoefficients temp_coefficients = MakeImplicitLineCoefficients(a, b);
        return Orient2D(temp_coefficients, point);
    }

    inline float SignedAreaOfTriangle(const Point3D& a, const Point3D& b, const Point3D& c)
    {
        return 0.5f * Orient2D(a, b, c);
    }

    inline float AreaOfTriangle(const Point3D& a, const Point3D& b, const Point3D& c)
    {
        return abs(SignedAreaOfTriangle(a, b, c));
    }

    struct BaryCentricCoordinate
    {
        float alpha;
        float beta;
        float gamma;
    };

    inline BaryCentricCoordinate CalculateBaryCentricCoordinate(const Point3D& a,
                                                                const Point3D& b,
                                                                const Point3D& c,
                                                                const Point3D& p)
    {
        BaryCentricCoordinate barycentric;
        float                 triangle_area = SignedAreaOfTriangle(a, b, c);
        barycentric.alpha                   = SignedAreaOfTriangle(b, c, p) / triangle_area;
        barycentric.beta                    = SignedAreaOfTriangle(c, a, p) / triangle_area;
        barycentric.gamma                   = SignedAreaOfTriangle(a, b, p) / triangle_area;
        return barycentric;
    }

}  // namespace amit::geometry

#endif  // CORE_MATHS_GEOMETRY_H_