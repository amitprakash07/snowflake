#ifndef __SCENE_H
#define __SCENE_H

#include <vector>

#include "../../../Core/Time/FrameTime.h"
#include "../../../Core/Utilities/SharedPointer.h"
#include "../../../Graphics/Light.h"
#include "../../../Graphics/Line.h"
#include "../../../Graphics/Plane.h"
#include "../../../Graphics/ReflectingObject.h"
#include "../../../Graphics/Sprite.h"
#include "../../../Graphics/Text.h"
#include "Camera.h"
#include "MeshObject.h"

namespace Engine {
class Scene : public Object, IMessageHandler {
 public:
  static SharedPointer<Scene> CreateNewScene(std::string);
  static SharedPointer<Engine::Time::FrameTime> getTimer();
  static Engine::SharedPointer<Scene> getRenderableScene();
  static SharedPointer<MeshObject> GetPlayer();
  void SetNewFrame(bool newFrame);
  bool IsNewFrame() const;
  void EnableAllMeshObjectsForSSAO();
  template <typename T>
  bool addObjectToScene(SharedPointer<T>&);
  bool addCameraToScene(SharedPointer<Camera>&);
  bool addLightToScene(SharedPointer<Graphics::Light>&);
  void useCamera(const std::string) const;
  void useCamera(SharedPointer<Camera>) const;
  void drawScene(bool withDebug = true);
  void updateScene();
  static SharedPointer<Engine::Scene> getScene(std::string);
  void renderScene(bool);
  std::vector<SharedPointer<Engine::MeshObject>> getMeshObjectList() const;
  std::vector<SharedPointer<Engine::Graphics::Sprite>> getSpriteObjectList()
      const;
  std::vector<SharedPointer<Engine::Graphics::Line>> getLineList() const;
  std::vector<SharedPointer<Engine::Graphics::ReflectingObject>>
  getReflectingObjectList() const;
  std::vector<SharedPointer<Engine::Graphics::Plane>> getPlaneList() const;
  std::vector<SharedPointer<Engine::Graphics::Light>> getLightList() const;
  SharedPointer<Camera> getActiveCamera() const;
  void setRenderable(bool iRenderable) override {}
  static void deleteAllScene();
  std::string getTypeInfo() const override { return ""; }
  bool isBothSameType(SharedPointer<RTTI>, std::string) const override {
    return true;
  }
  static void applyPaintersAlgorithmForTransparency();
  static void sortAllReflectingObjects();
  // Object Override functions
  Math::Transform getTransform() override { return Math::Transform(); }
  void draw(bool) override {}
  bool isRenderable() const override { return true; }
  bool isDebugObject() const override { return false; }
  void updateObject() override;
  void setObjectController(
      SharedPointer<IObjectController> iObjectController) override;
  void setTransform(
      Engine::Math::Vector3,
      Engine::Math::Quaternion = Engine::Math::Quaternion()) override {}
  void setScale(float x = 1.0f, float y = 1.0f, float z = 1.0f) override;
  Math::Vector3 getScale() const override {
    return Math::Vector3(0.0f); /*Stub*/
  }
  Graphics::RGBAColor GetVertexColor() const override {
    return Graphics::RGBAColor(0.0f);
  }
  void SetVertexColor(float iR, float iG, float iB, float iA) override{};
  void resetTransform() override {}
  std::string getMaterialName() override { return "NO Material"; }
  bool isCollidable() override;
  bool isPhysicsEnabled() override;
  void enableCollision(bool) override;
  void enablePhysics(bool) override;
  void castShadow(bool, Graphics::ShadowMethod) override;
  bool castingShadowEnabled() override;
  void receiveShadow(bool) override;
  bool receivingShadowEnabled() override;
  bool IsPlayer() override { return false; }
  void setPlayer(bool) override{};
  void setObjectType(ObjectType iObjectType) override;
  void SetMaterial(std::string iMaterialName) override;
  // SharedPointer<Object> getObject();
  ObjectType getObjectType() override;
  // IMesageHandler override function
  void HandleMessage(Engine::utils::StringHash&,
                     SharedPointer<RTTI> i_MessageSender,
                     void* i_pMessageData) override;
  bool isSSAOEnabled() override { return false; }
  void EnableSSAO(bool iRequest) override {}
  ~Scene();

 private:
  static std::map<std::string, SharedPointer<Scene>> mSceneList;
  Scene(std::string);
  static bool isSceneExist(std::string);
  std::vector<SharedPointer<Engine::MeshObject>> mMeshObjectInSceneList;
  std::vector<SharedPointer<Engine::Graphics::Line>> mLineListInScene;
  std::vector<SharedPointer<Engine::Graphics::Sprite>> mSpriteListInScene;
  std::vector<SharedPointer<Engine::Graphics::ReflectingObject>>
      mReflectingObjectList;
  std::vector<SharedPointer<Engine::Graphics::Plane>> mPlaneList;
  std::vector<SharedPointer<Engine::Graphics::Light>> mLightList;
  std::vector<SharedPointer<Engine::Graphics::Text>> mTextList;
  std::map<std::string, SharedPointer<Camera>> mCameraListInScene;
  static void deactivateAllSceneToRender();
  void deactivateAllCamera() const;
  SharedPointer<Engine::Time::FrameTime> mTimer;
  SharedPointer<Camera> activeCamera;

  static bool sortMeshObject(SharedPointer<MeshObject>,
                             SharedPointer<MeshObject>);

  static bool sortSprites(SharedPointer<Engine::Graphics::Sprite>,
                          SharedPointer<Engine::Graphics::Sprite>);

  static bool sortReflectingObject(
      SharedPointer<Engine::Graphics::ReflectingObject>,
      SharedPointer<Engine::Graphics::ReflectingObject>);

  SharedPointer<Camera> findCamera(const std::string) const;
  bool findCamera(const SharedPointer<Camera>) const;
  std::string sceneName;
  bool render;
  bool renderDebug;
  SharedPointer<IObjectController> mObjectController;
  ObjectType mObjectType;
  bool isNextFrame;
};
}  // namespace Engine

#endif