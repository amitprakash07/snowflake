#ifndef CORE_GRAPHICS_RASTER_PRIMITIVES_H_
#define CORE_GRAPHICS_RASTER_PRIMITIVES_H_

#include "core/maths/point.h"
#include "core/maths/triangle.h"

#include "color.h"

namespace amit::render::cpu
{
    struct RasterVertex
    {
        geometry::Point3D position;
        graphics::Rgb8    color;
    };

    inline std::array<RasterVertex, 3> MakeRasterTriangleVertices(const geometry::Triangle& triangle)
    {
        std::array<RasterVertex, 3> raster_vertices{
            RasterVertex{.position = triangle.VertA(), .color = graphics::Rgb8()},
            RasterVertex{.position = triangle.VertB(), .color = graphics::Rgb8()},
            RasterVertex{.position = triangle.VertC(), .color = graphics::Rgb8()}};

        return raster_vertices;
    }

    class RasterTriangle
    {
    public:
        RasterTriangle(const RasterVertex& vert_a, const RasterVertex& vert_b, const RasterVertex& vert_c)
            : vert_a_(vert_a)
            , vert_b_(vert_b)
            , vert_c_(vert_c)
        {
        }

        RasterTriangle(const std::array<RasterVertex, 3>& raster_vertices)
            : vert_a_(raster_vertices[0])
            , vert_b_(raster_vertices[1])
            , vert_c_(raster_vertices[2])
        {
        }

        const RasterVertex& VertA() const
        {
            return vert_a_;
        }

        const RasterVertex& VertB() const
        {
            return vert_b_;
        }

        const RasterVertex& VertC() const
        {
            return vert_c_;
        }

    private:
        RasterVertex vert_a_;
        RasterVertex vert_b_;
        RasterVertex vert_c_;
    };

}  // namespace amit::render::cpu

#endif