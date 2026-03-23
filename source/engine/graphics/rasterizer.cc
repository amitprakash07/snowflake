#include <iostream>

#include "rasterizer.h"

// Triangle
void engine::graphics::Rasterizer<engine::geometry::Triangle>::RasterizePixelCoordinate(
    const std::function<void(const engine::graphics::PixelCoordinate&)>& pixel_callback) const
{
    Rasterizer<geometry::LineSegment> line_segment_ab(viewport_,
                                                      geometry::LineSegment(primitive_.Vert_A(), primitive_.Vert_B()));
    line_segment_ab.RasterizePixelCoordinate(pixel_callback);

    Rasterizer<geometry::LineSegment> line_segment_bc(viewport_,
                                                      geometry::LineSegment(primitive_.Vert_B(), primitive_.Vert_C()));
    line_segment_bc.RasterizePixelCoordinate(pixel_callback);

    Rasterizer<geometry::LineSegment> line_segment_ca(viewport_,
                                                      geometry::LineSegment(primitive_.Vert_C(), primitive_.Vert_A()));
    line_segment_ca.RasterizePixelCoordinate(pixel_callback);
}

void engine::graphics::Rasterizer<engine::geometry::Triangle>::RasterizeBoundingBoxPixel(
    const std::function<void(const engine::graphics::PixelCoordinate&)>& pixel_callback) const
{
    pixel_callback;
}

void engine::graphics::Rasterizer<engine::geometry::Triangle>::RasterizePixels(
    const std::function<void(const engine::graphics::Pixel&)>& pixel_callback) const
{
    Rasterizer<geometry::LineSegment> line_segment_ab(viewport_,
                                                      geometry::LineSegment(primitive_.Vert_A(), primitive_.Vert_B()));
    line_segment_ab.RasterizePixels(pixel_callback);

    Rasterizer<geometry::LineSegment> line_segment_bc(viewport_,
                                                      geometry::LineSegment(primitive_.Vert_B(), primitive_.Vert_C()));
    line_segment_bc.RasterizePixels(pixel_callback);

    Rasterizer<geometry::LineSegment> line_segment_ca(viewport_,
                                                      geometry::LineSegment(primitive_.Vert_C(), primitive_.Vert_A()));
    line_segment_ca.RasterizePixels(pixel_callback);
}

// Line Segment
void engine::graphics::Rasterizer<engine::geometry::LineSegment>::RasterizePixelCoordinate(
    const std::function<void(const engine::graphics::PixelCoordinate&)>& pixel_callback) const
{
    pixel_callback;
}

void engine::graphics::Rasterizer<engine::geometry::LineSegment>::RasterizeBoundingBoxPixel(
    const std::function<void(const engine::graphics::PixelCoordinate&)>& pixel_callback) const
{
    pixel_callback;
}

void engine::graphics::Rasterizer<engine::geometry::LineSegment>::RasterizePixels(
    const std::function<void(const engine::graphics::Pixel&)>& pixel_callback) const
{
    auto RasterizeEdge = [&pixel_callback, this]() {
        // Equation of a line y - y1 = m(x - x1), where m = (y2 - y1) / (x2 - x1)
        float x1 = this->primitive_.Start().x;
        float y1 = this->primitive_.Start().y;

        float x2 = this->primitive_.End().x;
        float y2 = this->primitive_.End().y;

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
                Pixel pixel{static_cast<uint16_t>(pixel_coordinate_x), static_cast<uint16_t>(pixel_coordinate_y)};
                pixel.SetColor(kRed);
                pixel_callback(pixel);
            }
        }
    };

    RasterizeEdge();
    //auto RasterizeEdge_MidPointAlgo = [&pixel_callback, this](const engine::geometry::Vertex& vert_a,
    //                                                          const engine::geometry::Vertex& vert_b) {
    //    // Equation of a line y - y1 = m(x - x1), where m = (y2 - y1) / (x2 - x1)
    //    uint32_t x1 = static_cast<uint32_t>(vert_a.x);
    //    uint32_t y1 = static_cast<uint32_t>(vert_a.y);

    //    uint32_t x2 = static_cast<uint32_t>(vert_b.x);
    //    uint32_t y2 = static_cast<uint32_t>(vert_b.y);
    //};
}
