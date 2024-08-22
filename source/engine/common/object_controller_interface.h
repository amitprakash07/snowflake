#ifndef ENGINE_COMMON_OBJECT_CONTROLLER_INTERFACE_H
#define ENGINE_COMMON_OBJECT_CONTROLLER_INTERFACE_H

#include "additional_types.h"

namespace engine {
class Object;
class IObjectController {
 public:
  virtual ~IObjectController() = default;
  virtual void updateObject(Object &,
                            typedefs::ActionWithKeyBound iAction) = 0;  
};
}  

#endif