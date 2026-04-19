#include "rasterizer.h"

#include "core/graphics/render_primitives.h"
#include "core/maths/geometry.h"

// Triangle
template <>
void amit::render::cpu::Rasterizer::Rasterize<amit::geometry::Triangle>(
    graphics::RenderContext&                                                                             render_context,
    graphics::DrawContext&                                                                               draw_context,
    const geometry::Triangle&                                                                            triangle,
    const std::function<void(graphics::RenderContext&, graphics::DrawContext&, const RasterizedPixel&)>& pixel_callback)
    const
{
    draw_context.StartRenderStatCollection(triangle);

    amit::geometry::AxisAlignedBoundingBox bounding_box = triangle.GetBoundingBox();

    std::array<RasterVertex, 3> raster_vertices = MakeRasterTriangleVertices(triangle);
    raster_vertices.at(0).color                 = graphics::kRgb8ColorRed;
    raster_vertices.at(1).color                 = graphics::kRgb8ColorGreen;
    raster_vertices.at(2).color                 = graphics::kRgb8ColorBlue;

    geometry::Point3D viewport_clamped_min = render_context.GetViewport().ClampToView(bounding_box.GetMin());
    geometry::Point3D viewport_clamped_max = render_context.GetViewport().ClampToView(bounding_box.GetMax());

    uint32_t x_start = static_cast<uint32_t>(viewport_clamped_min.x);
    uint32_t x_end   = static_cast<uint32_t>(viewport_clamped_max.x);

    uint32_t y_start = static_cast<uint32_t>(viewport_clamped_min.y);
    uint32_t y_end   = static_cast<uint32_t>(viewport_clamped_max.y);

    using EdgeFunctionValue = float;

    const std::array<geometry::ImplicitLineCoefficients, 3> triangle_edge_coefficients{
        geometry::MakeImplicitLineCoefficients(triangle.Edge_0().start, triangle.Edge_0().end),
        geometry::MakeImplicitLineCoefficients(triangle.Edge_1().start, triangle.Edge_1().end),
        geometry::MakeImplicitLineCoefficients(triangle.Edge_2().start, triangle.Edge_2().end)};

    std::array<EdgeFunctionValue, 3> triangle_edge_function_value_row_start{
        geometry::Orient2D(triangle_edge_coefficients[0], geometry::Point3D(x_start, y_start)),
        geometry::Orient2D(triangle_edge_coefficients[1], geometry::Point3D(x_start, y_start)),
        geometry::Orient2D(triangle_edge_coefficients[2], geometry::Point3D(x_start, y_start))};

    if (draw_context.GetDrawMode() == graphics::PrimitiveDrawMode::kSolid)
    {
        for (uint32_t y_iter = y_start; y_iter <= y_end; y_iter++)
        {
            std::array<EdgeFunctionValue, 3> edge_value           = triangle_edge_function_value_row_start;
            bool                             is_first_or_last_row = (y_iter == y_start || y_iter == y_end);

            for (uint32_t x_iter = x_start; x_iter <= x_end; x_iter++)
            {
                bool is_first_or_last_column = (x_iter == x_start || x_iter == x_end);

                if ((edge_value[0] < 0 && edge_value[1] < 0 && edge_value[2] < 0) ||
                    (edge_value[0] >= 0 && edge_value[1] >= 0 && edge_value[2] >= 0))
                {
                    geometry::BaryCentricCoordinate barycentric_coordinate = geometry::CalculateBaryCentricCoordinate(
                        triangle.VertA(), triangle.VertB(), triangle.VertC(), geometry::Point3D(x_iter, y_iter));

                    amit::graphics::FloatColor interpolated_color =
                        amit::graphics::InterpolateColor(raster_vertices[0].color.ToFloatColor(),
                                                           raster_vertices[1].color.ToFloatColor(),
                                                           raster_vertices[2].color.ToFloatColor(),
                                                           barycentric_coordinate);

                    RasterizedPixel primitive_pixel{.pixel      = {x_iter, y_iter, interpolated_color.ToRgb8()},
                                                    .pixel_kind = RasterizedPixel::Kind::Primitive};

                    RenderPixel(render_context, draw_context, primitive_pixel, pixel_callback);
                }

                if (draw_context.GetDrawDebugFlag() == graphics::DrawDebugFlag::kWireframeBoundingBox &&
                    (is_first_or_last_column || is_first_or_last_row))
                {
                    RasterizedPixel bounding_box_pixel{.pixel      = {x_iter, y_iter, graphics::kRgb8ColorGreen},
                                                       .pixel_kind = RasterizedPixel::Kind::BoundingBox};
                    RenderPixel(render_context, draw_context, bounding_box_pixel, pixel_callback);
                }

                edge_value[0] += triangle_edge_coefficients[0].a;
                edge_value[1] += triangle_edge_coefficients[1].a;
                edge_value[2] += triangle_edge_coefficients[2].a;
            }

            triangle_edge_function_value_row_start[0] += triangle_edge_coefficients[0].b;
            triangle_edge_function_value_row_start[1] += triangle_edge_coefficients[1].b;
            triangle_edge_function_value_row_start[2] += triangle_edge_coefficients[2].b;
        }
    }
    else if (draw_context.GetDrawMode() == graphics::PrimitiveDrawMode::kNone &&
             draw_context.GetDrawDebugFlag() == graphics::DrawDebugFlag::kWireframeBoundingBox)
    {
        for (uint32_t y_iter = y_start; y_iter <= y_end; y_iter++)
        {
            bool is_first_or_last_row = (y_iter == y_start || y_iter == y_end);

            for (uint32_t x_iter = x_start; x_iter <= x_end; x_iter++)
            {
                bool is_first_or_last_column = (x_iter == x_start || x_iter == x_end);

                if (is_first_or_last_column || is_first_or_last_row)
                {
                    RasterizedPixel bounding_box_pixel{.pixel      = {x_iter, y_iter, graphics::kRgb8ColorGreen},
                                                       .pixel_kind = RasterizedPixel::Kind::BoundingBox};
                    RenderPixel(render_context, draw_context, bounding_box_pixel, pixel_callback);
                }
            }
        }
    }
    else if (draw_context.GetDrawMode() == graphics::PrimitiveDrawMode::kWireframe)
    {
        Rasterize(render_context, draw_context, triangle.Edge_0().ToLineSegment(), pixel_callback);
        Rasterize(render_context, draw_context, triangle.Edge_1().ToLineSegment(), pixel_callback);
        Rasterize(render_context, draw_context, triangle.Edge_2().ToLineSegment(), pixel_callback);
    }

    draw_context.EndRenderStatCollection();
}

