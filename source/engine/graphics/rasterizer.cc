#include <iostream>

#include "rasterizer.h"

// Triangle
void engine::graphics::Rasterizer<engine::geometry::Triangle>::Rasterize(
    const std::function<void(const engine::graphics::Pixel&)>& pixel_callback) const
{
    Rasterizer<geometry::LineSegment> line_segment_ab(viewport_,
                                                      geometry::LineSegment(primitive_.Vert_A(), primitive_.Vert_B()));
    line_segment_ab.Rasterize(pixel_callback);

    Rasterizer<geometry::LineSegment> line_segment_bc(viewport_,
                                                      geometry::LineSegment(primitive_.Vert_B(), primitive_.Vert_C()));
    line_segment_bc.Rasterize(pixel_callback);

    Rasterizer<geometry::LineSegment> line_segment_ca(viewport_,
                                                      geometry::LineSegment(primitive_.Vert_C(), primitive_.Vert_A()));
    line_segment_ca.Rasterize(pixel_callback);
}

void engine::graphics::Rasterizer<engine::geometry::Triangle>::RasterizeBoundingBox(
    const std::function<void(const engine::graphics::Pixel&)>& pixel_callback) const
{
    pixel_callback;
}

// Line Segment
void engine::graphics::Rasterizer<engine::geometry::LineSegment>::Rasterize(
    const std::function<void(const engine::graphics::Pixel&)>& pixel_callback) const
{
    auto RasterizeEdgeUsingLineEquation = [&pixel_callback, this]() {
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

    auto RasterizeEdgeUsingMidPointAlgo = [&pixel_callback, this]() {
        /* Bresenham Mid-point algo
         * 1. Calculate the differences dx and dy between the start and end points of the line.
         * F(x,y) = ax + by + c
         * F(x0,y0) = ax0 + by0 + c
         * F(x1,y1) = ax1 + by1 + c
         * F(x) => y = mx + b 
         * m = dy/dx
         * F(x,y) = 0 => (dy/dx)x - y + b
         * F(x,y) = 0 => dy*x - dx*y + b*dx
         * F(x,y) = Ax + By + C => A = dy, B = -dx, C = b*dx
         * Decision parameter Initial (d) = F(M) - F(x0, y0) where M is the mid-point of (x0,y0) and (x0 + 1, y0 + 1) 
         * F(M) = F(x0 +1, y0 + 1/2), and F(x0, y0) = 0
         * d = F(x0 +1, y0 + 1/2) = A(x0 +1) + B(y0 + 1/2) + C
         * d = Ax0 + A + By0 + B/2 + C
         * d = Ax0 + By0 + C + A + B/2
         * d = A + B/2 as F(x0, y0) = 0 => Ax0 + By0 + C = 0
         * d = dy + (-dx)/2 => d = dy - dx/2 => d = 2*dy - dx
         *
         * All of this for slope between 0 and 1, i.e. dx > dy
         * For other case where m > 1, we need to swap the role of x and y. It means y will move every time while
         * x change will be based on d.
         */
        int32_t x1 = static_cast<int32_t>(this->primitive_.Start().x);
        int32_t y1 = static_cast<int32_t>(this->primitive_.Start().y);

        int32_t x2 = static_cast<int32_t>(this->primitive_.End().x);
        int32_t y2 = static_cast<int32_t>(this->primitive_.End().y);

        int32_t dx = x2 - x1;
        int32_t dy = y2 - y1;

        int32_t sx = dx >= 0 ? 1 : -1;  // Step direction for x
        int32_t sy = dy >= 0 ? 1 : -1;  // Step direction for y

        dx = abs(dx);
        dy = abs(dy);

        int32_t x = x1;
        int32_t y = y1;

        if (dx >= dy)
        {
            int32_t d = 2 * dy - dx;  // Initial decision parameter

            for (int32_t i = 0; i <= dx; ++i)
            {
                Pixel draw_pixel{static_cast<uint16_t>(x), static_cast<uint16_t>(y), kRed};
                pixel_callback(draw_pixel);
                x = x + sx;  // Move to the next x coordinate
                if (d > 0)
                {
                    y = y + sy;               // Move to the next y coordinate
                    d = d + (2 * (dy - dx));  // Update decision parameter for the next point
                }
                else
                {
                    d = d + (2 * dy);  // Update decision parameter for the next point
                }
            }
        }
        else
        {
            int32_t d = 2 * dx - dy;  // Initial decision parameter

            for (int32_t i = 0; i <= dy; ++i)
            {
                Pixel draw_pixel{static_cast<uint16_t>(x), static_cast<uint16_t>(y), kRed};
                pixel_callback(draw_pixel);
                y = y + sy;  // Move to the next y coordinate
                if (d > 0)
                {
                    x = x + sx;               // Move to the next x coordinate
                    d = d + (2 * (dx - dy));  // Update decision parameter for the next point
                }
                else
                {
                    d = d + (2 * dx);  // Update decision parameter for the next point
                }
            }
        }
    };

    //RasterizeEdgeUsingLineEquation();
    RasterizeEdgeUsingMidPointAlgo();
}

void engine::graphics::Rasterizer<engine::geometry::LineSegment>::RasterizeBoundingBox(
    const std::function<void(const engine::graphics::Pixel&)>& pixel_callback) const
{
    pixel_callback;
}
