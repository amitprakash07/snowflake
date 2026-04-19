
#include <iostream>

#include "engine/common/perf_stats.h"
#include "engine/cpu_renderer/rasterizer.h"
#include "engine/graphics/image_2d.h"
#include "engine/graphics/pixel.h"
#include "engine/graphics/viewport.h"
#include "engine/graphics/render_context.h"
#include "engine/graphics/text_overlay.h"

int main(int argc, char* argv[])
{
    uint16_t                 width  = 800;
    uint16_t                 height = 600;
    amit::graphics::Viewport viewport(width, height);
    amit::geometry::Point3D  a{400u, 100u};
    amit::geometry::Point3D  b{200u, 500u};
    amit::geometry::Point3D  c{600u, 500u};
    amit::geometry::Triangle screen_space_triangle(a, b, c);

    // Rasterization logic goes here. For now, we just set the triangle vertices to red color.
    amit::graphics::Pixel vert_a_pixel = {static_cast<uint16_t>(a.x), static_cast<uint16_t>(a.y)};
    amit::graphics::Pixel vert_b_pixel = {static_cast<uint16_t>(b.x), static_cast<uint16_t>(b.y)};
    amit::graphics::Pixel vert_c_pixel = {static_cast<uint16_t>(c.x), static_cast<uint16_t>(c.y)};

    std::cout << "Rasterization started\n";

    amit::graphics::RenderContext render_context(viewport);

    auto pixel_shader = [](amit::graphics::RenderContext&            render_context,
                           amit::graphics::DrawContext&              draw_context,
                           const amit::render::cpu::RasterizedPixel& raster_pixel) {
        amit::graphics::ImageCoordinate image_coordinate{raster_pixel.pixel.x(), raster_pixel.pixel.y()};
        render_context.GetColorBuffer().SetImageData(image_coordinate, raster_pixel.pixel.GetRgb8Color());
    };

    amit::graphics::DrawContext draw_context(
        amit::graphics::PrimitiveDrawMode::kSolid, amit::graphics::DrawDebugFlag::kNone, true);

    amit::render::cpu::Rasterizer triangle_rasterizer;
    triangle_rasterizer.Rasterize(render_context, draw_context, screen_space_triangle, pixel_shader);

    std::cout << "Rasterization Finished\n";

    std::string stats = amit::StatsCollector::GetInstance().GetAllStatsAsString();

    amit::graphics::ColorBuffer& color_buffer = render_context.GetColorBuffer();
    amit::graphics::TextOverlay::Render(stats, 10, 20, amit::graphics::kRgb8ColorWhite, color_buffer);

    // Save the frame buffer to disk as a PPM image
    amit::image::WriteColorBufferToPPM(color_buffer, "output.ppm");
    std::cout << "Color buffer saved to disk\n";

    std::cout << stats;
    return 0;
}