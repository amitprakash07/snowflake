#ifndef CORE_GRAPHICS_COMMON_GRAPHICS_COMMON_H_
#define CORE_GRAPHICS_COMMON_GRAPHICS_COMMON_H_

#include <cstdint>
#include <type_traits>

#include "core/maths/linear_algebra/intervals.h"

namespace amit::graphics
{
    struct Width
    {
        std::uint32_t value;
    };

    struct Height
    {
        std::uint32_t value;
    };

    struct TileSize
    {
        // Represents a square tile of size {value x value}.
        std::uint32_t value;
    };

    template <typename T>
        requires std::is_arithmetic_v<T> || std::is_same_v<T, std::uint32_t>
    struct Coordinate
    {
        T x;
        T y;
    };

    using DiscreteCoordinate   = Coordinate<std::uint32_t>;
    using ContinuousCoordinate = Coordinate<float>;

    using UVCoordinate           = ContinuousCoordinate;
    using NormalizedUVCoordinate = amit::maths::ClosedInterval<double, 0.0f, 1.0f>;

    using PixelCoordinate = DiscreteCoordinate;

}  // namespace amit::graphics

#endif  // CORE_GRAPHICS_COMMON_GRAPHICS_COMMON_H_
