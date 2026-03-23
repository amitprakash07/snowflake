#ifndef ENGINE_MATHS_LINE_SEGMENT_H_
#define ENGINE_MATHS_LINE_SEGMENT_H_

#include "point.h"

namespace engine
{
    namespace geometry
    {
        class LineSegment : public Primitive
        {
        public:
            LineSegment() = delete;

            LineSegment(const Point3D& start, const Point3D& end)
                : Primitive(PrimitiveType::kLineSegment)
                , start_(start)
                , end_(end)

            {
            }

            LineSegment(const LineSegment& other)
                : start_(other.start_)
                , end_(other.end_)
            {
            }

            LineSegment& operator=(const LineSegment& other)
            {
                start_ = other.start_;
                end_   = other.end_;
                return *this;
            }

            inline const Point3D& Start() const
            {
                return start_;
            }

            inline const Point3D& End() const
            {
                return end_;
            }

        private:
            Point3D start_;
            Point3D end_;
        };
    }  // namespace geometry
}  // namespace engine

#endif