#ifndef ENGINE_MATH_H_
#define ENGINE_MATH_H_

#include <numbers>

namespace engine
{
    constexpr float kEpsilon  = 1.0e-9f;
    constexpr float kPi       = std::numbers::pi_v<float>;
    constexpr float kBigFloat = 1.0e30f;

    class Vector3;

    namespace math
    {
        float ConvertDegreesToRadians(const float i_degrees);

        bool InRange(float valToCheck, float min, float max, bool minInclusive = true, bool maxInclusive = true);

        float scaleAndBias(float valueToConvert, float oldRangeMin, float oldRangeMax, float newRangeMin, float newRangeMax);

        void ClosestPointFromPointOnLineSegment(Vector3 c, Vector3 a, Vector3 b, float& t, Vector3& d);

        float SqDistPointSegment(Vector3 a, Vector3 b, Vector3 c);
    }  // namespace math

}  // namespace engine

#endif