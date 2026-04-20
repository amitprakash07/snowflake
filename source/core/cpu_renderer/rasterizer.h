#ifndef CORE_CPU_RENDERER_RASTERIZER_H_
#define CORE_CPU_RENDERER_RASTERIZER_H_

#include <functional>

#include "core/maths/geometry_primitives.h"
#include "core/graphics/pixel.h"
#include "core/graphics/render_context.h"
#include "core/graphics/render_primitives.h"

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

        template <amit::graphics::RenderPrimitiveType type>
        void Rasterize(
            graphics::RenderContext&,
            graphics::DrawContext&,
            const amit::graphics::RenderPrimitive<type>&,
            const std::function<void(graphics::RenderContext&, graphics::DrawContext&, const RasterizedPixel&)>&) const
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
    void Rasterizer::Rasterize<amit::graphics::RenderPrimitiveType::kTriangle>(
        graphics::RenderContext&                                                               render_context,
        graphics::DrawContext&                                                                 draw_context,
        const amit::graphics::RenderPrimitive<amit::graphics::RenderPrimitiveType::kTriangle>& triangle,
        const std::function<void(graphics::RenderContext&,
                                 graphics::DrawContext&,
                                 const RasterizedPixel& rasterized_pixel)>&                    pixel_callback) const;

    template <>
    void Rasterizer::Rasterize<amit::graphics::RenderPrimitiveType::kLine>(
        graphics::RenderContext&                                                           render_context,
        graphics::DrawContext&                                                             draw_context,
        const amit::graphics::RenderPrimitive<amit::graphics::RenderPrimitiveType::kLine>& line,
        const std::function<void(graphics::RenderContext&, graphics::DrawContext&, const RasterizedPixel&)>&
            pixel_callback) const;

}  // namespace amit::render::cpu

#endif