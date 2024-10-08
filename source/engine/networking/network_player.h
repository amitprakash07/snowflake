#ifndef __NETWORK_PLAYER_H
#define __NETWORK_PLAYER_H
#include "../../../Externals/Raknet/src/NetworkIDObject.h"
#include "../EngineCore/Objects/MeshObject.h"
#include "../Utilities/SharedPointer.h"

namespace engine {
namespace Networking {

class NetworkPlayer : public RakNet::NetworkIDObject {
 public:
  static SharedPointer<NetworkPlayer> CreateNetworkPlayer(
      std::string i_meshFileName, std::string i_materialName,
      Math::Transform clientPlayerTransform = Math::Transform(),
      Graphics::RGBAColor = {1.0f, 1.0f, 1.0f, 1.0f});

  static SharedPointer<NetworkPlayer> CreateNetworkPlayer(
      SharedPointer<MeshObject> iMeshObject);

  void SetControlPlayer(bool i_isControlPlayer);
  bool GetControlPlayerStatus() const;

  SharedPointer<MeshObject> GetMeshObject() const;
  void SendNewNetworkPlayer(RakNet::RakPeerInterface* iServer);
  void SendNetworkPlayerUpdates(RakNet::RakPeerInterface* iServer);

 private:
  NetworkPlayer(std::string i_meshFileName, std::string i_materialName,
                Math::Transform clientPlayerTransform = Math::Transform(),
                Graphics::RGBAColor = {1.0f, 1.0f, 1.0f, 1.0f});
  NetworkPlayer(SharedPointer<MeshObject> iMeshObject);
  SharedPointer<MeshObject> mMeshObject;
  bool isSpawned;
  bool isControlPlayer;
};
}  // namespace Networking
}  
#endif