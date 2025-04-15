#ifndef ENGINE_MATH_VECTOR_4_H_
#define ENGINE_MATH_VECTOR_4_H_

#include <string>

namespace engine
{
    class Vector4
    {
    public:
        Vector4  operator+(const Vector4& other) const;
        Vector4& operator+=(const Vector4& other);

        Vector4  operator-(const Vector4& other) const;
        Vector4& operator-=(const Vector4& other);
        Vector4  operator-() const;

        Vector4  operator*(float scalar) const;
        Vector4& operator*=(float scalar);

        Vector4  operator/(float scalar) const;
        Vector4& operator/=(float scalar);

        Vector4& operator=(const Vector4& other);

        float   GetLength() const;
        void    Normalize();
        Vector4 GetNormalizedVec() const;

        float Dot(const Vector4& other) const;

        bool operator==(const Vector4& other) const;
        bool operator!=(const Vector4& other) const;

        const float* AsFloatArray() const;

        Vector4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);

        std::string ToString() const;

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

    private:
        float  data_[4];
        float& x_ = data_[0];
        float& y_ = data_[1];
        float& z_ = data_[2];
        float& w_ = data_[3];
    };

}  // namespace engine

#endif  // ENGINE_MATH_VECTOR_4_H_
