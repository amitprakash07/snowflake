
#include <font8x8_basic.h>

#include "text_overlay.h"

bool engine::graphics::TextOverlay::Render(const std::string& text,
                                           uint16_t           x,
                                           uint16_t           y,
                                           Rgb8               color,
                                           PpmImage&          ppm_image)
{
    if (!text.empty())
    {
        uint16_t x_iter = x;
        uint16_t y_iter = y;

        for (char ch : text)
        {
            if (ch == '\n')
            {
                y_iter += 10;
                x_iter = x;
                continue;
            }

            if (ch == '\t')
            {
                x_iter += 4;
                continue;
            }

            uint8_t ascii_code = static_cast<uint8_t>(ch);
            char*   bitmap     = font8x8_basic[ascii_code];
            RenderGlyph(bitmap, x_iter, y_iter, color, ppm_image);
            x_iter += 8;
        }
    }

    return true;
}

void engine::graphics::TextOverlay::RenderGlyph(const char* bitmap,
                                                uint16_t    x,
                                                uint16_t    y,
                                                Rgb8        color,
                                                PpmImage&   ppm_image)
{
    for (uint16_t bitmap_iter = 0; bitmap_iter < 8; bitmap_iter++)
    {
        for (uint16_t bit_iter = 0; bit_iter < 8; bit_iter++)
        {
            if (bitmap[bitmap_iter] & 1 << bit_iter)
            {
                ppm_image.SetPixelColor({static_cast<uint16_t>(x + bit_iter), static_cast<uint16_t>(y + bitmap_iter)},
                                        color);
            }
        }
    }
}