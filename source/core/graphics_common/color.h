#ifndef CORE_GRAPHICS_COMMON_COLOR_H_
#define CORE_GRAPHICS_COMMON_COLOR_H_

#include <cstdint>

namespace amit::graphics
{
    enum class ColorFormat : uint8_t
    {
        kRgb8,
        kFloat
    };

    class FloatColor;

    class Rgb8
    {
    public:
        Rgb8()
            : r(0)
            , g(0)
            , b(0)
        {
        }

        Rgb8(uint8_t r_in, uint8_t g_in, uint8_t b_in)
            : r(r_in)
            , g(g_in)
            , b(b_in)
        {
        }

        FloatColor ToFloatColor() const;

        Rgb8(const Rgb8& other)            = default;
        Rgb8& operator=(const Rgb8& other) = default;

        uint8_t r, g, b;
    };

    const Rgb8 kRgb8ColorRed   = {255, 0, 0};
    const Rgb8 kRgb8ColorGreen = {0, 255, 0};
    const Rgb8 kRgb8ColorBlue  = {0, 0, 255};

    const Rgb8 kRgb8ColorWhite = {255, 255, 255};
    const Rgb8 kRgb8ColorBlack = {0, 0, 0};

    const Rgb8 kRgb8ColorCyan    = {0, 255, 255};
    const Rgb8 kRgb8ColorMagenta = {255, 0, 255};
    const Rgb8 kRgb8ColorYellow  = {255, 255, 0};

    class FloatColor
    {
    public:
        FloatColor()
            : r(0.0f)
            , g(0.0f)
            , b(0.0f)
        {
        }

        FloatColor(float red, float green, float blue)
            : r(red)
            , g(green)
            , b(blue)
        {
        }

        FloatColor(const FloatColor& other)            = default;
        FloatColor& operator=(const FloatColor& other) = default;

        Rgb8 ToRgb8() const;

        float r;
        float g;
        float b;
    };

}  // namespace amit::graphics

#endif
