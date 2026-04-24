#ifndef CORE_GRAPHICS_TEXTURE_H_
#define CORE_GRAPHICS_TEXTURE_H_

#include <cstdint>

#include "image_2d.h"

namespace amit::graphics
{
    template <typename TextureDataType>
    class Texture
    {
    public:
        explicit Texture(const Image2D<TextureDataType>& image)
            : image_(image)
        {
        }

        TextureDataType Sample(const UVCoordinate& coordinate) const
        {
            const uint32_t width  = image_.GetWidth().value;
            const uint32_t height = image_.GetHeight().value;

            if (width == 0 || height == 0)
            {
                return TextureDataType{};
            }

            const float clamped_u = ClampNormalizedCoordinate(coordinate.x);
            const float clamped_v = ClampNormalizedCoordinate(coordinate.y);

            const uint32_t image_x = static_cast<uint32_t>(clamped_u * static_cast<float>(width - 1));
            const uint32_t image_y = static_cast<uint32_t>(clamped_v * static_cast<float>(height - 1));

            return image_.GetImageData({image_x, image_y});
        }

    private:
        static float ClampNormalizedCoordinate(float value)
        {
            if (value < 0.0f)
            {
                return 0.0f;
            }

            if (value > 1.0f)
            {
                return 1.0f;
            }

            return value;
        }

        const Image2D<TextureDataType>& image_;
    };

}  // namespace amit::graphics

#endif
