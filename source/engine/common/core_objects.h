#ifndef ENGINE_COMMON_CORE_OBJECTS_H
#define ENGINE_COMMON_CORE_OBJECTS_H

#include <map>

#include "additional_types.h"

namespace engine
{
    // Enum for type of Object property
    enum class ObjectProperty : uint8_t
    {
        Default = 0
    };

    // Interface IObjectPropertyAttributes class for describing object property
    // attributes
    class IObjectPropertyAttributes
    {
    public:
        IObjectPropertyAttributes()          = delete;
        virtual ~IObjectPropertyAttributes() = default;
        virtual void Describe()              = 0;
    };

    // Interface class for all objects
    class IObject
    {
    public:
        IObject()          = delete;
        virtual ~IObject() = default;
        virtual void AddObjectPropertyAttributes(ObjectProperty property, IObjectPropertyAttributes* attributes) = 0;
        virtual IObjectPropertyAttributes* RemovePropertyAttributes(ObjectProperty property)                     = 0;
        virtual uint64_t                   GetId() const                                                         = 0;
    };

    class ObjectId
    {
    public:
        ObjectId()
        {
            id_ = GetNewUniqueId();
        }

        static uint64_t GetNewUniqueId()
        {
            id_counter++;
            return id_counter;
        }

    private:
        uint64_t               id_;
        inline static uint64_t id_counter = 0;
    };

    // Default Object Property
    class ObjectDefaultPropertyAttributes : public IObjectPropertyAttributes
    {
    public:
        ObjectDefaultPropertyAttributes() = delete;
    };

    // Default Object
    class Object : public IObject
    {
    public:
        Object()
            : default_attributes_()
        {
            object_property_attributes_map_[ObjectProperty::Default] = &default_attributes_;
        }

        ~Object() = default;

    private:
        ObjectDefaultPropertyAttributes                      default_attributes_;
        std::map<ObjectProperty, IObjectPropertyAttributes*> object_property_attributes_map_;
        ObjectId                                             obj_id_;
    };
}  // namespace engine

#endif