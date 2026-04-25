#ifndef CORE_CPU_RENDERER_RASTERIZER_H_
#define CORE_CPU_RENDERER_RASTERIZER_H_

#include <functional>

#include "core/maths/geometry/geometry.h"
#include "core/maths/geometry/geometry_primitives.h"
#include "core/graphics/render_context.h"
#include "core/graphics_common/render_primitives.h"

namespace amit::render::cpu
{
    struct RasterizedFragment
    {
        enum class Kind : uint8_t
        {
            Primitive,
            BoundingBox
        };

        graphics::PixelCoordinate       coordinate;
        graphics::FloatColor            color;
        graphics::UVCoordinate          uv = {};
        geometry::BaryCentricCoordinate barycentric_coordinate;
        float                           depth = 0.0f;
        Kind                            fragment_kind;
    };

    using FragmentShader = std::function<void(const RasterizedFragment&)>;

    class Rasterizer
    {
    public:
        Rasterizer() = default;

        template <amit::graphics::RenderPrimitiveType type>
        void Rasterize(const graphics::RenderConfig&,
                       graphics::RenderState&,
                       graphics::DrawOptions&,
                       const amit::graphics::RenderPrimitive<type>&,
                       const FragmentShader&) const
        {
        }
    };

    template <>
    void Rasterizer::Rasterize<amit::graphics::RenderPrimitiveType::kTriangle>(
        const graphics::RenderConfig&                                                          render_config,
        graphics::RenderState&                                                                 render_state,
        graphics::DrawOptions&                                                                 draw_options,
        const amit::graphics::RenderPrimitive<amit::graphics::RenderPrimitiveType::kTriangle>& triangle,
        const FragmentShader&                                                                  fragment_shader) const;

    template <>
    void Rasterizer::Rasterize<amit::graphics::RenderPrimitiveType::kLine>(
        const graphics::RenderConfig&                                                      render_config,
        graphics::RenderState&                                                             render_state,
        graphics::DrawOptions&                                                             draw_options,
        const amit::graphics::RenderPrimitive<amit::graphics::RenderPrimitiveType::kLine>& line,
        const FragmentShader&                                                              fragment_shader) const;

}  // namespace amit::render::cpu

#endif