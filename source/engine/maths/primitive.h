#ifndef ENGINE_MATHS_PRIMITIVE_H_
#define ENGINE_MATHS_PRIMITIVE_H_

#include <cstdint>

#include "vector3.h"

namespace engine::geometry
{
    enum class PrimitiveType : std::uint8_t
    {
        kUnknown = 0,
        kPoint,
        kLineSegment,
        kTriangle,
        kBoundingBox,
        kPlane,
        kSphere
    };

    const engine::maths::Vector3 kYAxis{0.0f, 1.0f, 0.0f};
    const engine::maths::Vector3 kXAxis{1.0f, 0.0f, 0.0f};
    const engine::maths::Vector3 kZAxis{0.0f, 0.0f, 1.0f};

    class Primitive
    {
    public:
        Primitive()          = default;
        virtual ~Primitive() = default;

        virtual PrimitiveType GetType() const
        {
            return primitive_type_;
        }

    protected:
        Primitive(PrimitiveType type)
            : primitive_type_(type)
        {
        }

        PrimitiveType primitive_type_{PrimitiveType::kUnknown};
    };
}  // namespace engine::geometry
#endif