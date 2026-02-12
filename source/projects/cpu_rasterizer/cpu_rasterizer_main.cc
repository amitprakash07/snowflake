
#include <iostream>

#include "engine/common/maths_util.h"
#include "engine/maths/triangle.h"
#include "engine/graphics/color.h"
#include "engine/graphics/ppm_image.h"

int main(int argc, char* argv[])
{
    /*
     * What do we need to do to start the CPU rasterizer?
     * Suggested steps:
     * 1. Create a frame buffer to hold pixel data - think it as a PPM file
     * 2. Work in Screen space for a triangle
     * 3. Find the pixels and add color to it.
     */

    uint16_t                   width  = 800;
    uint16_t                   height = 600;
    engine::geometry::Vertex   a{400, 100, 0};
    engine::geometry::Vertex   b{200, 500, 0};
    engine::geometry::Vertex   c{600, 500, 0};
    engine::geometry::Triangle screen_space_triangle(a, b, c);
    screen_space_triangle;

    engine::graphics::PpmImage framebuffer(width, height);

    // Rasterization logic goes here. For now, we just set the triangle vertices to red color.
    framebuffer.SetPixelColor((int)a.x(), (int)a.y(), 255, 0, 0);
    framebuffer.SetPixelColor((int)b.x(), (int)b.y(), 255, 0, 0);
    framebuffer.SetPixelColor((int)c.x(), (int)c.y(), 255, 0, 0);

    /*framebuffer.SetSurroundIngPixelsColor((int)a.x(), (int)a.y(), 2, engine::graphics::Color(255, 0, 0));
    framebuffer.SetSurroundIngPixelsColor((int)b.x(), (int)b.y(), 2, engine::graphics::Color(255, 0, 0));
    framebuffer.SetSurroundIngPixelsColor((int)c.x(), (int)c.y(), 2, engine::graphics::Color(255, 0, 0));*/

    // Save the frame buffer to disk as a PPM image
    framebuffer.SaveToDisk("output.ppm");

    printf("CPU rasterizer is starting");
    return 0;
}