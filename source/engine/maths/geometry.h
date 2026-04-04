#ifndef ENGINE_MATHS_GEOMETRY_H_
#define ENGINE_MATHS_GEOMETRY_H_

#include "geometry_primitives.h"

namespace engine::geometry
{
    inline float EdgeFunction(const Point3D& a, const Point3D& b, const Point3D& point)
    {
        /*
         * edge_function = (point - a) x (b - a), i.e. the cross product of (point - a) and (b - a)
         * matrix representation of cross product of two 2D vectors (x1, y1) and (x2, y2) 
         * is given by the determinant of the following matrix:
         * | point.x - a.x   point.y - a.y |
         * | b.x - a.x       b.y - a.y     |
         */
        return (point.x - a.x) * (b.y - a.y) - (point.y - a.y) * (b.x - a.x);
    }

}  // namespace engine::geometry

#endif  // ENGINE_MATHS_GEOMETRY_H_