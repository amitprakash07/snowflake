#ifndef CORE_COMMON_CORE_H
#define CORE_COMMON_CORE_H

#include <string>
#include <atomic>
#include <format>

namespace amit
{
    struct ObjectId
    {
        uint64_t value() const
        {
            return id_;
        }

        explicit ObjectId(uint64_t id)
            : id_(id)
        {
        }

    private:
        uint64_t id_;
    };

    struct IdGenerator
    {
        static uint64_t GetNextId()
        {
            static std::atomic_uint64_t current_id_{0};
            ++current_id_;
            return current_id_;
        }
    };

    template <class ObjectType>
    concept ObjectTypeEnumConcept = std::is_enum_v<ObjectType> && requires(ObjectType enum_type) {
        { TypeToString(enum_type) } -> std::convertible_to<std::string_view>;
    };

    template <ObjectTypeEnumConcept ObjectType>
    struct ObjectLabel
    {
        ObjectLabel(ObjectType type, const std::string& name)
            : object_name(name)
            , object_type(type)
            , object_id(IdGenerator::GetNextId())
        {
        }

        ObjectLabel(ObjectType type)
            : object_name("")
            , object_type(type)
            , object_id(IdGenerator::GetNextId())
        {
        }

        ObjectLabel() = delete;

        void SetName(const std::string& name)
        {
            object_name = name;
        }

        std::string ToString() const
        {
            std::string ret_string = std::format("[Type:{}, Name: {}, Id: {}]",
                                                 TypeToString(object_type),
                                                 object_name.empty() ? "None" : object_name,
                                                 object_id.value());
            return ret_string;
        }

    private:
        std::string object_name;
        ObjectType  object_type;
        ObjectId    object_id;
    };

}  // namespace amit

#endif
