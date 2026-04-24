#ifndef CORE_GRAPHICS_PIXEL_H_
#define CORE_GRAPHICS_PIXEL_H_

#include <cstdint>

#include "color.h"
#include "graphics_common.h"

namespace amit::graphics
{
    class Pixel
    {
    public:
        Pixel(ColorFormat color_format = ColorFormat::kRgb8)
            : coordinate_(0, 0)
            , color_format_(color_format)
        {
            if (color_format == ColorFormat::kRgb8)
            {
                color_data_.rgb8_color_ = Rgb8(0, 0, 0);
            }
            else if (color_format == ColorFormat::kFloat)
            {
                color_data_.float_color_ = FloatColor(0.0f, 0.0f, 0.0f);
            }
        }

        Pixel(uint32_t x, uint32_t y, ColorFormat color_format = ColorFormat::kRgb8)
            : coordinate_(x, y)
            , color_format_(color_format)
        {
            if (color_format == ColorFormat::kRgb8)
            {
                color_data_.rgb8_color_ = Rgb8(0, 0, 0);
            }
            else if (color_format == ColorFormat::kFloat)
            {
                color_data_.float_color_ = FloatColor(0.0f, 0.0f, 0.0f);
            }
        }

        Pixel(uint32_t x, uint32_t y, const Rgb8& color)
            : coordinate_(x, y)
            , color_format_(ColorFormat::kRgb8)
            , color_data_{.rgb8_color_ = color}
        {
        }

        Pixel(uint32_t x, uint32_t y, const FloatColor& color)
            : coordinate_(x, y)
            , color_format_(ColorFormat::kFloat)
            , color_data_{.float_color_ = color}
        {
        }

        explicit Pixel(PixelCoordinate coordinate, const Rgb8& color)
            : coordinate_(coordinate)
            , color_format_(ColorFormat::kRgb8)
            , color_data_{.rgb8_color_ = color}
        {
        }

        explicit Pixel(PixelCoordinate coordinate, const FloatColor& color)
            : coordinate_(coordinate)
            , color_format_(ColorFormat::kFloat)
            , color_data_{.float_color_ = color}
        {
        }

        Pixel(const Pixel& other)
        {
            coordinate_   = other.coordinate_;
            color_format_ = other.color_format_;
            if (color_format_ == ColorFormat::kRgb8)
            {
                color_data_.rgb8_color_ = other.color_data_.rgb8_color_;
            }
            else if (color_format_ == ColorFormat::kFloat)
            {
                color_data_.float_color_ = other.color_data_.float_color_;
            }
        }

        uint32_t x() const
        {
            return coordinate_.x;
        }

        uint32_t y() const
        {
            return coordinate_.y;
        }

        ColorFormat GetColorFormat() const
        {
            return color_format_;
        }

        void SetColor(const Rgb8& color)
        {
            color_data_.rgb8_color_ = color;
        }

        void SetColor(const FloatColor& color)
        {
            color_data_.float_color_ = color;
        }

        Rgb8 GetRgb8Color() const
        {
            return color_data_.rgb8_color_;
        }

        FloatColor GetFloatColor() const
        {
            return color_data_.float_color_;
        }

        PixelCoordinate GetCoordinate() const
        {
            return coordinate_;
        }

    private:
        PixelCoordinate coordinate_;
        ColorFormat     color_format_;
        union
        {
            Rgb8       rgb8_color_ = {};
            FloatColor float_color_;
        } color_data_;
    };

}  // namespace amit::graphics

#endif
