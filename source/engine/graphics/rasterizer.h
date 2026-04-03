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
        template <engine::geometry::PrimitiveTypeConcept Primitive>
        class PrimitiveRasterizer
        {
        public:
            PrimitiveRasterizer() = delete;

            PrimitiveRasterizer(const Viewport& viewport, const Primitive& primitive)
                : viewport_(viewport)
                , primitive_(primitive)
            {
            }

            virtual ~PrimitiveRasterizer() = default;

        protected:
            Primitive primitive_;
            Viewport  viewport_;
        };

        class RasterizerTrait
        {
        public:
            virtual void Rasterize(const std::function<void(const engine::graphics::Pixel&)>& pixel_callback) const = 0;

            virtual void RasterizeBoundingBox(
                const std::function<void(const engine::graphics::Pixel&)>& pixel_callback) const = 0;

            virtual ~RasterizerTrait() = default;
        };

        template <engine::geometry::PrimitiveTypeConcept Primitive>
        class Rasterizer : public PrimitiveRasterizer<Primitive>, public RasterizerTrait
        {
        public:
            Rasterizer(const Viewport& viewport, const Primitive& primitive)
                : PrimitiveRasterizer<Primitive>(viewport, primitive)
            {
            }
        };

        template <>
        class Rasterizer<engine::geometry::Triangle> : public PrimitiveRasterizer<engine::geometry::Triangle>,
                                                       public RasterizerTrait
        {
        public:
            Rasterizer(const Viewport& viewport, const engine::geometry::Triangle& primitive)
                : PrimitiveRasterizer<engine::geometry::Triangle>(viewport, primitive)
            {
            }

            void Rasterize(const std::function<void(const engine::graphics::Pixel&)>& pixel_callback) const override;

            void RasterizeBoundingBox(
                const std::function<void(const engine::graphics::Pixel&)>& pixel_callback) const override;
        };

        template <>
        class Rasterizer<engine::geometry::LineSegment> : public PrimitiveRasterizer<engine::geometry::LineSegment>,
                                                          RasterizerTrait
        {
        public:
            Rasterizer(const Viewport& viewport, const engine::geometry::LineSegment& primitive)
                : PrimitiveRasterizer<engine::geometry::LineSegment>(viewport, primitive)
            {
            }

            void Rasterize(const std::function<void(const engine::graphics::Pixel&)>& pixel_callback) const override;

            void RasterizeBoundingBox(
                const std::function<void(const engine::graphics::Pixel&)>& pixel_callback) const override;
        };
    }  // namespace graphics
}  // namespace engine

#endif