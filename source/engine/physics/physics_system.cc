#include "../EngineCore/EngineCore.h"
#include "../EngineCore/Objects/Scene.h"
#include "PhysicsSystem.h"
#include "RayIntersection.h"

SharedPointer<Physics::PhysicsSystem>
    Physics::PhysicsSystem::mPhysicsSystem;

void Physics::PhysicsSystem::InitializePhysicsSystem(
    std::string iCollisionMesh) {
  if (mPhysicsSystem.isNull()) {
    SharedPointer<PhysicsSystem> tempPhysicsSystem =
        SharedPointer<PhysicsSystem>(new PhysicsSystem(), "Physicssystem");
    mPhysicsSystem = tempPhysicsSystem;

    SharedPointer<MeshObject> mCollsionMeshObject =
        MeshObject::CreateMeshObject(iCollisionMesh,
                                             "Game/Arena/metalMaterial.mat");
    mPhysicsSystem->mMeshObject = mCollsionMeshObject;

    mCollsionMeshObject->EnableDebugging(true);
    mCollsionMeshObject->setRenderable(false);
    Scene::getRenderableScene()->addObjectToScene(mCollsionMeshObject);

    std::string meshFolderPath = EngineCore::getMeshFolderPath();
    iCollisionMesh = meshFolderPath + iCollisionMesh;

    SharedPointer<Graphics::Mesh> tempMesh =
        Graphics::Mesh::getMesh(iCollisionMesh);
    mPhysicsSystem->mCollisionMesh = tempMesh;
    mPhysicsSystem->collisionDebugging = false;

    SharedPointer<Graphics::Line> ab = Graphics::Line::AddLine(
        Math::Vector3(0, 0, 0), Math::Vector3(0, 0, 0),
        Graphics::RGBAColor(0, 1, 0, 1));

    SharedPointer<Graphics::Line> bc = Graphics::Line::AddLine(
        Math::Vector3(0, 0, 0), Math::Vector3(0, 0, 0),
        Graphics::RGBAColor(0, 1, 0, 1));

    SharedPointer<Graphics::Line> ca = Graphics::Line::AddLine(
        Math::Vector3(0, 0, 0), Math::Vector3(0, 0, 0),
        Graphics::RGBAColor(0, 1, 0, 1));

    mPhysicsSystem->AB = ab;
    mPhysicsSystem->BC = bc;
    mPhysicsSystem->AC = ca;
  }
}

Physics::PhysicsSystem::PhysicsSystem() { showCollisionMesh = false; }

void Physics::PhysicsSystem::SetShowCollisionMesh(bool iRequest) {
  mPhysicsSystem->showCollisionMesh = iRequest;
  if (iRequest)
    mPhysicsSystem->mMeshObject->setRenderable(true);
  else
    mPhysicsSystem->mMeshObject->setRenderable(false);
}

bool Physics::PhysicsSystem::ShowCollisionMesh() {
  return mPhysicsSystem->showCollisionMesh;
}

void Physics::PhysicsSystem::DrawCollisionMesh() {
  mPhysicsSystem->mMeshObject->draw(true);
}

SharedPointer<Physics::PhysicsSystem>
Physics::PhysicsSystem::GetPhysicsSystem() {
  return mPhysicsSystem;
}

