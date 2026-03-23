#ifndef ENGINE_GRAPHICS_COLOR_H_
#define ENGINE_GRAPHICS_COLOR_H_

namespace engine
{
    namespace graphics
    {
        enum class ColorFormat : uint8_t
        {
            kRgb8,
            kFloat
        };

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

            Rgb8(const Rgb8& other)
                : r(other.r)
                , g(other.g)
                , b(other.b)
            {
            }

            uint8_t r, g, b;
        };

        const Rgb8 kRed   = {255, 0, 0};
        const Rgb8 kGreen = {0, 255, 0};
        const Rgb8 kBlue  = {0, 0, 255};
        const Rgb8 kWhite = {255, 255, 255};
        const Rgb8 kBlack = {0, 0, 0};

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

            FloatColor(const FloatColor& other)
                : r(other.r)
                , g(other.g)
                , b(other.b)
            {
            }

            float r;
            float g;
            float b;
        };

    }  // namespace graphics
}  // namespace engine

#endif