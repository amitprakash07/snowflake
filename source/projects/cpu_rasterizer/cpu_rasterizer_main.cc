
#include <iostream>

#include "core/common/perf_stats.h"
#include "core/cpu_renderer/rasterizer.h"
#include "core/graphics/image_2d.h"
#include "core/graphics/viewport.h"
#include "core/graphics/render_context.h"
#include "core/graphics/text_overlay.h"

int main(int argc, char* argv[])
{
    uint16_t                 width  = 800;
    uint16_t                 height = 600;
    amit::graphics::Viewport viewport(width, height);

    amit::geometry::Point3D  a{400u, 100u};
    amit::geometry::Point3D  b{200u, 500u};
    amit::geometry::Point3D  c{600u, 500u};

    std::array<amit::graphics::VertexAttributes, 3> screen_space_triangle_vertices;

    screen_space_triangle_vertices[0] =
        amit::graphics::VertexAttributes{.position = a, .color = amit::graphics::kRgb8ColorRed};
    screen_space_triangle_vertices[1] =
        amit::graphics::VertexAttributes{.position = b, .color = amit::graphics::kRgb8ColorGreen};
    screen_space_triangle_vertices[2] =
        amit::graphics::VertexAttributes{.position = c, .color = amit::graphics::kRgb8ColorBlue};

    amit::graphics::RenderPrimitive<amit::graphics::RenderPrimitiveType::kTriangle> screen_space_triangle(
        screen_space_triangle_vertices);

    // Rasterization logic goes here. For now, we just set the triangle vertices to red color.
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