#ifndef ENGINE_GRAPHICS_PIXEL_H_
#define ENGINE_GRAPHICS_PIXEL_H_

#include <cstdint>
#include <cstring>

#include "color.h"

namespace engine
{
    namespace graphics
    {

        class PixelCoordinate
        {
        public:
            enum class Origin : uint8_t
            {
                kTopLeft,
                kBottomLeft
            };

            PixelCoordinate() = default;
            PixelCoordinate(uint16_t x_in, uint16_t y_in, Origin origin_in = Origin::kTopLeft)
                : x(x_in)
                , y(y_in)
                , origin(origin_in)
            {
            }

            uint16_t x, y;
            Origin   origin;

        private:
            [[maybe_unused]] uint8_t _padding_ = 0;
        };

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

            Pixel(uint16_t x, uint16_t y, ColorFormat color_format = ColorFormat::kRgb8)
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

            Pixel(PixelCoordinate coordinate, ColorFormat color_format = ColorFormat::kRgb8)
                : coordinate_(coordinate)
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

            uint16_t x() const
            {
                return coordinate_.x;
            }

            uint16_t y() const
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
    }  // namespace graphics
}  // namespace engine

#endif
