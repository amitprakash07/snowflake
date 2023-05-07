#include <iostream>

#include "Transform.h"

Math::Transform::Transform() {
  position = Vector3(0.0f, 0.0f, 0.0f);
  orientation = Quaternion();
  forwardVector = Vector3(0, 0, -1);
  upVector = Vector3(0, 1, 0);
  rightVector = Vector3(1, 0, 0);
}

Math::Transform::Transform(Math::Vector3 iPosition,
                                   Math::Quaternion iOrientation) {
  position = iPosition;
  orientation = iOrientation;
  forwardVector = Vector3(0, 0, -1);
  upVector = Vector3(0, 1, 0);
  rightVector = Vector3(1, 0, 0);
  if (orientation != Quaternion::getIdentityQuartenion()) {
    Matrix4x4 nonTranslatingMatrix = Matrix4x4(orientation, position);
    forwardVector =
        nonTranslatingMatrix.mul(forwardVector, true).CreateNormalized();
    rightVector =
        nonTranslatingMatrix.mul(rightVector, true).CreateNormalized();
    upVector = nonTranslatingMatrix.mul(upVector, true).CreateNormalized();
  }
}

Math::Vector3 Math::Transform::getForwardVector() const {
  return forwardVector;
}

Math::Vector3 Math::Transform::getRightVector() const {
  return rightVector;
}

Math::Vector3 Math::Transform::getUpVector() const {
  return upVector;
}

Math::Matrix4x4 Math::Transform::getLocalToWorldMatrix() const {
  return (Matrix4x4(orientation, position));
}

void Math::Transform::TransformTo(Vector3& iPoint) const {
  iPoint = getLocalToWorldMatrix().mul(iPoint, false);
}

void Math::Transform::TransformFrom(Vector3& iPoint) const {
  iPoint = getLocalToWorldMatrix().mul(iPoint, false);
}

void Math::Transform::VectorTransformFrom(Vector3& iDir) const {
  iDir = getLocalToWorldMatrix().mul(iDir, true);
}

void Math::Transform::VectorTransformTo(Vector3& iDir) const {
  iDir = getLocalToWorldMatrix().getInverse().mul(iDir, true);
}

Math::Vector3 Math::Transform::getPosition() const {
  return position;
}

Math::Quaternion Math::Transform::getOrientation() const {
  return orientation;
}

void Math::Transform::setForwardVector(const Vector3 i_forwardVector) {
  forwardVector = i_forwardVector;
}

void Math::Transform::getEulerAngles() const {
  // to do
}

void Math::Transform::rotateByEulerAngles(
    const float angleInRadiansForPitch, const float angleInRadiansForYaw,
    const float angleInRadiansForRoll) {
  // to do
}

void Math::Transform::Move(Vector3 along, float unit) {
  if (along.GetLength() > 1) along = along.CreateNormalized();

  float angle = forwardVector.dot(along);
  this->Rotate(angle, along);
  this->MoveForward(unit);
}

void Math::Transform::MoveBackWard(float unit) {
  position = position + (-forwardVector) * unit;
}

void Math::Transform::MoveForward(float unit) {
  position = position + forwardVector * unit;
}

void Math::Transform::MoveLeft(float unit) {
  position = position - (rightVector * unit);
}

void Math::Transform::MoveRight(float unit) {
  position = position + (rightVector * unit);
}

void Math::Transform::MoveUp(float unit) {
  position = position + upVector * unit;
}

void Math::Transform::MoveDown(float unit) {
  position = position - upVector * unit;
}

void Math::Transform::Rotate(const float angleInRadians,
                                     RotationAxis iRotationAxis) {
  Vector3 axisOfRotation;
  switch (iRotationAxis) {
    case Up:
      axisOfRotation = upVector;
      break;
    case Right:
      axisOfRotation = rightVector;
      break;
    case Forward:
      axisOfRotation = forwardVector;
      break;
  }
  orientation = orientation * Quaternion(angleInRadians, axisOfRotation);
  Matrix4x4 localToWorld = Matrix4x4(orientation, position);

  switch (iRotationAxis) {
    case Up:
      forwardVector = localToWorld.mul(forwardVector, true).CreateNormalized();
      rightVector = localToWorld.mul(rightVector, true).CreateNormalized();
      break;
    case Right:
      forwardVector = localToWorld.mul(forwardVector, true).CreateNormalized();
      upVector = localToWorld.mul(upVector, true).CreateNormalized();
      break;
    case Forward:
      rightVector = localToWorld.mul(rightVector, true).CreateNormalized();
      upVector = localToWorld.mul(upVector, true).CreateNormalized();
      break;
  }
}

void Math::Transform::Rotate(const float angleInRadians,
                                     Vector3 arbitraryAxis) {
  if (arbitraryAxis.GetLength() > 1.0f)
    arbitraryAxis = arbitraryAxis.CreateNormalized();
  Quaternion rotor = Quaternion(angleInRadians, arbitraryAxis);
  orientation = orientation * rotor;
  Matrix4x4 localToWorld = Matrix4x4(orientation, position);
  forwardVector = localToWorld.mul(forwardVector, true).CreateNormalized();
  rightVector = localToWorld.mul(rightVector, true).CreateNormalized();
  upVector = localToWorld.mul(upVector, true).CreateNormalized();
}

void Math::Transform::rotate(const Quaternion rotor) {
  orientation = orientation * rotor;
}

void Math::Transform::setOrientation(Quaternion newOrientation) {
  orientation = newOrientation;
}

void Math::Transform::setPosition(Vector3 newPosition) {
  position = newPosition;
}

void Math::Transform::printTransform() const {
  std::cout << "Position is ";
  position.printVector();
  std::cout << "Orientation is ";
  orientation.printQuaternion();
}
