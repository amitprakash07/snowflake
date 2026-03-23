#ifndef ENGINE_GRAPHICS_VIEWPORT_H_
#define ENGINE_GRAPHICS_VIEWPORT_H_

#include <cstdint>

#include "engine/maths/point.h"

namespace engine
{
    namespace graphics
    {
        class Viewport
        {
        public:
            Viewport() = delete;

            Viewport(geometry::Point3D origin, uint16_t width, uint16_t height)
                : origin_(origin)
                , width_(width)
                , height_(height)
            {
            }

            Viewport(uint16_t width, uint16_t height)
                : origin_()
                , width_(width)
                , height_(height)
            {
            }

            inline uint16_t Width() const
            {
                return width_;
            }
            inline uint16_t Height() const
            {
                return height_;
            }

            inline const geometry::Point3D& Origin() const
            {
                return origin_;
            }

        private:
            geometry::Point3D origin_;
            uint16_t          width_;
            uint16_t          height_;
        };
    }  // namespace graphics
}  // namespace engine

#endif