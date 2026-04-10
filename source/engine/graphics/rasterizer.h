#ifndef ENGINE_GRAPHICS_RASTERIZER_H_
#define ENGINE_GRAPHICS_RASTERIZER_H_

#include <functional>

#include "engine/maths/geometry_primitives.h"
#include "pixel.h"
#include "viewport.h"

namespace engine
{
    namespace graphics
    {
        enum class RasterizeMode : uint8_t
        {
            PrimitiveOnly,
            BoundingBoxOnly,
            PrimitiveAndBoundingBox
        };

        struct RasterizedPixel
        {
            enum class Kind : uint8_t
            {
                Primitive,
                BoundingBox
            };

            Pixel pixel;
            Kind  pixel_kind;
        };

        class Rasterizer
        {
        public:
            Rasterizer(const Viewport& viewport)
                : viewport_(viewport)
            {
            }

            template <engine::geometry::PrimitiveTypeConcept Primitive>
            void Rasterize(RasterizeMode,
                           const Primitive&,
                           const std::function<void(const engine::graphics::RasterizedPixel&)>&) const
            {
            }

        private:
            Viewport viewport_;
        };

        template <>
        void Rasterizer::Rasterize<geometry::Triangle>(
            RasterizeMode                                                                         raster_mode,
            const geometry::Triangle&                                                             triangle,
            const std::function<void(const engine::graphics::RasterizedPixel& rasterized_pixel)>& pixel_callback) const;

        template <>
        void Rasterizer::Rasterize<geometry::LineSegment>(
            RasterizeMode                                                                         raster_mode,
            const geometry::LineSegment&                                                          line,
            const std::function<void(const engine::graphics::RasterizedPixel& rasterized_pixel)>& pixel_callback) const;

    }  // namespace graphics
}  // namespace engine

#endif