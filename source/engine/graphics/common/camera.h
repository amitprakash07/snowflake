#ifndef __CAMERA_H
#define __CAMERA_H

#include "../../../Core/Utilities/IMessageHandler.h"
#include "../../../Core/Utilities/SharedPointer.h"
#include "../enginedefs.h"
#include "Object.h"

namespace engine {
class Camera : public IMessageHandler, Object {
 public:
  static SharedPointer<Camera> CreateCamera(
      std::string, Math::Vector3, Math::Quaternion, float i_fieldofView = 60.0f,
      float i_aspectRatio = static_cast<float>(800 / 600));
  Math::Transform getTransform() override;
  void setTransform(
      Math::Vector3,
      Math::Quaternion = Math::Quaternion()) override;
  void resetTransform() override;
  void draw(bool) override {}
  void setRenderable(bool iRenderable) override {}
  void HandleMessage(utils::StringHash&,
                     SharedPointer<RTTI> i_MessageSender,
                     void* i_pMessageData) override;
  bool IsPlayer() override;
  void setPlayer(bool i_isPlayer) override;
  // void setCameraController(IObjectController*);
  void setFieldOfView(float);
  float getFieldOfView() const;
  void setAspectRatio(float);
  float getAspectRatio() const;
  bool isBothSameType(SharedPointer<RTTI>, std::string) const override {
    return true;
  }
  void activateCamera(bool);
  bool isActive() const;
  std::string getTypeInfo() const override { return ""; }
  void setNearPlane(float i_nearPlane);
  void setFarPlane(float i_farPlane);
  float getNearPlane() const;
  float getFarPlane() const;
  std::string getCameraName() const;
  bool isRenderable() const override { return false; }
  bool isDebugObject() const override { return false; }
  Math::Vector3 getForwardVector() const;
  void updateObject() override;
  void setScale(float x = 1.0f, float y = 1.0f,
                float z = 1.0f) override{/*Stub*/};
  Math::Vector3 getScale() const override {
    return Math::Vector3(0.0f); /*Stub*/
  };
  Graphics::RGBAColor GetVertexColor() const override {
    return Graphics::RGBAColor(0.0f);
  };
  void SetVertexColor(float iR, float iG, float iB, float iA) override{};
  void setObjectController(
      SharedPointer<IObjectController> objectController) override;
  std::string getMaterialName() override { return "NO Material"; }
  bool isCollidable() override;
  bool isPhysicsEnabled() override;
  void enableCollision(bool) override;
  void enablePhysics(bool) override;
  void castShadow(bool, Graphics::ShadowMethod) override;
  bool castingShadowEnabled() override;
  void receiveShadow(bool) override;
  bool receivingShadowEnabled() override;
  void setObjectType(ObjectType iObjectType) override;
  ObjectType getObjectType() override;
  void SetMaterial(std::string iMaterialName) override {}
  bool isSSAOEnabled() override { return false; }
  void EnableSSAO(bool iRequest) override {}

 private:
  Math::Transform mTransform;
  Math::Transform mInitialTransform;
  bool isInitialTransform;
  std::string mCameraName;
  SharedPointer<IObjectController> mObjectController;
  float fieldOfView;
  float aspectRatio;
  bool active;
  float nearPlane;
  float farPlane;
  bool isPlayer;
  ObjectType mObjectType;
  Math::Vector3 lookAtTarget;
  bool isThirdPerson;
  MouseEventAndPosition mMouseCurrentStateAndPosition;
  MouseEventAndPosition mMousePreviousStateAndPosition;
  Camera(std::string, Math::Vector3, Math::Quaternion, float, float,
         float i_nearPlane = 0.1f, float u_farPlane = 10000.0f);
  Camera();
};
}  

#endif