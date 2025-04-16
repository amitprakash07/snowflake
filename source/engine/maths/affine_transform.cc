
#include "affine_transform.h"

using namespace engine;

Transform::Transform()
{
    position_       = Vector3(0.0f, 0.0f, 0.0f);
    orientation_    = Quaternion();
    forward_vector_ = Vector3(0, 0, -1);
    up_vector_      = Vector3(0, 1, 0);
    right_vector_   = Vector3(1, 0, 0);
}

Transform::Transform(const Vector3& position, const Quaternion& orientation)
{
    position_       = position;
    orientation_    = orientation;
    forward_vector_ = Vector3(0, 0, -1);
    up_vector_      = Vector3(0, 1, 0);
    right_vector_   = Vector3(1, 0, 0);
    if (orientation_ != Quaternion::GetIdentityQuaternion())
    {
        Matrix4x4 non_translating_matrix = Matrix4x4(orientation_, position_);
        forward_vector_                  = non_translating_matrix.Mul(forward_vector_, true).CreateNormalized();
        right_vector_                    = non_translating_matrix.Mul(right_vector_, true).CreateNormalized();
        up_vector_                       = non_translating_matrix.Mul(up_vector_, true).CreateNormalized();
    }
}

Vector3 Transform::GetForwardVector() const
{
    return forward_vector_;
}

Vector3 Transform::GetRightVector() const
{
    return right_vector_;
}

Vector3 Transform::GetUpVector() const
{
    return up_vector_;
}

Matrix4x4 Transform::GetLocalToWorldMatrix() const
{
    return Matrix4x4{orientation_, position_};
}

void Transform::TransformTo(Vector3& point) const
{
    point = GetLocalToWorldMatrix().Mul(point, false);
}

void Transform::TransformFrom(Vector3& point) const
{
    point = GetLocalToWorldMatrix().Mul(point, false);
}

void Transform::VectorTransformFrom(Vector3& direction) const
{
    direction = GetLocalToWorldMatrix().Mul(direction, true);
}

void Transform::VectorTransformTo(Vector3& direction) const
{
    direction = GetLocalToWorldMatrix().GetInverse().Mul(direction, true);
}

Vector3 Transform::GetPosition() const
{
    return position_;
}

Quaternion Transform::GetOrientation() const
{
    return orientation_;
}

void Transform::SetForwardVector(const Vector3& forWard_vector)
{
    forward_vector_ = forWard_vector;
}

void Transform::GetEulerAngles() const
{
    // to do
}

void Transform::RotateByEulerAngles(float angle_in_radians_for_pitch, float angle_in_radians_for_yaw, float angle_in_radians_for_roll)
{
    // to do
}

void Transform::Move(Vector3 along, float unit)
{
    if (along.GetLength() > 1)
        along = along.CreateNormalized();

    float angle = forward_vector_.Dot(along);
    this->Rotate(angle, along);
    this->MoveForward(unit);
}

void Transform::MoveBackWard(float unit)
{
    position_ = position_ + (-forward_vector_) * unit;
}

void Transform::MoveForward(float unit)
{
    position_ = position_ + forward_vector_ * unit;
}

void Transform::MoveLeft(float unit)
{
    position_ = position_ - (right_vector_ * unit);
}

void Transform::MoveRight(float unit)
{
    position_ = position_ + (right_vector_ * unit);
}

void Transform::MoveUp(float unit)
{
    position_ = position_ + up_vector_ * unit;
}

void Transform::MoveDown(float unit)
{
    position_ = position_ - up_vector_ * unit;
}

void Transform::Rotate(float angle_in_radians, RotationAxis rotation_axis)
{
    Vector3 axis_of_rotation;
    switch (rotation_axis)
    {
    case Up:
        axis_of_rotation = up_vector_;
        break;
    case Right:
        axis_of_rotation = right_vector_;
        break;
    case Forward:
        axis_of_rotation = forward_vector_;
        break;
    }
    orientation_             = orientation_ * Quaternion(angle_in_radians, axis_of_rotation);
    Matrix4x4 local_to_world = Matrix4x4(orientation_, position_);

    switch (rotation_axis)
    {
    case Up:
        forward_vector_ = local_to_world.Mul(forward_vector_, true).CreateNormalized();
        right_vector_   = local_to_world.Mul(right_vector_, true).CreateNormalized();
        break;
    case Right:
        forward_vector_ = local_to_world.Mul(forward_vector_, true).CreateNormalized();
        up_vector_      = local_to_world.Mul(up_vector_, true).CreateNormalized();
        break;
    case Forward:
        right_vector_ = local_to_world.Mul(right_vector_, true).CreateNormalized();
        up_vector_    = local_to_world.Mul(up_vector_, true).CreateNormalized();
        break;
    }
}

void Transform::Rotate(float angle_in_radians, Vector3 arbitrary_axis)
{
    if (arbitrary_axis.GetLength() > 1.0f)
        arbitrary_axis = arbitrary_axis.CreateNormalized();
    Quaternion rotor         = Quaternion(angle_in_radians, arbitrary_axis);
    orientation_             = orientation_ * rotor;
    Matrix4x4 local_to_world = Matrix4x4(orientation_, position_);
    forward_vector_          = local_to_world.Mul(forward_vector_, true).CreateNormalized();
    right_vector_            = local_to_world.Mul(right_vector_, true).CreateNormalized();
    up_vector_               = local_to_world.Mul(up_vector_, true).CreateNormalized();
}

void Transform::Rotate(const Quaternion& rotor)
{
    orientation_ = orientation_ * rotor;
}

void Transform::SetOrientation(const Quaternion& new_orientation)
{
    orientation_ = new_orientation;
}

void Transform::SetPosition(const Vector3& new_position)
{
    position_ = new_position;
}
