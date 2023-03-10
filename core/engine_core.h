#pragma once
#ifndef __CORE_H
#define __CORE_H

#include "../MessagingSystem/MessagingSystem.h"
#include "../StringPoolManager/StringPool.h"
#include "../Utilities/SharedPointer.h"
#include "InputController/InputController.h"
#include "InputController/MouseController.h"
#include "WindowingSystem/WindowsProgram.h"

namespace Engine {
class EngineCore {
 public:
  static void Initialize(HINSTANCE hInstance, int windowLayout, bool isServer);
  static void onNewFrame();
  static bool isWindowClosed(HINSTANCE hInstance);
  static void shutDownEngine();
  static SharedPointer<Engine::MessagingSystem> getMessagingSystem();
  static SharedPointer<Engine::StringPool> getStringPool();
  static SharedPointer<Engine::Windows::WindowingSystem> getWindowingSystem();
  static SharedPointer<Engine::InputController> getInputController();
  static SharedPointer<Engine::MouseController> getMouseInputController();
  static std::string getMeshFolderPath();
  static std::string getMaterialFolderPath();
  static std::string getEffectFolderPath();
  static std::string getShaderFolderPath();
  static std::string getTextureFolderPath();

 private:
  EngineCore();
  // static SharedPointer<EngineCore> mEngineInstance;
  static SharedPointer<Engine::MessagingSystem> mMessagingSystem;
  static SharedPointer<Engine::StringPool> mStringPool;
  static SharedPointer<Engine::Windows::WindowingSystem> mEngineWindowingSystem;
  static SharedPointer<Engine::InputController> mInputController;
  static SharedPointer<Engine::MouseController> mMouseController;
  static std::string materialFolderPath;
  static std::string shaderFolderName;
  static std::string effectFolderName;
  static std::string meshFolderName;
  static std::string textureFolderName;
};
}  // namespace Engine

#endif
