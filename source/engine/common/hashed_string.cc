#include <string>

#include "hashed_string.h"
namespace engine
{
    namespace utils
    {
        bool StringHash::isNil() const
        {
            return (mHash == StringHash("\0").getHash() ? true : false);
        }

        StringHash::StringHash()
        {
            StringHash("\0");
        }  // end default constructor

        StringHash::StringHash(const char* i_string)
            : mHash(Hash(i_string))
        {
#ifdef _DEBUG
            mString = _strdup(i_string);
#endif
        }  // end parameterized constructor

        StringHash::StringHash(const StringHash& i_other)
            : mHash(i_other.mHash)
        {
#ifdef _DEBUG
            mString = _strdup(i_other.mString);
#endif
        }  // end copy constructor

        StringHash& StringHash::operator=(const StringHash& i_other)
        {
            mHash = i_other.mHash;
#ifdef _DEBUG
            if (mString)
                free(mString);

            mString = _strdup(i_other.mString);
#endif
            return *this;
        }  // end operator=

        bool StringHash::operator==(const StringHash& i_other) const
        {
            return (mHash == i_other.mHash ? true : false);
        }  // end operator ==

        bool StringHash::operator!=(const StringHash& i_other) const
        {
            return (mHash != i_other.mHash ? true : false);
        }

        bool StringHash::operator<(const StringHash& i_other) const
        {
            return (mHash < i_other.mHash);
        }

        unsigned __int32 StringHash::getHash() const
        {
            return mHash;
        }  // end getHash()

        unsigned __int32 StringHash::Hash(const char* i_string)
        {
            return (Hash(reinterpret_cast<void*>(const_cast<char*>(i_string)), strlen(i_string)));
        }  // end Hash(char*)

        unsigned __int32 StringHash::Hash(const void* i_bytes, size_t i_length)
        {
            /*
   * register storage specifier is deprecated from c++17
   * register const unsigned char* p = static_cast<const unsigned char*>(i_bytes);*/

            const unsigned char* p    = static_cast<const unsigned char*>(i_bytes);
            unsigned int         hash = 2166136261;

            for (unsigned int i = 0; i < i_length; ++i)
                hash = 16777619 * (hash ^ p[i]);

            return hash ^ (hash >> 16);
        }  // end Hash(void*, size_t)
    }  // end namespace utils
}  // namespace engine