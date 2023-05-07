#ifndef __STRING_POOL_H
#define __STRING_POOL_H

#include <vector>

#include "../Utilities/RTTI.h"
#include "../Utilities/additionaltypes.h"

namespace PROJECT_NAMESPACE {
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