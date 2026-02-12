#include "ppm_image.h"

engine::graphics::PpmImage::PpmImage(uint16_t width, uint16_t height)
    : image_data_(nullptr)
    , width_(width)
    , height_(height)
{
    if (width_ > 0 && height_ > 0)
    {
        image_data_ = new engine::graphics::Color[width_ * height_];  // RGB
    }
}

void engine::graphics::PpmImage::SetPixelColor(int x, int y, const engine::graphics::Color& color)
{
    if (x < 0 || y < 0)
    {
        printf("It's wrong");
        return;
    }

    int index          = y * width_ + x;
    if (index >= (width_ *height_))
    {
        return;
    }

    image_data_[index] = color;
}

void engine::graphics::PpmImage::SetPixelColor(int x, int y, uint8_t r, uint8_t g, std::uint8_t b)
{
    SetPixelColor(x, y, engine::graphics::Color(r, g, b));
}

void engine::graphics::PpmImage::SetSurroundIngPixelsColor(int                            x,
                                                           int                            y,
                                                           uint8_t                        step,
                                                           const engine::graphics::Color& color)
{
    for (int16_t i = -x; i < x; i++)
    {
        for (int16_t j = -y; j < y; j++)
        {
            SetPixelColor(x + i, y + j, color);
        }
    }
}

void engine::graphics::PpmImage::SaveToDisk(const char* filename)
{
    FILE* file = fopen(filename, "wb");
    fprintf(file, "P6\n%d %d\n255\n", width_, height_);
    fwrite(image_data_, sizeof(engine::graphics::Color), width_ * height_, file);
    fclose(file);
}