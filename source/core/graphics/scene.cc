#include "Scene.h"

#include <algorithm>

#include "../../../Graphics/SSAO.h"
#include "../../../Graphics/SkyBox.h"
#include "../../Physics/PhysicsSystem.h"

std::map<std::string, SharedPointer<Scene>>
    Scene::mSceneList;

Scene::Scene(std::string i_sceneName)
    : mTimer(Time::FrameTime::getFrameTimeController()) {
  mMeshObjectInSceneList.reserve(20);
  mLineListInScene.reserve(20);
  mSpriteListInScene.reserve(20);
  mReflectingObjectList.reserve(20);
  mPlaneList.reserve(20);
  mLightList.reserve(10);
  sceneName = i_sceneName;
  render = false;
  renderDebug = true;
  mObjectType = ObjectType::NONE;
}

SharedPointer<Scene> Scene::CreateNewScene(
    std::string i_sceneName) {
  if (!i_sceneName.empty()) {
    SharedPointer<Scene> temp =
        SharedPointer<Scene>(new Scene(i_sceneName), "Scene");
    mSceneList[i_sceneName] = temp;
    return (getScene(i_sceneName));
  }
  return (SharedPointer<Scene>());
}

SharedPointer<Time::FrameTime> Scene::getTimer() {
  return (getRenderableScene()->mTimer);
}

Scene::~Scene() {
  for (std::vector<SharedPointer<MeshObject>>::iterator i =
           mMeshObjectInSceneList.begin();
       i != mMeshObjectInSceneList.end(); ++i)
    i->deleteObject();
}

template <typename T>
bool Scene::addObjectToScene(SharedPointer<T>& i_game_object) {
  return false;
}

// MeshObjects
template <>
bool Scene::addObjectToScene<MeshObject>(
    SharedPointer<MeshObject>& iMeshObject) {
  if (!iMeshObject.isNull()) {
    mMeshObjectInSceneList.push_back(iMeshObject);
    return true;
  }
  return false;
}

template <>
bool Scene::addObjectToScene<Graphics::Text>(
    SharedPointer<Graphics::Text>& iText) {
  if (!iText.isNull()) {
    mTextList.push_back(iText);
    return true;
  }
  return false;
}

// Lines
template <>
bool Scene::addObjectToScene<Graphics::Line>(
    SharedPointer<Graphics::Line>& iLine) {
  if (!iLine.isNull()) {
    mLineListInScene.push_back(iLine);
    return true;
  }
  return false;
}

// Sprites
template <>
bool Scene::addObjectToScene<Graphics::Sprite>(
    SharedPointer<Graphics::Sprite>& iSprite) {
  if (!iSprite.isNull()) {
    mSpriteListInScene.push_back(iSprite);
    return true;
  }
  return false;
}

// Planes
template <>
bool Scene::addObjectToScene<Graphics::Plane>(
    SharedPointer<Graphics::Plane>& iPlane) {
  if (!iPlane.isNull()) {
    mPlaneList.push_back(iPlane);
    return true;
  }
  return false;
}

// Reflecting Objects - Environment Maps
template <>
bool Scene::addObjectToScene<Graphics::ReflectingObject>(
    SharedPointer<Graphics::ReflectingObject>& iReflectingObject) {
  if (!iReflectingObject.isNull()) {
    mReflectingObjectList.push_back(iReflectingObject);
    return true;
  }
  return false;
}

// Camera
bool Scene::addCameraToScene(SharedPointer<Camera>& i_camera) {
  if (!i_camera.isNull()) {
    mCameraListInScene[i_camera->getCameraName()] = i_camera;
    return true;
  }
  return false;
}

// Light
bool Scene::addLightToScene(SharedPointer<Graphics::Light>& iLight) {
  if (!iLight.isNull()) {
    mLightList.push_back(iLight);
    return true;
  }
  return false;
}

void Scene::renderScene(bool i_render) {
  deactivateAllSceneToRender();
  render = i_render;
}

void Scene::deactivateAllSceneToRender() {
  for (std::map<std::string, SharedPointer<Scene>>::iterator i =
           mSceneList.begin();
       i != mSceneList.end(); ++i)
    i->second->render = false;
}

