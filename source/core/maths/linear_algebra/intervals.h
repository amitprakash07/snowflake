#ifndef CORE_MATHS_LINEAR_ALGEBRA_INTERVALS_H_
#define CORE_MATHS_LINEAR_ALGEBRA_INTERVALS_H_

#include <type_traits>

namespace amit::maths
{
    enum class IntervalType : uint8_t
    {
        kClosed,
        kOpen,
        kLeftOpen,
        kRightOpen
    };

    template <typename T, T begin, T end, IntervalType left, IntervalType right>
        requires std::is_arithmetic_v<T>
    class Interval
    {
    public:
        Interval() = default;

        T GetStart() const
        {
            return start_;
        }

        T GetEnd() const
        {
            return end_;
        }

    private:
        T start_ = begin;
        T end_   = end;
    };

    template <typename T, T begin, T end>
    using ClosedInterval = Interval<T, begin, end, IntervalType::kClosed, IntervalType::kClosed>;

    template <typename T, T begin, T end>
    using OpenInterval = Interval<T, begin, end, IntervalType::kOpen, IntervalType::kOpen>;

    template <typename T, T begin, T end>
    using LeftOpenInterval = Interval<T, begin, end, IntervalType::kLeftOpen, IntervalType::kClosed>;

    template <typename T, T begin, T end>
    using RightOpenInterval = Interval<T, begin, end, IntervalType::kClosed, IntervalType::kOpen>;

}  // namespace amit::maths

#endif  // CORE_MATHS_LINEAR_ALGEBRA_INTERVALS_H_