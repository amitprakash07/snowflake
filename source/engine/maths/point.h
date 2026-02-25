#ifndef ENGINE_MATHS_POINT_H_
#define ENGINE_MATHS_POINT_H_

namespace engine
{
    namespace geometry
    {
        class Point2D
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

            Point2D(float x = 0.0f, float y = 0.0f)
                : x_(x)
                , y_(y)
            {
            }

        private:
            float x_;
            float y_;
        };

        class Point3D
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

            float z() const
            {
                return z_;
            }
            Point3D(float x = 0.0f, float y = 0.0f, float z = 0.0f)
                : x_(x)
                , y_(y)
                , z_(z)
            {
            }

        private:
            float x_;
            float y_;
            float z_;
        };
    }  // namespace geometry
}  // namespace engine

#endif  // ENGINE_MATHS_POINT_H_