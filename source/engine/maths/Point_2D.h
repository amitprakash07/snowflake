#ifndef ENGINE_MATHS_POINT_H_
#define ENGINE_MATHS_POINT_H_

namespace engine
{
    namespace geometry
    {
        class Point
        {
        public:
            float x() const
            {
                return x_;
            }
            float y() const
            {
                return y_;
            }
            Point(float x = 0.0f, float y = 0.0f);
        private:
            float x_;
            float y_;
        };
    }  // namespace geometry
}

#endif  // ENGINE_MATHS_POINT_H_