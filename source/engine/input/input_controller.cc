#include <windows.h>

#include "../../Debugging/DebugMenu.h"
#include "../../MessagingSystem/MessagingSystem.h"
#include "../../Physics/PhysicsSystem.h"
#include "../../StringPoolManager/StringPool.h"
#include "../EngineCore.h"
#include "../Objects/Scene.h"
#include "../WindowingSystem/WindowsProgram.h"
#include "InputController.h"

SharedPointer<InputController>
    InputController::mInputController;

std::string InputController::getTypeInfo() const { return mTypeName; }

bool InputController::isBothSameType(SharedPointer<RTTI> i_first,
                                             std::string i_second) const {
  if (i_first->getTypeInfo() == i_second) return true;
  return false;
}

void InputController::HandleMessage(
    utils::StringHash& i_message, SharedPointer<RTTI> i_MessageSender,
    void* i_pMessageData) {
  if (!i_MessageSender.isNull()) {
    if (utils::StringHash("KeyDown") == i_message) {
      if (i_pMessageData && Scene::getRenderableScene()->IsNewFrame()) {
        typedefs::ActionWithKeyBound action;
        utils::StringHash gameObjectController =
            EngineCore::getStringPool()->findString("UpdateObject");
        utils::StringHash debugMenuController =
            EngineCore::getStringPool()->findString("DebugMenuHandler");
        SharedPointer<InputController> tempInputController =
            EngineCore::getInputController();
        action.keyVal = reinterpret_cast<WPARAM>(i_pMessageData);
        action.action = typedefs::Default;

        if (action.keyVal == VK_OEM_3) {
          bool CurrentStatus = Debug::DebugMenu::GetDebugMenu()->isActivated();
          Debug::DebugMenu::GetDebugMenu()->Activate(!CurrentStatus);
        }

        if (Debug::DebugMenu::GetDebugMenu()->isActivated())
          EngineCore::getMessagingSystem()->sendMessage(
              debugMenuController,
              tempInputController.CastSharedPointer<RTTI>(), &action);
        else
          EngineCore::getMessagingSystem()->sendMessage(
              gameObjectController,
              tempInputController.CastSharedPointer<RTTI>(), &action);

        if (Physics::PhysicsSystem::GetPhysicsSystem()
                ->CollisionDebuggingStatus()) {
          EngineCore::getMessagingSystem()->sendMessage(
              gameObjectController,
              tempInputController.CastSharedPointer<RTTI>(), &action);
        }

        Scene::getRenderableScene()->SetNewFrame(false);
      }
    }
  }
}

InputController::InputController() {
  mTypeName = "InputController";
}

SharedPointer<InputController>
InputController::getInputController() {
  if (mInputController.isNull()) {
    SharedPointer<InputController> tempInputController(
        SharedPointer<InputController>(
            new InputController(),
            EngineCore::getStringPool()->findString(
                "InputController")));
    mInputController = tempInputController;
    utils::StringHash temp = utils::StringHash(
        EngineCore::getStringPool()->findString("KeyDown"));
    EngineCore::getMessagingSystem()->addMessageHandler(
        temp, tempInputController.CastSharedPointer<IMessageHandler>(),
        typedefs::HIGH);
  }
  return mInputController;
}
