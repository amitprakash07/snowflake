#pragma once

#ifndef __DEBUG_SHAPES_H
#define __DEBUG_SHAPES_H

#define GAME_ENGINE_DEBUG_MODE
#include "../../Graphics/Line.h"

#ifdef GAME_ENGINE_DEBUG_MODE

#include "../../Graphics/typedefs.h"
#include "../EngineCore/Objects/MeshObject.h"
#include "../Utilities/SharedPointer.h"

namespace Engine {
enum ShapeTarget {
  SPHERE = 0,    // Needs radius,position
  BOX = 1,       // Need Position, length, breadth,height
  CYLINDER = 2,  // Need position, radius, height
  LINE = 3       // Need two positions
};
namespace Debug {
class DebugShapes {
 public:
  static bool IsDebugShapesAvailable();
  static SharedPointer<Object> GetDebugShape(std::string iName,
                                             ShapeTarget iShape);
  static SharedPointer<MeshObject> DrawShape(
      std::string iName, ShapeTarget, Engine::Math::Vector3,
      float iRadius = 1.0f,
      Engine::Graphics::RGBColor = Engine::Graphics::RGBColor(0.0f, 1.0f,
                                                              0.0f));  // Sphere

  static SharedPointer<MeshObject> DrawShape(
      std::string iName, ShapeTarget, Engine::Math::Vector3,
      float iLength = 1.0f, float iWidth = 1.0f, float iHeight = 1.0f,
      Engine::Graphics::RGBColor = Engine::Graphics::RGBColor(0.0f, 1.0f,
                                                              0.0f));  // Box

  static SharedPointer<MeshObject> DrawShape(
      std::string iName, ShapeTarget, Engine::Math::Vector3,
      float iRadius = 1.0f, float iHeight = 1.0f,
      Engine::Graphics::RGBColor =
          Engine::Graphics::RGBColor(0.0f, 1.0f, 0.0f));  // Cylinder

  static SharedPointer<Engine::Graphics::Line> DrawShape(
      std::string iName, ShapeTarget, Engine::Math::Vector3,
      Engine::Math::Vector3,
      Engine::Graphics::RGBColor = Engine::Graphics::RGBColor(0.0f, 1.0f,
                                                              0.0f));  // Line
 private:
  DebugShapes();
  static std::map<ShapeTarget,
                  std::map<std::string, SharedPointer<Engine::Object>>>
      debugShapeList;
  Engine::SharedPointer<Engine::Object> debugShape;
};
}  // namespace Debug
}  // namespace Engine
#endif

#endif