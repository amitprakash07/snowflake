#ifndef ENGINE_MATHS_AFFINE_TRANSFORM_H_
#define ENGINE_MATHS_AFFINE_TRANSFORM_H_

#include "matrix_4x4.h"
#include "Quaternion.h"
#include "Vector3.h"

namespace engine
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
        Transform(const Vector3& position, const Quaternion& orientation);
        Vector3    GetPosition() const;
        Quaternion GetOrientation() const;
        Vector3    GetForwardVector() const;
        Vector3    GetRightVector() const;
        Vector3    GetUpVector() const;

        void SetForwardVector(const Vector3& forWard_vector);
        void SetPosition(const Vector3& new_position);
        void SetOrientation(const Quaternion& new_orientation);

        void RotateByEulerAngles(float angle_in_radians_for_pitch, float angle_in_radians_for_yaw, float angle_in_radians_for_roll);
        void GetEulerAngles() const;

        void MoveForward(float unit);
        void MoveBackWard(float unit);
        void MoveRight(float unit);
        void MoveLeft(float unit);
        void MoveUp(float unit);
        void MoveDown(float unit);
        void Move(Vector3 along, float unit);

        // void Slide(Vector3 along, float unit);
        void      Rotate(float angle_in_radians, RotationAxis rotation_axis);
        void      Rotate(float angle_in_radians, Vector3 arbitrary_axis);
        void      Rotate(const Quaternion& rotor);

        Matrix4x4 GetLocalToWorldMatrix() const;

        void      TransformTo(Vector3& point) const;
        void      TransformFrom(Vector3& point) const;
        void      VectorTransformTo(Vector3& direction) const;
        void      VectorTransformFrom(Vector3& direction) const;

    private:
        Vector3    position_;
        Quaternion orientation_;
        Vector3    forward_vector_;
        Vector3    right_vector_;
        Vector3    up_vector_;
        Vector3    euler_angles_;
    };

}  // namespace engine

#endif
