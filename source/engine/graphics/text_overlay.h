#ifndef ENGINE_GRAPHICS_TEXT_OVERLAY_H_
#define ENGINE_GRAPHICS_TEXT_OVERLAY_H_

#include "ppm_image.h"

namespace engine::graphics
{
    class TextOverlay
    {
    public:
        static bool Render(const std::string& text, uint16_t x, uint16_t y, Rgb8 color, PpmImage& ppm_image);
        TextOverlay();
        ~TextOverlay();

    private:
        static void RenderGlyph(const char* bitmap, uint16_t x, uint16_t y, Rgb8 color, PpmImage& ppm_image);
    };

}  // namespace engine::graphics

#endif  // ENGINE_GRAPHICS_TEXT_OVERLAY_H_