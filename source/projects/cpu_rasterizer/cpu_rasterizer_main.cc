
#include <iostream>

#include "core/common/perf_stats.h"
#include "core/maths/geometry/point.h"
#include "core/cpu_renderer/rasterizer.h"
#include "core/graphics/image_2d.h"
#include "core/graphics/image_generator.h"
#include "core/graphics/viewport.h"
#include "core/graphics/render_context.h"
#include "core/graphics/text_overlay.h"

int main(int argc, char* argv[])
{
    amit::graphics::Viewport viewport({.value = 800}, {.value = 600});

    amit::graphics::RenderPrimitive<amit::graphics::RenderPrimitiveType::kTriangle> screen_space_triangle_1{
        {.position = amit::geometry::Point3D{500u, 100u, 10u}, .color = amit::graphics::kRgb8ColorRed},
        {.position = amit::geometry::Point3D{300u, 500u, 10u}, .color = amit::graphics::kRgb8ColorGreen},
        {.position = amit::geometry::Point3D{700u, 500u, 10u}, .color = amit::graphics::kRgb8ColorBlue}};

    amit::graphics::RenderPrimitive<amit::graphics::RenderPrimitiveType::kTriangle> screen_space_triangle_2{
        {.position = amit::geometry::Point3D{200u, 200u, 20u}, .color = amit::graphics::kRgb8ColorYellow},
        {.position = amit::geometry::Point3D{200u, 550u, 20u}, .color = amit::graphics::kRgb8ColorRed},
        {.position = amit::geometry::Point3D{500u, 550u, 20u}, .color = amit::graphics::kRgb8ColorYellow}};

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
    triangle_rasterizer.Rasterize(render_context, draw_context, screen_space_triangle_2, pixel_shader);
    triangle_rasterizer.Rasterize(render_context, draw_context, screen_space_triangle_1, pixel_shader);

    std::cout << "Rasterization Finished\n";

    std::string stats = amit::StatsCollector::GetInstance().GetAllStatsAsString();

    amit::graphics::ColorBuffer& color_buffer = render_context.GetColorBuffer();
    amit::graphics::TextOverlay::Render(stats, 10, 20, amit::graphics::kRgb8ColorWhite, color_buffer);

    // Save the frame buffer to disk as a PPM image
    amit::image::WriteColorBufferToPPM(color_buffer, "output.ppm");

    amit::graphics::Image2D<amit::graphics::Rgb8> checker_board =
        amit::graphics::ImageGenerator::GetCheckerBoard({.value = 200}, {.value = 200}, {.value = 8});
    // Save the frame buffer to disk as a PPM image
    amit::image::WriteColorBufferToPPM(checker_board, "checker_board.ppm");

    amit::graphics::Image2D<amit::graphics::Rgb8> checker_board_8_8 =
        amit::graphics::ImageGenerator::GetCheckerBoard({.value = 16}, 8, 8);
    // Save the frame buffer to disk as a PPM image
    amit::image::WriteColorBufferToPPM(checker_board_8_8, "checker_board_8_8.ppm");

    std::cout << "Color buffer saved to disk\n";

    std::cout << stats;
    return 0;
}