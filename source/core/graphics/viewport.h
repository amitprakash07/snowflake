#ifndef ENGINE_GRAPHICS_VIEWPORT_H_
#define ENGINE_GRAPHICS_VIEWPORT_H_

#include <cstdint>
#include <utility>

#include "core/maths/point.h"

namespace amit::graphics
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

        inline uint16_t GetWidth() const
        {
            return width_;
        }
        inline uint16_t GetHeight() const
        {
            return height_;
        }

        inline const geometry::Point3D& Origin() const
        {
            return origin_;
        }

        inline uint32_t ClampX(int32_t x) const
        {
            if (std::cmp_less(x, 0))
            {
                return 0;
            }

            if (std::cmp_greater(x, width_))
            {
                return width_;
            }

            return static_cast<uint32_t>(x);
        }

        inline uint32_t ClampY(int32_t y) const
        {
            if (std::cmp_less(y, 0))
            {
                return 0;
            }

            if (std::cmp_greater(y, height_))
            {
                return width_;
            }

            return static_cast<uint32_t>(y);
        }

        geometry::Point3D ClampToView(const geometry::Point3D& point) const
        {
            return geometry::Point3D{static_cast<float>(ClampX(static_cast<int32_t>(point.x))),
                                     static_cast<float>(ClampY(static_cast<int32_t>(point.y))),
                                     point.z};
        }

    private:
        geometry::Point3D origin_;
        uint16_t          width_;
        uint16_t          height_;
    };
}  // namespace amit::graphics

#endif