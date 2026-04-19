#ifndef CORE_MATHS_AFFINE_TRANSFORM_H_
#define CORE_MATHS_AFFINE_TRANSFORM_H_

#include "matrix_4x4.h"
#include "Quaternion.h"
#include "Vector3.h"

namespace amit::maths
{
    enum RotationAxis
    {
        Up,
        Right,
        Forward
    };

    class Transform
    {
    public:
        Transform();
        Transform(const maths::Vector3& position, const Quaternion& orientation);
        maths::Vector3 GetPosition() const;
        Quaternion     GetOrientation() const;
        maths::Vector3 GetForwardVector() const;
        maths::Vector3 GetRightVector() const;
        maths::Vector3 GetUpVector() const;

        void SetForwardVector(const maths::Vector3& forWard_vector);
        void SetPosition(const maths::Vector3& new_position);
        void SetOrientation(const Quaternion& new_orientation);

        void RotateByEulerAngles(float angle_in_radians_for_pitch,
                                 float angle_in_radians_for_yaw,
                                 float angle_in_radians_for_roll);
        void GetEulerAngles() const;

        void MoveForward(float unit);
        void MoveBackWard(float unit);
        void MoveRight(float unit);
        void MoveLeft(float unit);
        void MoveUp(float unit);
        void MoveDown(float unit);
        void Move(maths::Vector3 along, float unit);

        // void Slide(Vector3 along, float unit);
        void Rotate(float angle_in_radians, RotationAxis rotation_axis);
        void Rotate(float angle_in_radians, maths::Vector3 arbitrary_axis);
        void Rotate(const Quaternion& rotor);

        Matrix4x4 GetLocalToWorldMatrix() const;

        void TransformTo(maths::Vector3& point) const;
        void TransformFrom(maths::Vector3& point) const;
        void VectorTransformTo(maths::Vector3& direction) const;
        void VectorTransformFrom(maths::Vector3& direction) const;

    private:
        maths::Vector3 position_;
        Quaternion     orientation_;
        maths::Vector3 forward_vector_;
        maths::Vector3 right_vector_;
        maths::Vector3 up_vector_;
        maths::Vector3 euler_angles_;
    };

}  // namespace engine

#endif
