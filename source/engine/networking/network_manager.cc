#include "../../Windows/WindowsFunctions.h"
#include "NetworkManager.h"

SharedPointer<Networking::NetworkManager>
    Networking::NetworkManager::mNetworkManager;

void Networking::NetworkManager::CreateNetworkManager(
    bool i_isServer, std::string iServerAddress) {
  if (mNetworkManager.isNull()) {
    SharedPointer<NetworkManager> temp =
        SharedPointer<NetworkManager>(new NetworkManager(), "NetworkManager");
    mNetworkManager = temp;
    mNetworkManager->mIsServer = i_isServer;

    switch (i_isServer) {
      case true:
        mNetworkManager->mSystem.mServer->CreateServerInterface();
        mNetworkManager->mSystem.mServer->ServerStartUp();
        break;
      case false:
        mNetworkManager->mSystem.mClient->CreateClientInterface();
        mNetworkManager->mSystem.mClient->SetIP();
        mNetworkManager->mSystem.mClient->ClientStartup();
        break;
    }
  }
}

Networking::Handler Networking::NetworkManager::GetHandler() {
  return mNetworkManager->mSystem;
}

Networking::NetworkPacket
Networking::NetworkManager::getReceivedNetworkPacket() {
  return mNetworkManager->receivingNetworkPacket;
}

void Networking::NetworkManager::setSendingNetworkPacket(
    NetworkPacket iSendingNetworkPacket) {
  mNetworkManager->sendingNetworkPacket = iSendingNetworkPacket;
}

bool Networking::NetworkManager::isServerInstance() {
  return mNetworkManager->mIsServer;
}

void Networking::NetworkManager::updateNetwork() {
  switch (mNetworkManager->isServerInstance()) {
    case true:
      mNetworkManager->mSystem.mServer->ReceivePackets();
      break;
    case false:
      mNetworkManager->mSystem.mClient->ReceivePackets();
      break;
  }
}

Networking::GameMessages
Networking::NetworkManager::getCurrentMessage() {
  return mNetworkManager->currentGameMessage;
}

std::string Networking::NetworkManager::getCurrentMessageString() {
  return "";
}

void Networking::NetworkManager::ShutDownNetwork() {}

Networking::NetworkManager::NetworkManager() {
  mIsServer = false;
  isConnected = false;
  Handler tempHandler = Handler();
  mSystem = tempHandler;
}
