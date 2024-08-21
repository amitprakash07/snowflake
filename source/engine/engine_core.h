#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

#include "engine_includes.h"
#include "../MessagingSystem/MessagingSystem.h"
#include "../StringPoolManager/StringPool.h"
#include "../Utilities/SharedPointer.h"
#include "InputController/InputController.h"
#include "InputController/MouseController.h"
#include "WindowingSystem/WindowsProgram.h"

namespace engine {
class EngineCore {
 public:
  static void Initialize(HINSTANCE hInstance, int windowLayout, bool isServer);
  static void onNewFrame();
  static bool isWindowClosed(HINSTANCE hInstance);
  static void shutDownEngine();
  static SharedPointer<MessagingSystem> getMessagingSystem();
  static SharedPointer<StringPool> getStringPool();
  static SharedPointer<Windows::WindowingSystem> getWindowingSystem();
  static SharedPointer<InputController> getInputController();
  static SharedPointer<MouseController> getMouseInputController();
  static std::string getMeshFolderPath();
  static std::string getMaterialFolderPath();
  static std::string getEffectFolderPath();
  static std::string getShaderFolderPath();
  static std::string getTextureFolderPath();

 private:
  EngineCore();
  // static SharedPointer<EngineCore> mEngineInstance;
  static SharedPointer<MessagingSystem> mMessagingSystem;
  static SharedPointer<StringPool> mStringPool;
  static SharedPointer<Windows::WindowingSystem> mEngineWindowingSystem;
  static SharedPointer<InputController> mInputController;
  static SharedPointer<MouseController> mMouseController;
  static std::string materialFolderPath;
  static std::string shaderFolderName;
  static std::string effectFolderName;
  static std::string meshFolderName;
  static std::string textureFolderName;
};
}  

#endif
