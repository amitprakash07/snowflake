
#include <iostream>

#include "engine/common/maths_util.h"
#include "engine/common/perf_stats.h"
#include "engine/graphics/pixel.h"
#include "engine/graphics/viewport.h"
#include "engine/graphics/ppm_image.h"
#include "engine/graphics/rasterizer.h"
#include "engine/graphics/text_overlay.h"

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

    std::cout << "Rasterization started\n";

    /*{
        engine::graphics::RenderContext render_context(viewport, engine::graphics::RasterizeMode::PrimitiveOnly, true);
        engine::graphics::Rasterizer    line_rasterizer;
        line_rasterizer.Rasterize(render_context,
                                  screen_space_triangle.Edge_0().ToLineSegment(),
                                  [&framebuffer](const engine::graphics::RasterizedPixel& raster_pixel) {
                                      engine::graphics::Pixel pixel = raster_pixel.pixel;
                                      pixel.SetColor(engine::graphics::kRgb8ColorBlue);
                                      framebuffer.SetPixel(pixel);
                                  });

        line_rasterizer.Rasterize(render_context,
                                  screen_space_triangle.Edge_1().ToLineSegment(),
                                  [&framebuffer](const engine::graphics::RasterizedPixel& raster_pixel) {
                                      engine::graphics::Pixel pixel = raster_pixel.pixel;
                                      pixel.SetColor(engine::graphics::kRgb8ColorBlue);
                                      framebuffer.SetPixel(pixel);
                                  });

        line_rasterizer.Rasterize(render_context,
                                  screen_space_triangle.Edge_2().ToLineSegment(),
                                  [&framebuffer](const engine::graphics::RasterizedPixel& raster_pixel) {
                                      engine::graphics::Pixel pixel = raster_pixel.pixel;
                                      pixel.SetColor(engine::graphics::kRgb8ColorBlue);
                                      framebuffer.SetPixel(pixel);
                                  });
    }*/

    {
        engine::graphics::Rasterizer    triangle_rasterizer;
        engine::graphics::RenderContext render_context(viewport, engine::graphics::RasterizeMode::PrimitiveAndBoundingBox, true);
        triangle_rasterizer.Rasterize(render_context,
                                      screen_space_triangle,
                                      [&framebuffer](const engine::graphics::RasterizedPixel& raster_pixel) {
                                          framebuffer.SetPixel(raster_pixel.pixel);
                                      });
    }

    std::cout << "Rasterization Finished\n";
    std::cout << "Frame buffer saved to disk\n";

    std::string stats = engine::StatsCollector::GetInstance().GetAllStatsAsString();
    std::cout << stats;
    engine::graphics::TextOverlay::Render(stats, 10, 20, engine::graphics::kRgb8ColorWhite, framebuffer);

    // Save the frame buffer to disk as a PPM image
    framebuffer.SaveToDisk("output.ppm");
    return 0;
}