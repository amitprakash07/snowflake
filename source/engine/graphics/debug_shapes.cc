#include "../../Graphics/Line.h"
#include "../../Windows/WindowsFunctions.h"
#include "../EngineCore/EngineCore.h"
#include "../EngineCore/Objects/Scene.h"
#include "DebugShapes.h"

std::map<ShapeTarget,
         std::map<std::string, SharedPointer<Object>>>
    Debug::DebugShapes::debugShapeList;

bool Debug::DebugShapes::IsDebugShapesAvailable() {
  return (debugShapeList.size() > 0 ? true : false);
}

// Line
SharedPointer<Graphics::Line>
Debug::DebugShapes::DrawShape(std::string iName,
                                      ShapeTarget i_shapeType,
                                      Math::Vector3 iStartPoint,
                                      Math::Vector3 iEndPoint,
                                      Graphics::RGBColor iColor) {
  WindowsUtil::Assert(i_shapeType == LINE, "Shape Type is Not Line");
  Graphics::RGBAColor color;
  color.r = iColor.r;
  color.g = iColor.g;
  color.b = iColor.b;
  color.a = 1.0f;

  if (Graphics::Line::getLineCounts() == 0) {
    std::string materialFolderName = EngineCore::getMaterialFolderPath();
    materialFolderName += "Game/lineMaterial.mat";
    Graphics::Material::addMaterialToList(materialFolderName.c_str());
    Graphics::Line::setMaterialName(materialFolderName);
  }

  return Graphics::Line::AddLine(iStartPoint, iEndPoint, color);
}

// Sphere
SharedPointer<MeshObject> Debug::DebugShapes::DrawShape(
    std::string iName, ShapeTarget iShapeType, Math::Vector3 iCenter,
    float iRadius, Graphics::RGBColor iColor) {
  WindowsUtil::Assert(iShapeType == SPHERE, "Shape Type is Not Sphere");
  Graphics::RGBAColor color;
  color.r = iColor.r;
  color.g = iColor.g;
  color.b = iColor.b;
  color.a = 1.0f;
  SharedPointer<MeshObject> debugSphere =
      MeshObject::CreateMeshObject("Game/DebugSphereForClass.mesh",
                                           "Game/defaultDebugShapes.mat",
                                           color);
  debugSphere->EnableDebugging(true);
  debugSphere->getMaterial()->changeMaterialColor(iColor.r, iColor.g, iColor.b);
  Math::Vector3 tempPosition;
  tempPosition.x = iCenter.x;
  tempPosition.y = iCenter.y;
  tempPosition.z = iCenter.z;
  debugSphere->setTransform(tempPosition, Math::Quaternion());
  Scene::getRenderableScene()->addObjectToScene(debugSphere);

  SharedPointer<Object> tempObject = debugSphere.CastSharedPointer<Object>();
  debugShapeList[iShapeType][iName] = tempObject;
  return debugSphere;
}

// Box
SharedPointer<MeshObject> Debug::DebugShapes::DrawShape(
    std::string iName, ShapeTarget iShapeType, Math::Vector3 i_position,
    float iLength, float iWidth, float iHeight,
    Graphics::RGBColor iColor) {
  WindowsUtil::Assert(iShapeType == BOX, "Shape Type is Not Box");
  Graphics::RGBAColor color;
  color.r = iColor.r;
  color.g = iColor.g;
  color.b = iColor.b;
  color.a = 1.0f;
  SharedPointer<MeshObject> debugBox =
      MeshObject::CreateMeshObject(
          "Game/DebugCubeForClass.mesh", "Game/defaultDebugShapes.mat", color);
  debugBox->EnableDebugging(true);
  debugBox->getMaterial()->changeMaterialColor(iColor.r, iColor.g, iColor.b);
  Math::Vector3 tempPosition;
  tempPosition.x = i_position.x;
  tempPosition.y = i_position.y;
  tempPosition.z = i_position.z;
  debugBox->setTransform(tempPosition, Math::Quaternion());
  Scene::getRenderableScene()->addObjectToScene(debugBox);

  SharedPointer<Object> tempObject = debugBox.CastSharedPointer<Object>();
  debugShapeList[iShapeType][iName] = tempObject;
  return debugBox;
}

// Cylinder
SharedPointer<MeshObject> Debug::DebugShapes::DrawShape(
    std::string iName, ShapeTarget iShapeType, Math::Vector3 i_position,
    float iRadius, float iHeight, Graphics::RGBColor iColor) {
  WindowsUtil::Assert(iShapeType == CYLINDER, "Shape Type is Not Cylinder");
  Graphics::RGBAColor color;
  color.r = iColor.r;
  color.g = iColor.g;
  color.b = iColor.b;
  color.a = 1.0f;
  SharedPointer<MeshObject> debugCylinder =
      MeshObject::CreateMeshObject("Game/DebugCylinderForClass.mesh",
                                           "Game/defaultDebugShapes.mat",
                                           color);
  debugCylinder->EnableDebugging(true);
  debugCylinder->getMaterial()->changeMaterialColor(iColor.r, iColor.g,
                                                    iColor.b);
  Math::Vector3 tempPosition;
  tempPosition.x = i_position.x;
  tempPosition.y = i_position.y;
  tempPosition.z = i_position.z;
  debugCylinder->setTransform(tempPosition, Math::Quaternion());
  Scene::getRenderableScene()->addObjectToScene(debugCylinder);

  SharedPointer<Object> tempObject = debugCylinder.CastSharedPointer<Object>();
  debugShapeList[iShapeType][iName] = tempObject;
  return debugCylinder;
}

SharedPointer<Object> Debug::DebugShapes::GetDebugShape(
    std::string iName, ShapeTarget iShape) {
  for (std::map<ShapeTarget,
                std::map<std::string, SharedPointer<Object>>>::iterator i =
           debugShapeList.begin();
       i != debugShapeList.end(); ++i) {
    if (i->first == iShape) {
      for (std::map<std::string, SharedPointer<Object>>::iterator j =
               i->second.begin();
           j != i->second.end(); ++j) {
        if (j->first == iName) return j->second;
      }
    }
  }
  return SharedPointer<Object>();
}
