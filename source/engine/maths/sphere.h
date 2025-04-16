#ifndef ENGINE_MATHS_SPHERE_H_
#define ENGINE_MATHS_SPHERE_H_

#include "vector3.h"

namespace engine
{
    class Sphere
    {
    public:
        bool    DoesIntersect(const Sphere& other) const;
        Vector3 centre;
        float   radius;
    };
}  // namespace engine

#endif