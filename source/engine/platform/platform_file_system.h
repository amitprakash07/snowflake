#ifndef ENGINE_PLATFORM_PLATFORM_FILE_SYSTEM_H_
#define ENGINE_PLATFORM_PLATFORM_FILE_SYSTEM_H_

#include <string>

namespace engine
{
    class FileSystem
    {
    public:
        enum class Status
        {

        };

        static FileSystem* LocalFileSystem();

        virtual ~FileSystem() = default;

        

    private:
        FileSystem() = default;
    };
}  // namespace engine

#endif