SharedPointer<Scene> Scene::getRenderableScene() {
  for (std::map<std::string, SharedPointer<Scene>>::iterator i =
           mSceneList.begin();
       i != mSceneList.end(); ++i) {
    if (i->second->render) return i->second;
  }
  return (SharedPointer<Scene>());
}

SharedPointer<MeshObject> Scene::GetPlayer() {
  SharedPointer<Scene> renderableScene = getRenderableScene();
  for (uint8_t i = 0; i < renderableScene->mMeshObjectInSceneList.size(); i++) {
    if (renderableScene->mMeshObjectInSceneList[i]->IsPlayer())
      return renderableScene->mMeshObjectInSceneList[i];
  }
  return SharedPointer<MeshObject>();
}

void Scene::EnableAllMeshObjectsForSSAO() {
  for (uint8_t i = 0; i < mMeshObjectInSceneList.size(); i++)
    mMeshObjectInSceneList[i]->EnableSSAO(true);
}

void Scene::SetNewFrame(bool newFrame) { isNextFrame = newFrame; }

bool Scene::IsNewFrame() const { return isNextFrame; }

void Scene::drawScene(bool withDebug) {
  if (Physics::PhysicsSystem::GetPhysicsSystem()->ShowCollisionMesh()) {
    Physics::PhysicsSystem::DrawCollisionMesh();
  }
  if (!Physics::PhysicsSystem::GetPhysicsSystem()->CollisionDebuggingStatus()) {
    // Graphics::SSAO::SSAOBindGBuffer();
    if (mLightList.size() > 0) {
      for (std::vector<SharedPointer<Graphics::Light>>::iterator iL =
               mLightList.begin();
           iL != mLightList.end(); ++iL) {
        (*iL)->setLightParameterValueToShaderObject();
      }
    }

    for (uint8_t i = 0; i < mMeshObjectInSceneList.size(); i++) {
      if (!mMeshObjectInSceneList[i]->isSSAOEnabled())
        mMeshObjectInSceneList[i]->draw(withDebug);
    }

    // Graphics::SSAO::GenerateGBuffer();
    // Generate dynamic Cube Maps
    if (mReflectingObjectList.size() > 0) {
      sortAllReflectingObjects();
      for (uint8_t i = 0; i < mReflectingObjectList.size(); i++) {
        mReflectingObjectList[i]->generateCubeMap();
      }
    }

    SharedPointer<Graphics::SkyBox> tempSkyBox =
        Graphics::SkyBox::getCurrentSkyBox();
    if (!tempSkyBox.isNull() && tempSkyBox->isSkyBoxAvailableIntialized()) {
      tempSkyBox->draw(true);
    }

    for (uint8_t i = 0; i < mMeshObjectInSceneList.size(); i++) {
      if (mMeshObjectInSceneList[i]->isSSAOEnabled())
        mMeshObjectInSceneList[i]->draw(withDebug);
    }

    for (uint8_t i = 0; i < mPlaneList.size(); i++)
      mPlaneList[i]->draw(withDebug);

    if (Graphics::Line::containsDebugLine())
      Graphics::Line::drawLines(withDebug);

    // Draw the environment mapping reflecting Objects
    if (mReflectingObjectList.size() > 0) {
      for (uint8_t i = 0; i < mReflectingObjectList.size(); i++) {
        mReflectingObjectList[i]->draw(true);
      }
    }

    for (uint8_t i = 0; i < mSpriteListInScene.size(); i++)
      mSpriteListInScene[i]->draw(withDebug);

    // Graphics::SSAO::RunSSAO();

    for (uint8_t i = 0; i < mTextList.size(); i++) mTextList[i]->draw(false);
  }
  mTimer->updateDeltaTime();
  updateScene();
}

