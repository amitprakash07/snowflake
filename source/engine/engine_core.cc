#include <iostream>

#include "../../Graphics/Material.h"
#include "../NetworkManager/NetworkManager.h"
#include "..\..\Graphics/Effect.h"
#include "..\..\Graphics/Mesh.h"
#include "..\..\Graphics\Graphics.h"
#include "..\..\Windows\WindowsFunctions.h"

#include "Objects/Scene.h"

#include "engine_core.h"

SharedPointer<MessagingSystem>
    EngineCore::mMessagingSystem;
SharedPointer<StringPool> EngineCore::mStringPool;
SharedPointer<Windows::WindowingSystem>
    EngineCore::mEngineWindowingSystem;
SharedPointer<InputController>
    EngineCore::mInputController;
SharedPointer<MouseController>
    EngineCore::mMouseController;
std::string EngineCore::materialFolderPath;
std::string EngineCore::shaderFolderName;
std::string EngineCore::effectFolderName;
std::string EngineCore::meshFolderName;
std::string EngineCore::textureFolderName;

void EngineCore::Initialize(HINSTANCE hInstance, int windowLayout,
                                    bool isServer) {
  getMessagingSystem();
  getStringPool();
  getWindowingSystem();
  getInputController();
  getMouseInputController();
  Networking::NetworkManager::CreateNetworkManager(isServer);

  std::stringstream errormessage;
  if (!getWindowingSystem().isNull()) {
    mEngineWindowingSystem->CreateMainWindow(hInstance, windowLayout);
    if (!Graphics::GraphicsSystem::Initialize(
            mEngineWindowingSystem->getMainWindow())) {
      errormessage << "Unable to initialize Graphics System";
      std::cerr << errormessage.str().c_str();
    }
  }

  std::string other;
  const char* envName = "MeshDir";
  meshFolderName = "data/Meshes/";
  shaderFolderName = "data/Shaders/";
  materialFolderPath = "data/Materials/";
  effectFolderName = "data/Effects/";
  textureFolderName = "data/Textures/";
}

std::string EngineCore::getEffectFolderPath() {
  return effectFolderName;
}

std::string EngineCore::getMaterialFolderPath() {
  return materialFolderPath;
}

std::string EngineCore::getMeshFolderPath() { return meshFolderName; }

std::string EngineCore::getShaderFolderPath() {
  return shaderFolderName;
}

std::string EngineCore::getTextureFolderPath() {
  return textureFolderName;
}

EngineCore::EngineCore() {}

SharedPointer<Windows::WindowingSystem>
EngineCore::getWindowingSystem() {
  if (mEngineWindowingSystem.isNull()) {
    SharedPointer<Windows::WindowingSystem> tempWindowingSystem =
        Windows::WindowingSystem::getWindowingSystem();
    mEngineWindowingSystem = tempWindowingSystem;
  }
  return mEngineWindowingSystem;
}

SharedPointer<MessagingSystem>
EngineCore::getMessagingSystem() {
  if (mMessagingSystem.isNull()) {
    SharedPointer<MessagingSystem> tempMessagingSystem =
        MessagingSystem::getMessagingSystem();
    mMessagingSystem = tempMessagingSystem;
  }
  return mMessagingSystem;
}

SharedPointer<StringPool> EngineCore::getStringPool() {
  if (mStringPool.isNull()) {
    SharedPointer<StringPool> tempStringPool =
        StringPool::getStringPool();
    mStringPool = tempStringPool;
  }
  return mStringPool;
}

SharedPointer<InputController>
EngineCore::getInputController() {
  if (mInputController.isNull()) {
    SharedPointer<InputController> tempInputcontroller =
        InputController::getInputController();
    mInputController = tempInputcontroller;
  }
  return mInputController;
}

SharedPointer<MouseController>
EngineCore::getMouseInputController() {
  if (mMouseController.isNull()) {
    SharedPointer<MouseController> tempMouseController =
        MouseController::getMouseController();
    mMouseController = tempMouseController;
  }
  return mMouseController;
}

void EngineCore::onNewFrame() {
  MSG message = {};
  bool hasWindowsSentAMessage;
  {
    HWND getMessagesFromAnyWindowBelongingToTheCurrentThread = nullptr;
    unsigned int getAllMessageTypes = 0;
    unsigned int ifAMessageExistsRemoveItFromTheQueue = PM_REMOVE;
    hasWindowsSentAMessage =
        PeekMessage(&message,
                    getMessagesFromAnyWindowBelongingToTheCurrentThread,
                    getAllMessageTypes, getAllMessageTypes,
                    ifAMessageExistsRemoveItFromTheQueue) == TRUE;
  }

  if (!hasWindowsSentAMessage) {
    Networking::NetworkManager::updateNetwork();
    Graphics::GraphicsSystem::Render();
    Scene::getRenderableScene()->SetNewFrame(true);
  } else {
    TranslateMessage(&message);
    DispatchMessage(&message);
  }
}

bool EngineCore::isWindowClosed(HINSTANCE hInstance) {
  if (mEngineWindowingSystem->getMainWindow() == nullptr) {
    shutDownEngine();
    if (mEngineWindowingSystem->OnMainWindowClosed(hInstance))
      return true;
    else {
      std::stringstream errormessage;
      errormessage << "Unable to close and clean up the windowing system";
      WindowsUtil::Print(errormessage.str());
      return false;
    }
  }
  return false;
}

void EngineCore::shutDownEngine() {
  Scene::deleteAllScene();
  Graphics::Mesh::deleteAllMesh();
  Graphics::Effect::deleteAllEffect();
  mMessagingSystem.deleteObject();
  mStringPool.deleteObject();
  mInputController.deleteObject();
}
