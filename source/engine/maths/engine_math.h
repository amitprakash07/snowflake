#ifndef ENGINE_MATH_H_
#define ENGINE_MATH_H_

namespace engine
{
    extern constexpr float kEpsilon;
    extern constexpr float kPi;

    class Vector3;

    namespace math
    {
        float ConvertDegreesToRadians(const float i_degrees);

        bool InRange(float valToCheck, float min, float max, bool minInclusive = true, bool maxInclusive = true);

        float scaleAndBias(float valueToConvert,
                           float oldRangeMin,
                           float oldRangeMax,
                           float newRangeMin,
                           float newRangeMax);

        void ClosestPointFromPointOnLineSegment(Vector3 c, Vector3 a, Vector3 b, float& t, Vector3& d);

        float SqDistPointSegment(Vector3 a, Vector3 b, Vector3 c);
    }  // namespace math

}  // namespace engine

#endif