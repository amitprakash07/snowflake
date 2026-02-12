#ifndef ENGINE_GRAPHICS_PPM_IMAGE_H_
#define ENGINE_GRAPHICS_PPM_IMAGE_H_

#include <cstdint>
#include <cstdio>

#include "color.h"

namespace engine
{
    namespace graphics
    {
        class PpmImage
        {
        public:
            PpmImage() = delete;

            PpmImage(uint16_t width, uint16_t height);

            ~PpmImage()
            {
                delete[] image_data_;
            }

            void SetPixelColor(int x, int y, const engine::graphics::Color& color);

            void SetPixelColor(int x, int y, uint8_t r, uint8_t g, std::uint8_t b);

            void SetSurroundIngPixelsColor(int x, int y, uint8_t step, const engine::graphics::Color& color);

            void SaveToDisk(const char* filename);

        private:
            engine::graphics::Color* image_data_;  // Array to hold pixel colors by row-major order
            uint16_t                 width_;
            uint16_t                 height_;
        };
    }  // namespace graphics
}  // namespace engine

#endif