// Line Segment
template <>
void amit::render::cpu::Rasterizer::Rasterize<amit::geometry::LineSegment>(
    graphics::RenderContext&                                                                             render_context,
    graphics::DrawContext&                                                                               draw_context,
    const amit::geometry::LineSegment&                                                                 line,
    const std::function<void(graphics::RenderContext&, graphics::DrawContext&, const RasterizedPixel&)>& pixel_callback)
    const
{
    draw_context.StartRenderStatCollection(line);

    auto RasterizeEdgeUsingLineEquation = [this, &render_context, &draw_context, &pixel_callback, &line]() {
        // Equation of a line y - y1 = m(x - x1), where m = (y2 - y1) / (x2 - x1)
        float x1 = line.Start().x;
        float y1 = line.Start().y;

        float x2 = line.End().x;
        float y2 = line.End().y;

        float slope_denominator = x2 - x1;

        if (slope_denominator != 0.0f)
        {
            float slope = 0.0f;
            slope       = (y2 - y1) / slope_denominator;

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
                float pixel_coordinate_y = y1 + (slope * (static_cast<float>(pixel_coordinate_x) - x1));

                RasterizedPixel primitive_pixel{.pixel      = {static_cast<uint16_t>(pixel_coordinate_x),
                                                               static_cast<uint16_t>(pixel_coordinate_y),
                                                               graphics::kRgb8ColorRed},
                                                .pixel_kind = RasterizedPixel::Kind::Primitive};
                RenderPixel(render_context, draw_context, primitive_pixel, pixel_callback);
            }
        }
    };

    auto RasterizeEdgeUsingMidPointAlgo = [this, &render_context, &draw_context, &pixel_callback, line]() {
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
        int32_t x1 = static_cast<int32_t>(line.Start().x);
        int32_t y1 = static_cast<int32_t>(line.Start().y);

        int32_t x2 = static_cast<int32_t>(line.End().x);
        int32_t y2 = static_cast<int32_t>(line.End().y);

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
                RasterizedPixel primitive_pixel{
                    .pixel      = {static_cast<uint16_t>(x), static_cast<uint16_t>(y), graphics::kRgb8ColorRed},
                    .pixel_kind = RasterizedPixel::Kind::Primitive};
                RenderPixel(render_context, draw_context, primitive_pixel, pixel_callback);

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
                RasterizedPixel primitive_pixel{
                    .pixel      = {static_cast<uint16_t>(x), static_cast<uint16_t>(y), graphics::kRgb8ColorRed},
                    .pixel_kind = RasterizedPixel::Kind::Primitive};
                RenderPixel(render_context, draw_context, primitive_pixel, pixel_callback);
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

    bool use_line_equation = false;

    if (use_line_equation)
    {
        RasterizeEdgeUsingLineEquation();
    }
    else
    {
        RasterizeEdgeUsingMidPointAlgo();
    }

    draw_context.EndRenderStatCollection();
}
