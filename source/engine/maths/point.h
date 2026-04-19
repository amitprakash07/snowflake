#ifndef ENGINE_MATHS_POINT_H_
#define ENGINE_MATHS_POINT_H_

#include "primitive.h"

namespace amit::geometry
{
    class Point2D : public Primitive
    {
    public:
        Point2D()
            : Primitive(PrimitiveType::kPoint)
            , x(0.0f)
            , y(0.0f)
        {
        }

        Point2D(float x_in, float y_in)
            : Primitive(PrimitiveType::kPoint)
            , x(x_in)
            , y(y_in)
        {
        }

        float x;
        float y;
    };

    class Point3D : public Primitive
    {
    public:
        Point3D()
            : Primitive(PrimitiveType::kPoint)
            , x(0.0f)
            , y(0.0f)
            , z(0.0f)
        {
        }

        explicit Point3D(float x_in, float y_in, float z_in)
            : Primitive(PrimitiveType::kPoint)
            , x(x_in)
            , y(y_in)
            , z(z_in)
        {
        }

        explicit Point3D(uint32_t x_in, uint32_t y_in, uint32_t z_in = 0)
            : Primitive(PrimitiveType::kPoint)
            , x(static_cast<float>(x_in))
            , y(static_cast<float>(y_in))
            , z(static_cast<float>(z_in))
        {
        }

        float x;
        float y;
        float z;
    };

}  // namespace amit::geometry

#endif  // ENGINE_MATHS_POINT_H_