void Scene::updateScene() {
  if (mReflectingObjectList.size() > 0) {
    for (uint8_t i = 0; i < mReflectingObjectList.size(); i++) {
      mReflectingObjectList[i]->updateObject();
    }
  }

  SharedPointer<Graphics::SkyBox> tempSkyBox =
      Graphics::SkyBox::getCurrentSkyBox();
  if (!tempSkyBox.isNull() && tempSkyBox->isSkyBoxAvailableIntialized()) {
    tempSkyBox->updateObject();
  }

  for (uint8_t i = 0; i < mMeshObjectInSceneList.size(); i++)
    mMeshObjectInSceneList[i]->updateObject();

  for (uint8_t i = 0; i < mSpriteListInScene.size(); i++)
    mSpriteListInScene[i]->updateObject();

  // Draw the environment mapping reflecting Objects
  if (mReflectingObjectList.size() > 0) {
    for (uint8_t i = 0; i < mReflectingObjectList.size(); i++) {
      mReflectingObjectList[i]->updateObject();
    }
  }
}

void Scene::applyPaintersAlgorithmForTransparency() {
  SharedPointer<Scene> activeScene = getRenderableScene();
  std::sort(activeScene->mMeshObjectInSceneList.begin(),
            activeScene->mMeshObjectInSceneList.end(), sortMeshObject);
}

void Scene::sortAllReflectingObjects() {
  SharedPointer<Scene> activeScene = getRenderableScene();
  std::sort(activeScene->mReflectingObjectList.begin(),
            activeScene->mReflectingObjectList.end(), sortReflectingObject);
}

std::vector<SharedPointer<MeshObject>>
Scene::getMeshObjectList() const {
  return mMeshObjectInSceneList;
}

std::vector<SharedPointer<Graphics::Sprite>>
Scene::getSpriteObjectList() const {
  return mSpriteListInScene;
}

std::vector<SharedPointer<Graphics::Line>>
Scene::getLineList() const {
  return mLineListInScene;
}

std::vector<SharedPointer<Graphics::ReflectingObject>>
Scene::getReflectingObjectList() const {
  return mReflectingObjectList;
}

std::vector<SharedPointer<Graphics::Plane>>
Scene::getPlaneList() const {
  return mPlaneList;
}

std::vector<SharedPointer<Graphics::Light>>
Scene::getLightList() const {
  return mLightList;
}

bool Scene::sortMeshObject(SharedPointer<MeshObject> i_gameObjectOne,
                                   SharedPointer<MeshObject> i_gameObjectTwo) {
  if (i_gameObjectOne->getTransform().getPosition().z <
      i_gameObjectTwo->getTransform().getPosition().z)
    return true;
  return false;
}

bool Scene::sortSprites(
    SharedPointer<Graphics::Sprite> i_gameObjectOne,
    SharedPointer<Graphics::Sprite> i_gameObjectTwo) {
  if (i_gameObjectOne->getTransform().getPosition().z <
      i_gameObjectTwo->getTransform().getPosition().z)
    return true;
  return false;
}

bool Scene::sortReflectingObject(
    SharedPointer<Graphics::ReflectingObject> i_gameObjectOne,
    SharedPointer<Graphics::ReflectingObject> i_gameObjectTwo) {
  if (i_gameObjectOne->getTransform().getPosition().z <
      i_gameObjectTwo->getTransform().getPosition().z)
    return true;
  return false;
}

bool Scene::isSceneExist(std::string i_sceneName) {
  if (!i_sceneName.empty()) {
    for (std::map<std::string, SharedPointer<Scene>>::iterator i =
             mSceneList.begin();
         i != mSceneList.end(); ++i) {
      if (i->first == i_sceneName) return true;
    }
    return false;
  }
  return false;
}

SharedPointer<Scene> Scene::getScene(
    std::string i_sceneName) {
  if (!i_sceneName.empty() && isSceneExist(i_sceneName)) {
    for (std::map<std::string, SharedPointer<Scene>>::iterator i =
             mSceneList.begin();
         i != mSceneList.end(); ++i) {
      if (i->first == i_sceneName) {
        return (i->second);
      }
    }
  }
  return (SharedPointer<Scene>());
}

