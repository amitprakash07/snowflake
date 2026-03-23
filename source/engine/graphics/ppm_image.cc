#include <cstring>
#include <iostream>

#include "ppm_image.h"

engine::graphics::PpmImage::PpmImage(uint16_t width, uint16_t height)
    : image_data_(nullptr)
    , width_(width)
    , height_(height)
{
    if (width_ > 0 && height_ > 0)
    {
        image_data_ = new engine::graphics::Rgb8[width_ * height_];  // RGB
        memset(image_data_, 0, width * height * sizeof(engine::graphics::Rgb8));
    }
}

void engine::graphics::PpmImage::SetPixelColor(const PixelCoordinate&        pixel_coordinate,
                                               const engine::graphics::Rgb8& color)
{
    const PixelCoordinate& coordinate = pixel_coordinate;

    if (coordinate.x < 0 || coordinate.y < 0)
    {
        printf("It's wrong");
        return;
    }

    int index = coordinate.y * width_ + coordinate.x;
    if (index >= (width_ * height_))
    {
        return;
    }

    image_data_[index] = color;
}

void engine::graphics::PpmImage::SetPixel(const Pixel& pixel)
{
    SetPixelColor(pixel.GetCoordinate(), pixel.GetRgb8Color());
}

void engine::graphics::PpmImage::SetPixelTileColor(Pixel& pixel, uint8_t step, const engine::graphics::Rgb8& rgb8_color)
{
    size_t count = 0;

    const PixelCoordinate& coordinate = pixel.GetCoordinate();

    for (int16_t i = -step; i < step; i++)
    {
        for (int16_t j = -step; j < step; j++)
        {
            Pixel tile_pixel(coordinate.x + i, coordinate.y + j);
            SetPixelColor(coordinate, rgb8_color);
            count++;
        }
    }

    std::cout << "Total Pixel count" << count;
}

void engine::graphics::PpmImage::SaveToDisk(const char* filename)
{
    FILE* file = fopen(filename, "wb");
    fprintf(file, "P6\n%d %d\n255\n", width_, height_);
    fwrite(image_data_, sizeof(engine::graphics::Rgb8), width_ * height_, file);
    fclose(file);
}