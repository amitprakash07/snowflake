
#include <iostream>

#include "core/common/perf_stats.h"
#include "core/maths/geometry/point.h"
#include "core/cpu_renderer/rasterizer.h"
#include "core/graphics/image_2d.h"
#include "core/graphics/image_generator.h"
#include "core/graphics/viewport.h"
#include "core/graphics/render_context.h"
#include "core/graphics/texture.h"
#include "core/graphics/text_overlay.h"

int main(int argc, char* argv[])
{
    amit::graphics::Viewport viewport({.value = 800}, {.value = 600});

    auto make_vertex = [&viewport](const amit::geometry::Point3D& position, const amit::graphics::Rgb8& color) {
        const float uv_x = position.x / static_cast<float>(viewport.GetWidth().value);
        const float uv_y = position.y / static_cast<float>(viewport.GetHeight().value);

        return amit::graphics::VertexAttributes{.position = position, .color = color, .uv = {uv_x, uv_y}};
    };

    amit::graphics::RenderPrimitive<amit::graphics::RenderPrimitiveType::kTriangle> screen_space_triangle_1{
        make_vertex(amit::geometry::Point3D{500u, 100u, 10u}, amit::graphics::kRgb8ColorRed),
        make_vertex(amit::geometry::Point3D{300u, 500u, 10u}, amit::graphics::kRgb8ColorGreen),
        make_vertex(amit::geometry::Point3D{700u, 500u, 10u}, amit::graphics::kRgb8ColorBlue)};

    amit::graphics::RenderPrimitive<amit::graphics::RenderPrimitiveType::kTriangle> screen_space_triangle_2{
        make_vertex(amit::geometry::Point3D{200u, 200u, 20u}, amit::graphics::kRgb8ColorYellow),
        make_vertex(amit::geometry::Point3D{200u, 550u, 20u}, amit::graphics::kRgb8ColorRed),
        make_vertex(amit::geometry::Point3D{500u, 550u, 20u}, amit::graphics::kRgb8ColorYellow)};

    // Rasterization logic goes here. For now, we just set the triangle vertices to red color.
    std::cout << "Rasterization started\n";

    amit::graphics::RenderFrame    render_frame(viewport);
    amit::graphics::RenderOutputs& render_outputs = render_frame.GetRenderOutputs();

    amit::graphics::Image2D<amit::graphics::Rgb8> checker_board =
        amit::graphics::ImageGenerator::GetCheckerBoard({.value = 200}, {.value = 200}, {.value = 8});
    amit::graphics::Texture<amit::graphics::Rgb8> checker_texture(checker_board);

    auto color_shader = [&render_outputs](const amit::render::cpu::RasterizedFragment& raster_fragment) {
        amit::graphics::ImageCoordinate image_coordinate{raster_fragment.coordinate.x, raster_fragment.coordinate.y};
        render_outputs.GetColorBuffer().SetImageData(image_coordinate, raster_fragment.color.ToRgb8());
    };

    auto checkerboard_shader = [&render_outputs,
                                &checker_texture](const amit::render::cpu::RasterizedFragment& raster_fragment) {
        amit::graphics::ImageCoordinate image_coordinate{raster_fragment.coordinate.x, raster_fragment.coordinate.y};

        if (raster_fragment.fragment_kind == amit::render::cpu::RasterizedFragment::Kind::BoundingBox)
        {
            render_outputs.GetColorBuffer().SetImageData(image_coordinate, raster_fragment.color.ToRgb8());
            return;
        }

        render_outputs.GetColorBuffer().SetImageData(image_coordinate, checker_texture.Sample(raster_fragment.uv));
    };

    amit::graphics::DrawContext draw_context(
        amit::graphics::PrimitiveDrawMode::kSolid, amit::graphics::DrawDebugFlag::kNone, true);

    amit::render::cpu::Rasterizer triangle_rasterizer;
    triangle_rasterizer.Rasterize(render_frame.GetRenderConfig(),
                                  render_frame.GetRenderState(),
                                  draw_context,
                                  screen_space_triangle_2,
                                  checkerboard_shader);
    triangle_rasterizer.Rasterize(render_frame.GetRenderConfig(),
                                  render_frame.GetRenderState(),
                                  draw_context,
                                  screen_space_triangle_1,
                                  color_shader);

    std::cout << "Rasterization Finished\n";

    std::string stats = amit::StatsCollector::GetInstance().GetAllStatsAsString();

    amit::graphics::ColorBuffer& color_buffer = render_outputs.GetColorBuffer();
    amit::graphics::TextOverlay::Render(stats, 10, 20, amit::graphics::kRgb8ColorWhite, color_buffer);

    // Save the frame buffer to disk as a PPM image
    amit::image::WriteColorBufferToPPM(color_buffer, "output.ppm");

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
}