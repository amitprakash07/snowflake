#include "../../../Externals/Raknet/src/BitStream.h"
#include "../../../Externals/Raknet/src/PacketPriority.h"
#include "../EngineCore/EngineCore.h"
#include "../Utilities/StringUtil.h"
#include "NetworkDefs.h"
#include "NetworkPlayer.h"

SharedPointer<Networking::NetworkPlayer>
Networking::NetworkPlayer::CreateNetworkPlayer(
    std::string i_meshFileName, std::string i_materialName,
    Math::Transform clientPlayerTransform, Graphics::RGBAColor iColor) {
  SharedPointer<NetworkPlayer> tempNetworkPlayer = SharedPointer<NetworkPlayer>(
      new NetworkPlayer(i_meshFileName, i_materialName, clientPlayerTransform,
                        iColor),
      "NetworkPlayer");
  return tempNetworkPlayer;
}

SharedPointer<Networking::NetworkPlayer>
Networking::NetworkPlayer::CreateNetworkPlayer(
    SharedPointer<MeshObject> iMeshObject) {
  SharedPointer<NetworkPlayer> tempPLayer = SharedPointer<NetworkPlayer>(
      new NetworkPlayer(iMeshObject), "NetworkPlayer");
  return tempPLayer;
}

SharedPointer<MeshObject>
Networking::NetworkPlayer::GetMeshObject() const {
  return mMeshObject;
}

Networking::NetworkPlayer::NetworkPlayer(
    std::string i_meshFileName, std::string i_materialName,
    Math::Transform clientPlayerTransform, Graphics::RGBAColor iColor) {
  SharedPointer<MeshObject> tempClientPlayer =
      MeshObject::CreateMeshObject(i_meshFileName, i_materialName, iColor);
  tempClientPlayer->setTransform(clientPlayerTransform.getPosition(),
                                 clientPlayerTransform.getOrientation());
  mMeshObject = tempClientPlayer;
}

Networking::NetworkPlayer::NetworkPlayer(
    SharedPointer<MeshObject> iMeshObject) {
  mMeshObject = iMeshObject;
}

void Networking::NetworkPlayer::SendNewNetworkPlayer(
    RakNet::RakPeerInterface* iServer) {
  std::string meshFileNameWithFullPath =
      mMeshObject->getMesh()->getMeshFileName();
  std::string meshFileName = Utils::RemoveString(
      meshFileNameWithFullPath, EngineCore::getMeshFolderPath());

  std::string materialFileNameWithFullPath = mMeshObject->getMaterialName();
  std::string materialFileName = Utils::RemoveString(
      materialFileNameWithFullPath, EngineCore::getMaterialFolderPath());

  Math::Transform networkPlayerTransform = mMeshObject->getTransform();

  Graphics::RGBAColor color = mMeshObject->GetVertexColor();

  RakNet::BitStream bsOut;
  bsOut.Write(static_cast<RakNet::MessageID>(ID_SPAWN_PLAYER));
  // Mesh File
  bsOut.Write(meshFileName.size());
  bsOut.Write(meshFileName.c_str(), meshFileName.size());

  // Material File
  bsOut.Write(materialFileName.size());
  bsOut.Write(materialFileName.c_str(), materialFileName.size());

  // Position
  bsOut.Write(networkPlayerTransform.getPosition().x);
  bsOut.Write(networkPlayerTransform.getPosition().y);
  bsOut.Write(networkPlayerTransform.getPosition().z);

  // Orientetion
  bsOut.Write(networkPlayerTransform.getOrientation().w());
  bsOut.Write(networkPlayerTransform.getOrientation().x());
  bsOut.Write(networkPlayerTransform.getOrientation().y());
  bsOut.Write(networkPlayerTransform.getOrientation().z());

  // Scale
  bsOut.Write(mMeshObject->getScale().x);
  bsOut.Write(mMeshObject->getScale().y);
  bsOut.Write(mMeshObject->getScale().z);

  // VertexColor
  bsOut.Write(color.r);
  bsOut.Write(color.g);
  bsOut.Write(color.b);
  bsOut.Write(color.a);

  // WireFrame Info
  bsOut.Write(mMeshObject->isDebugObject());

  // network Id
  bsOut.Write(GetNetworkID());

  iServer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0,
                RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

void Networking::NetworkPlayer::SendNetworkPlayerUpdates(
    RakNet::RakPeerInterface* iNetworkHandler) {
  // Send Information to all of the clients
  RakNet::BitStream bsOut;

  bsOut.Write(static_cast<RakNet::MessageID>(ID_SYNC_KEY_PRESS));

  // Network ID
  bsOut.Write(networkID);

  // Position
  bsOut.Write(mMeshObject->getTransform().getPosition().x);
  bsOut.Write(mMeshObject->getTransform().getPosition().y);
  bsOut.Write(mMeshObject->getTransform().getPosition().z);

  // Orientation
  bsOut.Write(mMeshObject->getTransform().getOrientation().w());
  bsOut.Write(mMeshObject->getTransform().getOrientation().x());
  bsOut.Write(mMeshObject->getTransform().getOrientation().y());
  bsOut.Write(mMeshObject->getTransform().getOrientation().z());

  iNetworkHandler->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0,
                        RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

void Networking::NetworkPlayer::SetControlPlayer(
    bool i_isControlPlayer) {
  isControlPlayer = i_isControlPlayer;
}

bool Networking::NetworkPlayer::GetControlPlayerStatus() const {
  return isControlPlayer;
}
