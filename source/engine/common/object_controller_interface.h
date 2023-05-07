#ifndef __IOBJECT_CONTROLLER
#define __IOBJECT_CONTROLLER

#include "additionaltypes.h"

namespace PROJECT_NAMESPACE {
class Object;
class IObjectController {
 public:
  virtual ~IObjectController(){};
  virtual void updateObject(Object &,
                            typedefs::ActionWithKeyBound iAction) = 0;
  IObjectController() {}
};
}  

#endif