/*
This file contains math-related functions
*/

#ifndef ENGINE_MATHS_UTILS_H
#define ENGINE_MATHS_UTILS_H

#include <numbers>

#include "vector3.h"

namespace amit::maths
{
    constexpr float kEpsilon  = 1.0e-9f;
    constexpr float kPi       = std::numbers::pi_v<float>;
    constexpr float kBigFloat = 1.0e30f;

    float ConvertDegreesToRadians(const float i_degrees);

    bool InRange(float valToCheck, float min, float max, bool minInclusive = true, bool maxInclusive = true);

    float scaleAndBias(float valueToConvert,
                       float oldRangeMin,
                       float oldRangeMax,
                       float newRangeMin,
                       float newRangeMax);

    void ClosestPointFromPointOnLineSegment(Vector3 c, Vector3 a, Vector3 b, float& t, Vector3& d);

    float SqDistPointSegment(Vector3 a, Vector3 b, Vector3 c);

}  // namespace amit::maths

#endif