bool Physics::PhysicsSystem::CheckCollision(Ray iRay,
                                                    HitInfo& hitInfo) const {
  Triangle* tempTriangle = mCollisionMesh->GetTriangles();

  Math::Vector3 vertexA;
  Math::Vector3 vertexB;
  Math::Vector3 vertexC;

  float distance = hitInfo.distance;
  HitInfo currentHitInfo;
  currentHitInfo.distance = BIG_FLOAT;
  for (int i = 0; i < mCollisionMesh->GetTriangleCount(); i++) {
    vertexA =
        Math::Vector3(tempTriangle[i].vertexA.X, tempTriangle[i].vertexA.Y,
                      tempTriangle[i].vertexA.Z);
    vertexB =
        Math::Vector3(tempTriangle[i].vertexB.X, tempTriangle[i].vertexB.Y,
                      tempTriangle[i].vertexB.Z);
    vertexC =
        Math::Vector3(tempTriangle[i].vertexC.X, tempTriangle[i].vertexC.Y,
                      tempTriangle[i].vertexC.Z);

    /*AB->mLineStruct.startPoint = vertexA;
    AB->mLineStruct.endPoint = vertexB;

    BC->mLineStruct.startPoint = vertexB;
    BC->mLineStruct.endPoint = vertexC;

    AC->mLineStruct.startPoint = vertexA;
    AC->mLineStruct.endPoint = vertexC;*/

    // Graphics::Line::drawLines(true);

    if (iRay.IntersectTriangle(vertexA, vertexB, vertexC, hitInfo) &&
        hitInfo.distance < currentHitInfo.distance) {
      currentHitInfo = hitInfo;
    }
  }

  if (currentHitInfo.distance < distance) return true;

  return false;
}

bool Physics::PhysicsSystem::CheckCollision(Math::Vector3 startPoint,
                                                    Math::Vector3 endPoint,
                                                    HitInfo& iHitInfo) {
  Triangle* tempTriangle = mCollisionMesh->GetTriangles();
  bool intersected = false;

  for (int i = 0; i < mCollisionMesh->GetTriangleCount(); i++) {
    if (IntersectTriangle(startPoint, endPoint, tempTriangle[i], iHitInfo)) {
      intersected = true;
      break;
    }
  }

  return intersected;
}

bool Physics::PhysicsSystem::IntersectTriangle(
    Math::Vector3 startPoint, Math::Vector3 EndPoint, Triangle iTriangle,
    HitInfo& iHitInfo) const {
  Math::Vector3 tv0(iTriangle.vertexA.X, iTriangle.vertexA.Y,
                    iTriangle.vertexA.Z);
  Math::Vector3 tv1(iTriangle.vertexB.X, iTriangle.vertexB.Y,
                    iTriangle.vertexB.Z);
  Math::Vector3 tv2(iTriangle.vertexC.X, iTriangle.vertexC.Y,
                    iTriangle.vertexC.Z);

  Math::Vector3 intersectionPoint;

  Math::Vector3 u, v,
      n(iTriangle.vertexA.nx, iTriangle.vertexA.ny, iTriangle.vertexA.nz);
  Math::Vector3 dir, w0, w;
  float r, a, b;

  u = tv1 - tv0;
  v = tv2 - tv0;

  dir = EndPoint - startPoint;
  w0 = startPoint - tv0;

  a = n.dot(w0);
  b = -n.dot(dir);

  if (b <= 0.0f) return false;

  r = a / b;
  if (r < 0.0f) return false;
  if (r > 1.0f) return false;

  intersectionPoint = startPoint + dir * r;

  float uu, uv, vv, wu, wv, D;
  uu = u.dot(u);
  uv = u.dot(v);
  vv = v.dot(v);
  w = w0 + dir * r;
  wu = w.dot(u);
  wv = w.dot(v);
  D = uv * uv - uu * vv;

  float s, t;
  s = (uv * wv - vv * wu) / D;
  if (s < 0.0f || s > 1.0f) return false;
  t = (uv * wu - uu * wv) / D;
  if (t < 0.0f || (s + t) > 1.0f) return false;

  iHitInfo.hitPoint.x = intersectionPoint.x;
  iHitInfo.hitPoint.y = intersectionPoint.y;
  iHitInfo.hitPoint.z = intersectionPoint.z;

  iHitInfo.normal.x = n.x;
  iHitInfo.normal.y = n.y;
  iHitInfo.normal.z = n.z;

  iHitInfo.normal.Normalize();
  return true;
}

bool Physics::PhysicsSystem::CollisionDebuggingStatus() {
  return mPhysicsSystem->collisionDebugging;
}

void Physics::PhysicsSystem::EnableCollisionDebugging(bool iRequest) {
  mPhysicsSystem->collisionDebugging = iRequest;
  if (iRequest) mPhysicsSystem->mMeshObject->EnableDebugging(false);
}
