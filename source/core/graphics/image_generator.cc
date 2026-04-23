#include "image_generator.h"

amit::graphics::Image2D<amit::graphics::Rgb8> amit::graphics::ImageGenerator::GetCheckerBoard(
    core::graphics::Width    width,
    core::graphics::Height   height,
    core::graphics::TileSize tile_size)
{
    Image2D<Rgb8> checker_board{width, height};

    for (uint32_t y = 0; y < height.value; y += tile_size.value)
    {
        for (uint32_t x = 0; x < width.value; x += tile_size.value)
        {
            Rgb8 color = ((x / tile_size.value + y / tile_size.value) % 2 == 0) ? kRgb8ColorWhite : kRgb8ColorBlack;
            checker_board.FillTile(color, {x, y}, tile_size);
        }
    }

    return checker_board;
}

amit::graphics::Image2D<amit::graphics::Rgb8> amit::graphics::ImageGenerator::GetCheckerBoard(
    core::graphics::TileSize tile_size,
    uint32_t                 tile_count_x,
    uint32_t                 tile_count_y)
{
    core::graphics::Width  image_width{.value = tile_size.value * tile_count_x};
    core::graphics::Height image_height{.value = tile_size.value * tile_count_y};

    return GetCheckerBoard(image_width, image_height, tile_size);
}