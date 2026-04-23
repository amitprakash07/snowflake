#ifndef CORE_GRAPHICS_GRAPHICS_COMMON_H_
#define CORE_GRAPHICS_GRAPHICS_COMMON_H_

#include <cstdint>
#include <type_traits>

namespace core::graphics
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
        requires std::is_same_v<T, uint32_t> || std::is_same_v<T, float>
    struct Coordinate
    {
        T x;
        T y;
    };

    using DiscreteCoordinate   = Coordinate<std::uint32_t>;
    using ContinuousCoordinate = Coordinate<float>;

}  // namespace core::graphics

#endif  // CORE_GRAPHICS_GRAPHICS_COMMON_H_