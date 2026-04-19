#ifndef ENGINE_COMMON_STRING_POOL_H
#define ENGINE_COMMON_STRING_POOL_H

#include <vector>

#include "additional_types.h"
#include "rtti.h"

namespace engine
{
    class StringPool : public RTTI
    {
    public:
        static SharedPointer<StringPool> Instance();
        char*                            FindString(const char*);
        std::string                      GetType() const override
        {
            return "";
        }
        bool IsSameType(SharedPointer<RTTI>, std::string) const override
        {
            return true;
        }
        ~StringPool();

    private:
        static SharedPointer<StringPool> string_pool_instance_;
        std::vector<typedefs::String>    string_list_;
        char*                            AddString(const char*);
        StringPool();
        StringPool(StringPool&);

    };  // end-StringPool
}  // namespace engine

#endif