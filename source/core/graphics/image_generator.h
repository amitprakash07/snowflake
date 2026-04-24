#ifndef CORE_GRAPHICS_IMAGE_GENERATOR_H_
#define CORE_GRAPHICS_IMAGE_GENERATOR_H_

#include "image_2d.h"

namespace amit::graphics
{
    class ImageGenerator
    {
    public:
        static Image2D<Rgb8> GetCheckerBoard(Width width, Height height, TileSize tile_size);

        static Image2D<Rgb8> GetCheckerBoard(TileSize tile_size, uint32_t tile_count_x, uint32_t tile_count_y);
    };
}  // namespace amit::graphics

#endif