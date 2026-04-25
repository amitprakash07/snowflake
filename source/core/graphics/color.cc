#include <algorithm>

#include "core/graphics_common/color.h"

amit::graphics::FloatColor amit::graphics::Rgb8::ToFloatColor() const
{
    return FloatColor({static_cast<float>(r) / 255.0f, static_cast<float>(g) / 255.0f, static_cast<float>(b) / 255.0f});
}

amit::graphics::Rgb8 amit::graphics::FloatColor::ToRgb8() const
{
    uint8_t r8 = static_cast<uint8_t>(std::clamp(r * 255.0f, 0.0f, 255.0f));
    uint8_t g8 = static_cast<uint8_t>(std::clamp(g * 255.0f, 0.0f, 255.0f));
    uint8_t b8 = static_cast<uint8_t>(std::clamp(b * 255.0f, 0.0f, 255.0f));
    return Rgb8{r8, g8, b8};
}