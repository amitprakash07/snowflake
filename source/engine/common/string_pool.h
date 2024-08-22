#ifndef ENGINE_COMMON_STRING_POOL_H
#define ENGINE_COMMON_STRING_POOL_H

#include <vector>

#include "rtti.h"
#include "additional_types.h"

namespace engine {
class StringPool : public RTTI {
 public:
  static SharedPointer<StringPool> getStringPool();
  char* findString(char*);
  std::string getTypeInfo() const override { return ""; }
  bool isBothSameType(SharedPointer<RTTI>, std::string) const override {
    return true;
  }
  ~StringPool();

 private:
  static SharedPointer<StringPool> mStringPool;
  std::vector<typedefs::String> mStringList;
  char* addString(char*);
  StringPool();
  StringPool(StringPool&);

};  // end-StringPool
}  

#endif  //__STRING_POOL_H