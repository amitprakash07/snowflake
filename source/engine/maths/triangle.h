#ifndef ENGINE_MATHS_TRIANGLE_H_
#define ENGINE_MATHS_TRIANGLE_H_

#include "vector3.h"

namespace engine
{
    using Vertex = Vector3;

    class Triangle
    {
    public:
        // Returns 2 times the signed triangle area. The result is positive if
        // abc is ccw, negative if abc is cw, zero if abc is degenerate.
        float Signed2DTriArea() const;

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

    private:
        // Counter ClockWise Direction
        Vertex vert_a_;
        Vertex vert_b_;
        Vertex vert_c_;
    };

}  // namespace engine

#endif