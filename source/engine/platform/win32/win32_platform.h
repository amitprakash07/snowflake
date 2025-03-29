/*
This file contains wrappers for Windows functions
*/

#ifndef ENGINE_OS_WIN32_OS_WIN32_UTILS_H_
#define ENGINE_OS_WIN32_OS_WIN32_UTILS_H_

#include <assert.h>

#include <cstdint>
#include <string>

#include "platform/platform.h"
#include "win32_platform_includes.h"

namespace engine
{
    class Win32Platform : public Platform
    {
        // Environment variable
        bool GetEnvVar(const char* env_var, std::string& env_val, std::string* error_message = nullptr) override;

        bool SetEnvVar(const char* env_var, const std::string& env_val, std::string* error_message = nullptr) override;

        // File System
        bool CopyFile(const char*  path_source,
                      const char*  path_target,
                      bool         overwrite     = false,
                      bool         modify_time   = false,
                      std::string* error_message = nullptr) override;

        bool CreateDirectoryIfNecessary(const std::string& directory_path,
                                        std::string*       error_message = nullptr) override;

        bool DoesFileExist(const std::string& file_path, std::string* error_message = nullptr) override;

        bool GetLastWriteTime(const std::string& file_path,
                              uint64_t&          last_write_time,
                              std::string*       error_message = nullptr) override;

        // Process Handling
        bool ExecuteCommand(const std::string& command, std::string* error_message = nullptr) override;

        bool ExecuteCommand(const std::string& command,
                            const std::string* optional_arguments = nullptr,
                            std::string*       error_message      = nullptr) override;

        // Error
        std::string GetLastWindowsError(DWORD* error_code = nullptr);

        std::string GetFormattedWindowsError(DWORD error_code);
    };

    //std::string GetFormattedWindowsError(const DWORD i_errorCode);

    //std::string GetLastWindowsError(DWORD* o_optionalErrorCode = nullptr);

    /*void Print(std::string, const char* i_optionalFileName = nullptr);

    bool Assert(bool, std::string = NULL);*/

    //    void displayToOutPutWindow(std::string iString);
}  // namespace engine

#endif
