#ifndef ENGINE_COMMON_CORE_OBJECTS_H
#define ENGINE_COMMON_CORE_OBJECTS_H

#include <map>

#include "additional_types.h"

namespace engine {

enum class ObjectProperty : uint32_t { Default = 0 };

class IObjectPropertyAttributes {
 public:
  virtual ~IObjectPropertyAttributes() = default;
};

class IObject {
 public:
  virtual ~IObject() = default;
  virtual void AddObjectPropertyAttributes(
      ObjectProperty property, IObjectPropertyAttributes* attributes) = 0;
  virtual IObjectPropertyAttributes* RemovePropertyAttributes(
      ObjectProperty property) = 0;
};

class ObjectDefaultPropertyAttributes : public IObjectPropertyAttributes {
 public:
  ObjectDefaultPropertyAttributes() = default;
};

class DefaultObject : public IObject {
 public:
  DefaultObject() : default_attributes_() {
    object_property_attributes_map_[ObjectProperty::Default] =
        &default_attributes_;
  }
  ~DefaultObject() = default;

 private:
  ObjectDefaultPropertyAttributes default_attributes_;
  std::map<ObjectProperty, IObjectPropertyAttributes*>
      object_property_attributes_map_;
};
}  // namespace engine

#endif