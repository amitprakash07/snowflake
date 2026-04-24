#ifndef CORE_MATHS_GEOMETRY_GEOMETRY_PRIMITIVES_H_
#define CORE_MATHS_GEOMETRY_GEOMETRY_PRIMITIVES_H_

#include <cstdint>
#include <concepts>

namespace amit::geometry
{
    class Primitive;

    template <typename T>
    concept PrimitiveTypeConcept = std::derived_from<T, Primitive>;

}  // namespace amit::geometry

#include "triangle.h"
#include "bounding_box.h"
#include "line_segment.h"
#include "point.h"
#include "plane.h"

#endif  // CORE_MATHS_GEOMETRY_PRIMITIVES_H_