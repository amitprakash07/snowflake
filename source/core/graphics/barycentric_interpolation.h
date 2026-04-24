#ifndef CORE_GRAPHICS_BARYCENTRIC_INTERPOLATION_H_
#define CORE_GRAPHICS_BARYCENTRIC_INTERPOLATION_H_

#include "color.h"
#include "core/graphics/graphics_common.h"
#include "core/maths/geometry/geometry.h"

namespace amit::graphics
{
    inline FloatColor InterpolateColor(const FloatColor&               color1,
                                       const FloatColor&               color2,
                                       const FloatColor&               color3,
                                       geometry::BaryCentricCoordinate barycentric_coordinate)
    {
        FloatColor interpolated_color;
        interpolated_color.r = color1.r * barycentric_coordinate.alpha + color2.r * barycentric_coordinate.beta +
                               color3.r * barycentric_coordinate.gamma;
        interpolated_color.g = color1.g * barycentric_coordinate.alpha + color2.g * barycentric_coordinate.beta +
                               color3.g * barycentric_coordinate.gamma;
        interpolated_color.b = color1.b * barycentric_coordinate.alpha + color2.b * barycentric_coordinate.beta +
                               color3.b * barycentric_coordinate.gamma;
        return interpolated_color;
    }

    inline float InterpolateDepth(const float&                    data1,
                                  const float&                    data2,
                                  const float&                    data3,
                                  geometry::BaryCentricCoordinate barycentric_coordinate)
    {
        float interpolated_depth = data1 * barycentric_coordinate.alpha + data2 * barycentric_coordinate.beta +
                                   data3 * barycentric_coordinate.gamma;
        return interpolated_depth;
    }

    inline UVCoordinate InterpolateUV(const UVCoordinate&             uv1,
                                      const UVCoordinate&             uv2,
                                      const UVCoordinate&             uv3,
                                      geometry::BaryCentricCoordinate barycentric_coordinate)
    {
        UVCoordinate interpolated_uv;
        interpolated_uv.x = uv1.x * barycentric_coordinate.alpha + uv2.x * barycentric_coordinate.beta +
                            uv3.x * barycentric_coordinate.gamma;
        interpolated_uv.y = uv1.y * barycentric_coordinate.alpha + uv2.y * barycentric_coordinate.beta +
                            uv3.y * barycentric_coordinate.gamma;
        return interpolated_uv;
    }

}  // namespace amit::graphics

#endif