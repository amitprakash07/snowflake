#ifndef ENGINE_COMMON_TIME_HELPER_H
#define ENGINE_COMMON_TIME_HELPER_H

#include <stdint.h>

namespace engine
{
    namespace time
    {
        inline uint64_t convertToMilliSeconds(const uint64_t i_seconds);
        inline uint64_t convertToSeconds(const uint64_t i_milliSeconds);
        inline uint32_t getTimeDiff(const uint64_t, const uint64_t);
        inline uint32_t getTickDifference(uint64_t, uint64_t);
    }  // namespace time
}  // namespace engine

#include "time_helper.inl"

#endif