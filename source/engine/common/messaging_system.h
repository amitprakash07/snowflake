#ifndef __MESSAGING_SYSTEM_H
#define __MESSAGING_SYSTEM_H

#include <map>
#include <vector>

#include "../Utilities/HashedString.h"
#include "../Utilities/IMessageHandler.h"
#include "../Utilities/RTTI.h"

namespace PROJECT_NAMESPACE {
class MessagingSystem : public RTTI {
 public:
  static SharedPointer<MessagingSystem> getMessagingSystem();
  void addMessageHandler(utils::StringHash&,
                         SharedPointer<IMessageHandler>,
                         typedefs::Priority);
  bool removeMessageHandler(utils::StringHash&,
                            SharedPointer<IMessageHandler>);
  ~MessagingSystem();

  // template<typename T>
  void sendMessage(utils::StringHash&, SharedPointer<RTTI>,
                   void* message_data = nullptr);
  std::string getTypeInfo() const override { return ""; }
  bool isBothSameType(SharedPointer<RTTI>, std::string) const override {
    return true;
  }

 private:
  static SharedPointer<MessagingSystem> mMessagingSystem;
  std::map<utils::StringHash, std::vector<MessageHandle>>
      m_MessageHandlers;
  MessagingSystem();
};
}  

#endif