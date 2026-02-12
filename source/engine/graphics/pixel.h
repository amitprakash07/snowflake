#ifndef ENGINE_GRAPHICS_PIXEL_H_
#define ENGINE_GRAPHICS_PIXEL_H_

#include <cstdint>

namespace engine
{
    namespace graphics
    {
        class Pixel
        {
        public:
            Pixel() = default;
            Pixel(uint16_t x, uint16_t y)
                : x_(x)
                , y_(y)
            {
            }

            uint16_t x() const
            {
                return x_;
            }

            uint16_t y() const
            {
                return y_;
            }

        private:
            uint16_t x_;
            uint16_t y_;
        };
    }  // namespace graphics
}  // namespace engine

#endif
