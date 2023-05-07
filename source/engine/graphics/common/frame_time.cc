#include <assert.h>

#include "FrameTime.h"
#include "TimeHelper.h"

SharedPointer<Time::FrameTime>
Time::FrameTime::getFrameTimeController() {
  LARGE_INTEGER *tempFrequency = new LARGE_INTEGER;
  LARGE_INTEGER *tempStartCounter = new LARGE_INTEGER;
  assert(QueryPerformanceFrequency(tempFrequency));   // takes Pointer
  assert(QueryPerformanceCounter(tempStartCounter));  // tekes Pointer
  return (SharedPointer<Time::FrameTime>(
      new FrameTime(tempFrequency, tempStartCounter),
      "Time::FrameTime"));
}

Time::FrameTime::FrameTime(LARGE_INTEGER *i_frequency,
                                   LARGE_INTEGER *i_hRCounter) {
  frameTimeFrequency = i_frequency->QuadPart;
  lastTick = i_hRCounter->QuadPart;
  currentTick = 0;
  isTimerPaused = false;
  pauseTimerTick = 0;
  deltaTime = 0;
  delete i_frequency;
  delete i_hRCounter;
  i_frequency = nullptr;
  i_hRCounter = nullptr;
}

void Time::FrameTime::pauseTimer(bool i_input) {
  if (i_input == true) {
    isTimerPaused = true;
    LARGE_INTEGER *tempTick = new LARGE_INTEGER;
    assert(QueryPerformanceCounter(tempTick));
    pauseTimerTick = tempTick->QuadPart;
    delete tempTick;
  }  // end - if
  else
    isTimerPaused = false;
}

void Time::FrameTime::updateDeltaTime() {
  LARGE_INTEGER *tempTick = new LARGE_INTEGER;
  assert(QueryPerformanceCounter(tempTick));  // takes Pointer
  currentTick = tempTick->QuadPart;
  deltaTime =
      static_cast<float>(Time::getTimeDiff(lastTick, currentTick) /
                         static_cast<float>(frameTimeFrequency));

  // checking timer was paused or not, if stopped subtracting the pause time
  // from the time difference
  if (pauseTimerTick != 0) {
    deltaTime -= static_cast<uint32_t>(
        (Time::getTimeDiff(pauseTimerTick, currentTick)) /
        frameTimeFrequency);
    pauseTimerTick = 0;
  }

  // if (timeDiff > (1 / 60)) timeDiff = (1 / 60);
  lastTick = currentTick;
  delete tempTick;
}

float Time::FrameTime::getdeltaTime() { return deltaTime; }

uint64_t Time::FrameTime::getCurrentTick() {
  LARGE_INTEGER *tempTick = new LARGE_INTEGER;
  assert(QueryPerformanceCounter(tempTick));
  return (tempTick->QuadPart);
}

float Time::FrameTime::getdeltaTimeDuringFrame() {
  LARGE_INTEGER *tempTick = new LARGE_INTEGER;
  assert(QueryPerformanceCounter(tempTick));  // takes Pointer
  uint64_t tempCurrentTick = tempTick->QuadPart;
  float o_deltaTime =
      static_cast<float>(Time::getTimeDiff(lastTick, tempCurrentTick) /
                         static_cast<float>(frameTimeFrequency));
  delete tempTick;
  return o_deltaTime;
}

bool Time::FrameTime::getTimerStatus() { return isTimerPaused; }
