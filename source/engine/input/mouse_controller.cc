#include "../../../Windows/WindowsFunctions.h"
#include "../EngineCore.h"
#include "MouseController.h"

SharedPointer<MouseController>
    MouseController::mMouseInputController;

std::string MouseController::getTypeInfo() const { return mTypeName; }

bool MouseController::isBothSameType(SharedPointer<RTTI> i_first,
                                             std::string i_second) const {
  if (i_first->getTypeInfo() == i_second) return true;
  return false;
}

MouseController::MouseController() {
  mTypeName = "InputController";
  mMouseCurrentStateAndPosition.mMouseStates.leftButtonPressed = false;
  mMouseCurrentStateAndPosition.mMouseStates.middleButtonPressed = false;
  mMouseCurrentStateAndPosition.mMouseStates.rightButtonPressed = false;
  mMouseCurrentStateAndPosition.x = 0;
  mMouseCurrentStateAndPosition.y = 0;

  mMousePreviousStateAndPosition.mMouseStates.leftButtonPressed = false;
  mMousePreviousStateAndPosition.mMouseStates.middleButtonPressed = false;
  mMousePreviousStateAndPosition.mMouseStates.rightButtonPressed = false;
  mMousePreviousStateAndPosition.x = 0;
  mMousePreviousStateAndPosition.y = 0;
  arcBallReady = false;
}

SharedPointer<MouseController>
MouseController::getMouseController() {
  if (mMouseInputController.isNull()) {
    SharedPointer<MouseController> tempInputController(
        SharedPointer<MouseController>(
            new MouseController(),
            EngineCore::getStringPool()->findString(
                "InputController")));
    mMouseInputController = tempInputController;
    utils::StringHash temp = utils::StringHash(
        EngineCore::getStringPool()->findString("MouseEvent"));
    EngineCore::getMessagingSystem()->addMessageHandler(
        temp, tempInputController.CastSharedPointer<IMessageHandler>(),
        typedefs::HIGH);
  }
  return mMouseInputController;
}

void MouseController::HandleMessage(utils::StringHash&,
                                            SharedPointer<RTTI>,
                                            void* i_pMessageData) {
  WindowsParam tempWindowsParameter =
      *reinterpret_cast<WindowsParam*>(i_pMessageData);
  if (tempWindowsParameter.windowsMessage && WM_LBUTTONDOWN &&
      (!tempWindowsParameter.windowsMessage && WM_MOUSEMOVE)) {
    mMouseCurrentStateAndPosition.mMouseStates.leftButtonPressed = true;
    if (tempWindowsParameter.wParam && MK_CONTROL)
      mMouseCurrentStateAndPosition.mMouseStates.ctrlKey = true;
    if (tempWindowsParameter.wParam && MK_SHIFT)
      mMouseCurrentStateAndPosition.mMouseStates.shiftKey = true;
    if (tempWindowsParameter.wParam && MK_RBUTTON)
      mMouseCurrentStateAndPosition.mMouseStates.rightButtonPressed = true;
    if (tempWindowsParameter.wParam && MK_MBUTTON)
      mMouseCurrentStateAndPosition.mMouseStates.middleButtonPressed = true;
    mMouseCurrentStateAndPosition.x = GET_X_LPARAM(tempWindowsParameter.lParam);
    mMouseCurrentStateAndPosition.y = GET_Y_LPARAM(tempWindowsParameter.lParam);
    mMouseCurrentStateAndPosition.P = MAKEPOINTS(tempWindowsParameter.lParam);
    arcBallReady = true;
    mMousePreviousStateAndPosition = mMouseCurrentStateAndPosition;
  } else
    arcBallReady = false;

  if (tempWindowsParameter.windowsMessage && WM_MOUSEMOVE && arcBallReady) {
    mMouseCurrentStateAndPosition.x = GET_X_LPARAM(tempWindowsParameter.lParam);
    mMouseCurrentStateAndPosition.y = GET_Y_LPARAM(tempWindowsParameter.lParam);
    mMouseCurrentStateAndPosition.P = MAKEPOINTS(tempWindowsParameter.lParam);
  }

  utils::StringHash temp =
      EngineCore::getStringPool()->findString("ActionOnMouseEvent");
  SharedPointer<MouseController> tempMouseController =
      EngineCore::getMouseInputController();
  EngineCore::getMessagingSystem()->sendMessage(
      temp, tempMouseController.CastSharedPointer<RTTI>(), i_pMessageData);
}

MouseEventAndPosition MouseController::getCurrentMouseState()
    const {
  return mMouseCurrentStateAndPosition;
}

void MouseController::leftButtonPressed(bool i_state) {
  mMousePreviousStateAndPosition.mMouseStates.leftButtonPressed =
      mMouseCurrentStateAndPosition.mMouseStates.leftButtonPressed;
  mMouseCurrentStateAndPosition.mMouseStates.leftButtonPressed = i_state;
}

void MouseController::rightButtonPressed(bool i_state) {
  mMousePreviousStateAndPosition.mMouseStates.rightButtonPressed =
      mMouseCurrentStateAndPosition.mMouseStates.rightButtonPressed;
  mMouseCurrentStateAndPosition.mMouseStates.rightButtonPressed = i_state;
}

void MouseController::middleButtonPressed(bool i_state) {
  mMousePreviousStateAndPosition.mMouseStates.middleButtonPressed =
      mMouseCurrentStateAndPosition.mMouseStates.middleButtonPressed;
  mMouseCurrentStateAndPosition.mMouseStates.middleButtonPressed = i_state;
}

void MouseController::mouseMoving(bool i_state) {
  mMousePreviousStateAndPosition.mMouseStates.mouseMoving =
      mMouseCurrentStateAndPosition.mMouseStates.mouseMoving;
  mMouseCurrentStateAndPosition.mMouseStates.mouseMoving = i_state;
}

void MouseController::setMousePosition(int i_x, int i_y,
                                               POINTS i_point) {
  mMousePreviousStateAndPosition.x = mMouseCurrentStateAndPosition.x;
  mMousePreviousStateAndPosition.y = mMouseCurrentStateAndPosition.y;
  mMousePreviousStateAndPosition.P = mMouseCurrentStateAndPosition.P;

  mMouseCurrentStateAndPosition.x = i_x;
  mMouseCurrentStateAndPosition.y = i_y;
  mMouseCurrentStateAndPosition.P = i_point;
}
