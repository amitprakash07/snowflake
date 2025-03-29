#ifndef ENGINE_PLATFORM_PLATFORM_INFO_H_
#define ENGINE_PLATFORM_PLATFORM_INFO_H_

#include <string>

namespace engine
{
    class Platform
    {
    public:
        virtual ~Platform() = default;

        // Environment variable
        virtual bool GetEnvVar(const char*  environment_var,
                               std::string& environment_value,
                               std::string* error_message = nullptr) = 0;

        virtual bool SetEnvVar(const char*        environment_var,
                               const std::string& environment_value,
                               std::string*       error_message = nullptr) = 0;

        // File System
        virtual bool CopyFile(const char*  path_source,
                              const char*  path_target,
                              bool         overwrite     = false,
                              bool         modify_time   = false,
                              std::string* error_message = nullptr) = 0;

        virtual bool CreateDirectoryIfNecessary(const std::string& directory_path,
                                                std::string*       error_message = nullptr) = 0;

        virtual bool DoesFileExist(const std::string& file_path, std::string* error_message = nullptr) = 0;

        virtual bool GetLastWriteTime(const std::string& file_path,
                                      uint64_t&          last_write_time,
                                      std::string*       error_message = nullptr) = 0;

        // Process Handling
        virtual bool ExecuteCommand(const std::string& command, std::string* error_message = nullptr) = 0;

        virtual bool ExecuteCommand(const std::string& command,
                                    const std::string* optional_arguments = nullptr,
                                    std::string*       error_message      = nullptr) = 0;
    };

}  // namespace engine

#endif
