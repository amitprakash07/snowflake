#ifndef ENGINE_COMMON_MESSAGE_HANDLER_H
#define ENGINE_COMMON_MESSAGE_HANDLER_H

#include "rtti.h"
#include "shared_pointer.h"
#include "additional_types.h"
#include "hashed_string.h"

namespace engine
{
    class IMessageHandler : public RTTI
    {
    public:
        virtual void HandleMessage(utils::StringHash&, SharedPointer<RTTI> i_MessageSender,
                                   void* i_pMessageData) = 0;  // Do not delete i_messageSenderPointer
        virtual ~IMessageHandler(){};
        IMessageHandler(){};
    };

    struct _IMessageHandle
    {
        SharedPointer<IMessageHandler> mHandler;
        typedefs::Priority             mMessagePriority;

        _IMessageHandle(SharedPointer<IMessageHandler> i_handler, typedefs::Priority i_priority)
        {
            // MessagedAssert(i_handler != nullptr, "Handle Pointer is NUll");
            mHandler         = i_handler;
            mMessagePriority = i_priority;
        }

        bool operator<(_IMessageHandle i_other) const
        {
            return (mMessagePriority < i_other.mMessagePriority ? true : false);
        }

        _IMessageHandle() = default;
        _IMessageHandle operator=(const _IMessageHandle&) const
        {
            return _IMessageHandle();
        }
    };
    typedef _IMessageHandle MessageHandle;
}  // namespace engine

#endif