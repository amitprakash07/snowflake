#ifndef ENGINE_MATHS_POINT_H_
#define ENGINE_MATHS_POINT_H_

#include "primitive.h"

namespace engine
{
    namespace geometry
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

            Point3D(float x_in, float y_in, float z_in)
                : Primitive(PrimitiveType::kPoint)
                , x(x_in)
                , y(y_in)
                , z(z_in)
            {
            }

            float x;
            float y;
            float z;
        };
    }  // namespace geometry
}  // namespace engine

#endif  // ENGINE_MATHS_POINT_H_