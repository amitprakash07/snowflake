
#include <iostream>

#include "engine/common/maths_util.h"
#include "engine/graphics/pixel.h"
#include "engine/graphics/viewport.h"
#include "engine/graphics/ppm_image.h"
#include "engine/graphics/rasterizer.h"

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
    engine::graphics::Viewport viewport(width, height);
    engine::geometry::Point3D  a{400u, 100u};
    engine::geometry::Point3D  b{200u, 500u};
    engine::geometry::Point3D  c{600u, 500u};
    engine::geometry::Triangle screen_space_triangle(a, b, c);

    engine::graphics::PpmImage framebuffer(width, height);

    // Rasterization logic goes here. For now, we just set the triangle vertices to red color.
    /*framebuffer.SetPixelColor((int)a.x(), (int)a.y(), 255, 0, 0);
    framebuffer.SetPixelColor((int)b.x(), (int)b.y(), 255, 0, 0);
    framebuffer.SetPixelColor((int)c.x(), (int)c.y(), 255, 0, 0);*/
    engine::graphics::Pixel vert_a_pixel = {static_cast<uint16_t>(a.x), static_cast<uint16_t>(a.y)};
    engine::graphics::Pixel vert_b_pixel = {static_cast<uint16_t>(b.x), static_cast<uint16_t>(b.y)};
    engine::graphics::Pixel vert_c_pixel = {static_cast<uint16_t>(c.x), static_cast<uint16_t>(c.y)};

    //framebuffer.SetPixelTileColor(vert_a_pixel, 5, engine::graphics::Rgb8(255, 0, 0));
    //framebuffer.SetPixelTileColor(vert_b_pixel, 5, engine::graphics::Rgb8(255, 0, 0));
    //framebuffer.SetPixelTileColor(vert_c_pixel, 5, engine::graphics::Rgb8(255, 0, 0));

    engine::graphics::Rasterizer triangle_rasterizer(viewport);

    printf("CPU rasterizer is starting");

    triangle_rasterizer.Rasterize(engine::graphics::RasterizeMode::PrimitiveAndBoundingBox,
                                  screen_space_triangle,
                                  [&framebuffer](const engine::graphics::RasterizedPixel& raster_pixel) {
                                      framebuffer.SetPixel(raster_pixel.pixel);
                                      std::cout << "Rasterized pixel at (" << raster_pixel.pixel.x() << ", "
                                                << raster_pixel.pixel.y() << ")" << std::endl;
                                  });

    // Save the frame buffer to disk as a PPM image
    framebuffer.SaveToDisk("output.ppm");

    return 0;
}