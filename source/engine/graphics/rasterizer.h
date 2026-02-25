#ifndef ENGINE_GRAPHICS_RASTERIZER_H_
#define ENGINE_GRAPHICS_RASTERIZER_H_

#include <functional>

#include "pixel.h"
#include "engine/maths/triangle.h"

namespace engine
{
    namespace graphics
    {
        class Rasterizer
        {
        public:
            Rasterizer() = delete;

            Rasterizer(uint16_t width, uint16_t height, const engine::geometry::Triangle& triangle)

            {
                width;
                height;
                shape_data_.triangle_ = triangle;
            }

            void RasterizeEdgePixels(
                const std::function<void(const engine::graphics::PixelCoordinate&)>& pixel_callback) const;
            void RasterizeBoundPixel(
                const std::function<void(const engine::graphics::PixelCoordinate&)>& pixel_callback) const;

        private:
            enum class ShapeType
            {
                Triangle,
                Sphere,
                Rectangle
            };

            union ShapeData
            {
                engine::geometry::Triangle triangle_ = {};
            } shape_data_;
        };

    }  // namespace graphics
}  // namespace engine

#endif