#ifndef __MOUSE_CONTROLLER_H
#define __MOUSE_CONTROLLER_H

namespace engine {
struct MouseStates {
  bool leftButtonPressed;
  bool rightButtonPressed;
  bool middleButtonPressed;
  bool shiftKey;
  bool ctrlKey;
  bool mouseMoving;
  MouseStates() {
    leftButtonPressed = rightButtonPressed = middleButtonPressed = shiftKey =
        ctrlKey = mouseMoving = false;
  }
};

struct MouseEventAndPosition {
  int x;     // x-coordinate
  int y;     // y-coordiante
  POINTS P;  // Point in screen coordinate - depending on screen size
  MouseStates mMouseStates;
};

struct WindowsParam {
  UINT windowsMessage;
  WPARAM wParam;
  LPARAM lParam;
};
}  
#endif
