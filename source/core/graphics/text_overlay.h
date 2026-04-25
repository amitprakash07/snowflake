#ifndef CORE_GRAPHICS_TEXT_OVERLAY_H_
#define CORE_GRAPHICS_TEXT_OVERLAY_H_

#include <string>

#include "core/graphics_common/color.h"
#include "image_2d.h"

namespace amit::graphics
{
    class TextOverlay
    {
    public:
        static bool Render(const std::string& text, uint16_t x, uint16_t y, Rgb8 color, ColorBuffer& color_buffer);

        ~TextOverlay() = default;
    private:
        static void RenderGlyph(const char* bitmap, uint16_t x, uint16_t y, Rgb8 color, ColorBuffer& color_buffer);
    };

}  // namespace amit::graphics

#endif  // CORE_GRAPHICS_TEXT_OVERLAY_H_