void Scene::deleteAllScene() {
  for (std::map<std::string, SharedPointer<Scene>>::iterator i =
           mSceneList.begin();
       i != mSceneList.end(); ++i) {
    for (std::vector<SharedPointer<MeshObject>>::iterator j =
             i->second->mMeshObjectInSceneList.begin();
         j != i->second->mMeshObjectInSceneList.end(); ++j)
      j->deleteObject();
    for (std::vector<SharedPointer<Graphics::Sprite>>::iterator j =
             i->second->mSpriteListInScene.begin();
         j != i->second->mSpriteListInScene.end(); ++j)
      j->deleteObject();
  }
}

SharedPointer<Camera> Scene::getActiveCamera() const {
  for (std::map<std::string, SharedPointer<Camera>>::const_iterator i =
           mCameraListInScene.begin();
       i != mCameraListInScene.end(); ++i) {
    if (i->second->isActive()) return i->second;
  }
  return SharedPointer<Camera>();
}

void Scene::deactivateAllCamera() const {
  for (std::map<std::string, SharedPointer<Camera>>::const_iterator i =
           mCameraListInScene.begin();
       i != mCameraListInScene.end(); ++i) {
    i->second->activateCamera(false);
  }
}

void Scene::useCamera(SharedPointer<Camera> iCamera) const {
  if (findCamera(iCamera)) {
    deactivateAllCamera();
    iCamera->activateCamera(true);
  }
}

void Scene::useCamera(const std::string iCamera) const {
  SharedPointer<Camera> tempCamera = findCamera(iCamera);
  if (!tempCamera.isNull()) useCamera(tempCamera);
}

bool Scene::findCamera(const SharedPointer<Camera> iCamera) const {
  for (std::map<std::string, SharedPointer<Camera>>::const_iterator i =
           mCameraListInScene.begin();
       i != mCameraListInScene.end(); ++i) {
    if (iCamera.isEqual(i->second)) return true;
  }
  return false;
}

SharedPointer<Camera> Scene::findCamera(
    const std::string iCamera) const {
  for (std::map<std::string, SharedPointer<Camera>>::const_iterator i =
           mCameraListInScene.begin();
       i != mCameraListInScene.end(); ++i) {
    if (iCamera == i->first) return i->second;
  }
  return SharedPointer<Camera>();
}

void Scene::updateObject() {
  typedefs::ActionWithKeyBound action;
  action.action = typedefs::Default;
  action.keyVal = 0x00;
  if (!mObjectController.isNull())
    mObjectController->updateObject(*this, action);
}

void Scene::setScale(float x, float y, float z) {
  // Need to implement Later
}

void Scene::setObjectController(
    SharedPointer<IObjectController> iObjectController) {
  if (!iObjectController.isNull()) mObjectController = iObjectController;
}

void Scene::HandleMessage(utils::StringHash& i_message,
                                  SharedPointer<RTTI> i_MessageSender,
                                  void* i_pMessageData) {
  if (!i_MessageSender.isNull()) {
    if (!i_MessageSender.isNull() &&
        utils::StringHash("UpdateObject") == i_message &&
        !mObjectController.isNull())
      mObjectController->updateObject(
          *this, *reinterpret_cast<typedefs::ActionWithKeyBound*>(
                     i_pMessageData));
  }
}

bool Scene::isCollidable() { return false; }

bool Scene::isPhysicsEnabled() { return false; }

void Scene::enableCollision(bool) {
  // Stub
}

void Scene::enablePhysics(bool) {
  // Stub
}

void Scene::receiveShadow(bool) {
  // Stub
}

bool Scene::receivingShadowEnabled() { return false; }

void Scene::castShadow(bool, Graphics::ShadowMethod) {
  // Stub
}

bool Scene::castingShadowEnabled() { return false; }

ObjectType Scene::getObjectType() { return mObjectType; }

void Scene::setObjectType(ObjectType iObjectType) {
  mObjectType = iObjectType;
}

void Scene::SetMaterial(std::string iMaterialName) {
  // Stub - No Implementation Required
}

// SharedPointer<Object> Scene::getObject()
//{
//	return mMeshObjectInSceneList[0].CastSharedPointer<Object>();
//}
