#ifndef __RTTI_H
#define __RTTI_H

#include <string>

#include "SharedPointer.h"

#define MAKE_STRING(X) #X

namespace engine {
template <typename TypeName> 
  std::string ToString() { return MAKE_STRING(TypeName); }
;
class RTTI {
public:
  virtual std::string getTypeInfo() const = 0;
  virtual bool isBothSameType(SharedPointer<RTTI>, std::string) const = 0;

  virtual ~RTTI(){};
  RTTI(){};
};

} // namespace engine

#endif