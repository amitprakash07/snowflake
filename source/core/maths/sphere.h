#ifndef CORE_MATHS_SPHERE_H_
#define CORE_MATHS_SPHERE_H_

#include "primitive.h"
#include "vector3.h"

namespace amit::geometry
{
    class Sphere : public geometry::Primitive
    {
    public:
        Sphere(const amit::maths::Vector3& centre, float radius)
            : Primitive(geometry::PrimitiveType::kSphere)
            , centre(centre)
            , radius(radius)
        {
        }

        Sphere()
            : Primitive(geometry::PrimitiveType::kSphere)
            , radius(1.0f)
        {
        }

        bool DoesIntersect(const Sphere& other) const;

        amit::maths::Vector3 centre;
        float                  radius;
    };
}  // namespace amit::geometry

#endif