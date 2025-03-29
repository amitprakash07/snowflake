/*
This file contains wrappers for Windows functions
*/

#ifndef ENGINE_OS_WIN32_OS_WIN32_UTILS_H_
#define ENGINE_OS_WIN32_OS_WIN32_UTILS_H_

#include <assert.h>

#include <cstdint>
#include <sstream>
#include <string>

#include "os_win32_includes.h"

namespace WindowsUtil {
// Interface
//==========

bool CopyFile(const char* const i_path_source, const char* const i_path_target,
              const bool i_shouldFunctionFailIfTargetAlreadyExists = false,
              const bool i_shouldTargetFileTimeBeModified = false,
              std::string* o_errorMessage = nullptr);

bool CreateDirectoryIfNecessary(const std::string& i_path,
                                std::string* o_errorMessage = nullptr);

bool DoesFileExist(const char* const i_path,
                   std::string* o_errorMessage = nullptr,
                   DWORD* o_errorCode = nullptr);

bool ExecuteCommand(const char* const i_command, DWORD* o_exitCode = nullptr,
                    std::string* o_errorMessage = nullptr);

bool ExecuteCommand(const char* const i_command,
                    const char* const i_optionalArguments = nullptr,
                    DWORD* o_exitCode = nullptr,
                    std::string* o_errorMessage = nullptr);

bool GetVSEnvironmentVariable(const char* const i_key, std::string& o_value,
                              std::string* o_errorMessage = nullptr);

std::string GetFormattedWindowsError(const DWORD i_errorCode);

std::string GetLastWindowsError(DWORD* o_optionalErrorCode = nullptr);

bool GetLastWriteTime(const char* const i_path, uint64_t& o_lastWriteTime,
                      std::string* o_errorMessage = nullptr);

void Print(std::string, const char* i_optionalFileName = nullptr);

bool Assert(bool, std::string = NULL);

bool setVSEnvironmentVariableValue(const char* variableName, const char* value);

void displayToOutPutWindow(std::string iString);
}  // namespace WindowsUtil

#endif
