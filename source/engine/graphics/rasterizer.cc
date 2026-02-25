#include "rasterizer.h"

void engine::graphics::Rasterizer::RasterizeEdgePixels(
    const std::function<void(const engine::graphics::PixelCoordinate&)>& pixel_callback) const
{
    auto RasterizeEdge = [&pixel_callback, this](const engine::geometry::Vertex& vert_a,
                                                 const engine::geometry::Vertex& vert_b) {
        // Equation of a line y - y1 = m(x - x1), where m = (y2 - y1) / (x2 - x1)
        float x1 = vert_a.x();
        float y1 = vert_a.y();

        float x2 = vert_b.x();
        float y2 = vert_b.y();

        float slope_denominator = x2 - x1;

        float slope = 0.0f;
        if (slope_denominator != 0)
        {
            slope = (y2 - y1) / slope_denominator;

            uint32_t start = 0;
            uint32_t end   = 0;

            if (x1 > x2)
            {
                start = static_cast<uint32_t>(x2);
                end   = static_cast<uint32_t>(x1);
            }
            else
            {
                start = static_cast<uint32_t>(x1);
                end   = static_cast<uint32_t>(x2);
            }

            for (uint32_t pixel_coordinate_x = start; pixel_coordinate_x < end; pixel_coordinate_x++)
            {
                float pixel_coordinate_y = y1 + (slope * (pixel_coordinate_x - x1));
                pixel_callback({static_cast<uint16_t>(pixel_coordinate_x), static_cast<uint16_t>(pixel_coordinate_y)});
            }
        }
    };

    RasterizeEdge(shape_data_.triangle_.Vert_A(), shape_data_.triangle_.Vert_B());
    RasterizeEdge(shape_data_.triangle_.Vert_B(), shape_data_.triangle_.Vert_C());
    RasterizeEdge(shape_data_.triangle_.Vert_C(), shape_data_.triangle_.Vert_A());
}

void engine::graphics::Rasterizer::RasterizeBoundPixel(
    const std::function<void(const engine::graphics::PixelCoordinate&)>& pixel_callback) const
{
    pixel_callback;
}