/*
This file contains math-related functions
*/

#ifndef ENGINE_MATHS_UTILS_H
#define ENGINE_MATHS_UTILS_H

#include "Math.h"

namespace engine {
namespace Math {
// Interface
//==========

extern const float Pi;

float ConvertDegreesToRadians(const float i_degrees);

bool InRange(float valToCheck, float min, float max, bool minInclusive = true,
             bool maxInclusive = true);

float scaleAndBias(float valueToConvert, float oldRangeMin, float oldRangeMax,
                   float newRangeMin, float newRangeMax);

}  // namespace Math
}  

#endif
