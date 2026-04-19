#include <cstring>
#include <iostream>

#include "image_2d.h"

void amit::image::WriteColorBufferToPPM(const amit::graphics::ColorBuffer& color_buffer, const char* filename)
{
    FILE* file = fopen(filename, "wb");
    fprintf(file, "P6\n%d %d\n255\n", color_buffer.GetWidth(), color_buffer.GetHeight());
    fwrite(color_buffer.GetData(),
           sizeof(amit::graphics::Rgb8),
           static_cast<size_t>(color_buffer.GetWidth()) * color_buffer.GetHeight(),
           file);
    fclose(file);
}

void amit::image::WriteDepthBufferToPPM(const amit::graphics::DepthBuffer& depth_buffer, const char* filename)
{
    FILE* file = fopen(filename, "wb");
    fprintf(file, "P6\n%d %d\n255\n", depth_buffer.GetWidth(), depth_buffer.GetHeight());
    fwrite(depth_buffer.GetData(),
           sizeof(amit::graphics::Rgb8),
           static_cast<size_t>(depth_buffer.GetWidth()) * depth_buffer.GetHeight(),
           file);
    fclose(file);
}