#ifndef ENGINE_MATH_VECTOR_3_H_
#define ENGINE_MATH_VECTOR_3_H_
#include <string>

namespace engine
{
    class Vector3
    {
    public:
        Vector3  operator+(const Vector3& other) const;
        Vector3& operator+=(const Vector3& other);

        Vector3  operator-(const Vector3& other) const;
        Vector3& operator-=(const Vector3& other);
        Vector3  operator-() const;

        Vector3  operator*(float scalar) const;
        Vector3& operator*=(float scalar);

        Vector3 operator*(const Vector3& other) const;

        Vector3  operator/(float scalar) const;
        Vector3& operator/=(float scalar);

        Vector3& operator=(const Vector3& other);

        float   GetLength() const;
        float   Normalize();
        Vector3 CreateNormalized() const;

        float Dot(const Vector3& other) const;

        Vector3 Cross(const Vector3& other) const;

        bool operator==(const Vector3& other) const;
        bool operator!=(const Vector3& other) const;

        float operator[](int index) const;

        float ScalarTripleProduct(const Vector3& vec_a, const Vector3& vec_b) const;

        const float* AsFloatArray() const;

        Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);

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
        float  data_[3];
        float& x_ = data_[0];
        float& y_ = data_[1];
        float& z_ = data_[2];
    };

}  // namespace engine

#endif  // ENGINE_MATH_VECTOR_3_H_
