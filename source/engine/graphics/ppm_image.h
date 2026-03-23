#ifndef ENGINE_GRAPHICS_PPM_IMAGE_H_
#define ENGINE_GRAPHICS_PPM_IMAGE_H_

#include <cstdint>
#include <cstdio>

#include "pixel.h"

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

            void SetPixelColor(const PixelCoordinate& pixel_coordinate, const engine::graphics::Rgb8& color);

            void SetPixel(const Pixel& pixel);

            void SetPixelTileColor(Pixel& pixel, uint8_t step, const engine::graphics::Rgb8& rgb8_color);

            void SaveToDisk(const char* filename);

        private:
            engine::graphics::Rgb8* image_data_;  // Array to hold pixel colors by row-major order
            uint16_t                width_;
            uint16_t                height_;
        };
    }  // namespace graphics
}  // namespace engine

#endif