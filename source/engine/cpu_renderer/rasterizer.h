#ifndef ENGINE_GRAPHICS_RASTERIZER_H_
#define ENGINE_GRAPHICS_RASTERIZER_H_

#include <functional>

#include "engine/maths/geometry_primitives.h"
#include "engine/graphics/pixel.h"
#include "engine/graphics/render_context.h"

namespace amit::render::cpu
{
    struct RasterizedPixel
    {
        enum class Kind : uint8_t
        {
            Primitive,
            BoundingBox
        };

        graphics::Pixel pixel;
        Kind            pixel_kind;
    };

    class Rasterizer
    {
    public:
        Rasterizer() = default;

        template <amit::geometry::PrimitiveTypeConcept Primitive>
        void Rasterize(
            graphics::RenderContext&,
            graphics::DrawContext&,
            const Primitive&,
            const std::function<void(graphics::RenderContext&, graphics::DrawContext&, const RasterizedPixel&)>&)
            const
        {
        }

    private:
        void RenderPixel(graphics::RenderContext&                                            render_context,
                         graphics::DrawContext&                                              draw_context,
                         const RasterizedPixel&                                              pixel,
                         const std::function<void(graphics::RenderContext&,
                                                  graphics::DrawContext&,
                                                  const RasterizedPixel& rasterized_pixel)>& pixel_callback) const
        {
            pixel_callback(render_context, draw_context, pixel);
            draw_context.IncrementRenderStat(graphics::RenderStatCountKind::kRasterizedPixelCount);
        }
    };

    template <>
    void Rasterizer::Rasterize<geometry::Triangle>(
        graphics::RenderContext&                                            render_context,
        graphics::DrawContext&                                              draw_context,
        const geometry::Triangle&                                           triangle,
        const std::function<void(graphics::RenderContext&,
                                 graphics::DrawContext&,
                                 const RasterizedPixel& rasterized_pixel)>& pixel_callback) const;

    template <>
    void Rasterizer::Rasterize<geometry::LineSegment>(
        graphics::RenderContext&     render_context,
        graphics::DrawContext&       draw_context,
        const geometry::LineSegment& line,
        const std::function<void(graphics::RenderContext&, graphics::DrawContext&, const RasterizedPixel&)>&
            pixel_callback) const;

}  // namespace amit::render::cpu

#endif