#include <cassert>
#include <iostream>
#include <ShlObj.h>
#include <sstream>
#include <ctime>

#include "platform/platform_systems.h"

engine::Platform* engine::Platform::platform_ = nullptr;
uint16_t const    engine::kFilePathMaxSize    = MAX_PATH;

bool engine::Platform::Initialize(const EngineStartupInfo* engine_startup_info)
{
    if (platform_ == nullptr)
    {
        platform_ = new Platform();
    }

    if (platform_)
    {
        if (!platform_->initialized_)
        {
            bool success = true;
            for (uint8_t i = 0; i < static_cast<uint8_t>(PlatformHandlerType::Count); i++)
            {
                IPlatformSystem*& platform_handler = platform_->platform_handlers_[i];

                if (platform_handler == nullptr)
                {
                    switch (static_cast<PlatformHandlerType>(i))
                    {
                    case PlatformHandlerType::File:
                        platform_handler = new FileSystem();
                        break;
                    case PlatformHandlerType::Process:
                        platform_handler = new ProcessSystem();
                        break;
                    case PlatformHandlerType::Error:
                        platform_handler = new ErrorSystem();
                        break;
                    case PlatformHandlerType::Logging:
                        platform_handler = new LoggingSystem();
                        break;
                    case PlatformHandlerType::Windowing:
                        if (engine_startup_info != nullptr)
                        {
                            platform_handler = new WindowingSystem(engine_startup_info->win_display_state);
                        }
                        break;

                    case PlatformHandlerType::UnRegistered:
                    case PlatformHandlerType::Count:
                        break;
                    }
                }

                if (platform_handler != nullptr)
                {
                    if (!platform_handler->IsInitialized())
                    {
                        success &= platform_handler->StartUp();
                    }
                }
            }

            if (success)
            {
                platform_->initialized_ = true;
            }
        }

        return platform_->initialized_;
    }

    return false;
}

engine::Platform* engine::Platform::Instance()
{
    return platform_;
}

bool engine::Platform::ShutDown()
{
    bool success = true;
    if (platform_)
    {
        if (platform_->initialized_)
        {
            for (uint8_t i = 0; i < static_cast<uint8_t>(PlatformHandlerType::Count); i++)
            {
                IPlatformSystem*& platform_handler = platform_->platform_handlers_[i];

                if (platform_handler != nullptr)
                {
                    if (platform_handler->IsInitialized())
                    {
                        success &= platform_handler->ShutDown();
                        delete platform_handler;
                        platform_handler = nullptr;
                    }
                }
            }
        }

        delete platform_;
        platform_ = nullptr;
    }

    return success;
}

bool engine::Platform::GetEnvVar(const char* const env_var, std::string& env_val, std::string* error_message)
{
    // Windows requires a character buffer
    // to copy the environment variable into.
    // An arbitrary value is chosen that "should" be "big enough":
    constexpr DWORD max_character_count = MAX_PATH;
    char            buffer[max_character_count];
    // Ask Windows for the environment variable
    const DWORD character_count = ::GetEnvironmentVariable(env_var, buffer, max_character_count);
    if (character_count > 0)
    {
        if (character_count <= max_character_count)
        {
            env_val = buffer;
            return true;
        }
        else
        {
            // If you're seeing this error you will need to increase maxCharacterCount
            if (error_message)
            {
                std::stringstream error_message_stream;
                error_message_stream << "The environment variable \"" << env_var << "\" requires " << character_count
                                     << " characters and the provided buffer only has room for " << max_character_count;
                *error_message = error_message_stream.str();
            }
            return false;
        }
    }
    else
    {
        if (error_message)
        {
            ErrorCode   error_code;
            std::string error_string;
            error_code = ErrorHandler()->GetLastError(&error_string);
            if (error_code == ERROR_ENVVAR_NOT_FOUND)
            {
                // If you're seeing this error and the environment variable is spelled correctly
                // it _probably_ means that you are debugging and haven't set up the environment.
                //	* Right click the project name and choose "Properties"
                //	* In the tree view to the left select "Configuration Properties->Debugging"
                //	* In the "Environment" field make sure that you have this environment variable set like:
                //		* someKey=$(someKey)
                std::stringstream error_message_stream;
                error_message_stream << "The environment variable \"" << env_var << "\" doesn't exist";
                *error_message = error_message_stream.str();
            }
            else
            {
                std::stringstream error_message_stream;
                error_message_stream << "Windows failed to get the environment variable \"" << env_var
                                     << "\": " << error_string;
                *error_message = error_message_stream.str();
            }
        }
        return false;
    }
}

bool engine::Platform::SetEnvVar(const char* env_var, const std::string& env_val, std::string* error_message)
{
    //Assert(env_var, "Null VAriable name");
    return (::SetEnvironmentVariable(env_var, env_val.c_str()));
}

engine::FilePath engine::FileSystem::GetCurrentModulePath()
{
    char  module_path[kFilePathMaxSize];
    DWORD path_size = ::GetModuleFileName(nullptr, module_path, kFilePathMaxSize);

    if (path_size > 0)
    {
        module_path[path_size] = '\0';
        return FilePath{std::string(module_path)};
    }

    return FilePath{""};
}

bool engine::FileSystem::Copy(const char* const path_source,
                              const char* const path_target,
                              bool              overwrite,
                              bool              modify_time,
                              std::string*      error_message)
{
    if (::CopyFile(path_source, path_target, overwrite) != FALSE)
    {
        if (modify_time)
        {
            // Get the current system time
            FILETIME   file_time;
            SYSTEMTIME system_time;
            GetSystemTime(&system_time);
            if (SystemTimeToFileTime(&system_time, &file_time) == FALSE)
            {
                if (error_message)
                {
                    *error_message = ErrorHandler()->GetFormattedLastError();
                }

                return false;
            }

            // Set the current system time as the file's last write time
            HANDLE file_handle       = CreateFile(path_target,
                                            FILE_WRITE_ATTRIBUTES,
                                            FILE_SHARE_READ,
                                            nullptr,
                                            OPEN_EXISTING,
                                            FILE_ATTRIBUTE_NORMAL,
                                            nullptr);
            bool   were_there_errors = file_handle == INVALID_HANDLE_VALUE;
            if (!were_there_errors)
            {
                if (SetFileTime(file_handle, nullptr, nullptr, &file_time) == FALSE)
                {
                    were_there_errors = true;
                }
            }

            if (were_there_errors)
            {
                if (error_message)
                {
                    *error_message = ErrorHandler()->GetFormattedLastError();
                }

                if (file_handle != INVALID_HANDLE_VALUE)
                {
                    if (CloseHandle(file_handle) == FALSE)
                    {
                        were_there_errors = true;
                        if (error_message)
                        {
                            *error_message += "\n";
                            *error_message += ErrorHandler()->GetFormattedLastError();
                        }
                    }
                }

                return !were_there_errors;
            }
        }

        return true;
    }

    if (error_message)
    {
        *error_message = ErrorHandler()->GetFormattedLastError();
    }
    return false;
}

bool engine::FileSystem::CreateDirectoryIfNecessary(const std::string& directory_path, std::string* error_message)
{
    // If the path is to a file (likely), remove it so that only the directory remains
    std::string directory;

    size_t pos_slash = directory_path.find_last_of("\\/");
    if (pos_slash != std::string::npos)
    {
        directory = directory_path.substr(0, pos_slash);
    }
    else
    {
        directory = directory_path;
    }

    // Get the path in a form Windows likes (without any ".."s).
    // Windows requires a character buffer
    // to copy the path variable into.
    // An arbitrary value is chosen that "should" be "big enough":
    constexpr DWORD max_character_count = MAX_PATH;
    char            buffer[max_character_count];

    char** path_is_directory = nullptr;
    DWORD  character_count   = GetFullPathName(directory.c_str(), max_character_count, buffer, path_is_directory);
    if (character_count > 0)
    {
        if (character_count <= max_character_count)
        {
            // Create the directory
            int result = SHCreateDirectoryEx(nullptr, buffer, nullptr);

            if (result == ERROR_SUCCESS || result == ERROR_FILE_EXISTS || result == ERROR_ALREADY_EXISTS)
            {
                std::cout << "Created directory " << buffer << "\n";
                return true;
            }

            if (error_message)
            {
                *error_message = ErrorHandler()->GetFormattedErrorMessage(result);
            }
            return false;
        }

        // If you're seeing this error you will need to increase maxCharacterCount
        if (error_message)
        {
            std::stringstream errorMessage;
            errorMessage << "The full path of \"" << directory << "\" requires " << character_count
                         << " characters and the provided buffer only "
                            "has room for "
                         << max_character_count;
            *error_message = errorMessage.str();
        }
        return false;
    }

    if (error_message)
    {
        *error_message = ErrorHandler()->GetFormattedLastError();
    }

    return false;
}

bool engine::FileSystem::DoesFileExist(const std::string& file_path, std::string* error_message)
{
    // Try to get information about the file
    WIN32_FIND_DATA fileData;
    HANDLE          file = FindFirstFile(file_path.c_str(), &fileData);
    if (file != INVALID_HANDLE_VALUE)
    {
        if (FindClose(file) == FALSE)
        {
            std::stringstream errorMessage;
            errorMessage << "Windows failed to close the file handle to \"" << file_path << "\": " << GetLastError();
            MessageBox(nullptr, errorMessage.str().c_str(), "Error Closing File Handle", MB_OK | MB_ICONERROR);
        }
        return true;
    }

    if (error_message)
    {
        *error_message = ErrorHandler()->GetFormattedLastError();
    }
    return false;
}

bool engine::FileSystem::GetLastWriteTime(const std::string& file_path,
                                          uint64_t&          last_write_time,
                                          std::string*       error_message)
{
    // Get the last time that the file was written to
    srand(time(nullptr));
    ULARGE_INTEGER lastWriteTime;
    {
        WIN32_FIND_DATA fileData;
        {
            HANDLE file = FindFirstFile(file_path.c_str(), &fileData);
            if (file != INVALID_HANDLE_VALUE)
            {
                if (FindClose(file) == FALSE)
                {
                    if (error_message)
                    {
                        *error_message = ErrorHandler()->GetFormattedLastError();
                    }
                    return false;
                }
            }
            else
            {
                if (error_message)
                {
                    *error_message = ErrorHandler()->GetFormattedLastError();
                }
                return false;
            }
        }
        FILETIME fileTime      = fileData.ftLastWriteTime;
        lastWriteTime.HighPart = fileTime.dwHighDateTime;
        lastWriteTime.LowPart  = fileTime.dwLowDateTime;
    }
    last_write_time = static_cast<uint64_t>(lastWriteTime.QuadPart);
    return true;
}

bool engine::ProcessSystem::ExecuteCommand(const std::string& command,
                                           const std::string* optional_arguments,
                                           std::string*       error_message)
{
    bool were_there_errors = false;

    // Copy the const arguments into a non-const buffer
    constexpr DWORD buffer_size            = 512;
    char            arguments[buffer_size] = {0};
    if (optional_arguments)
    {
        size_t argument_length = strlen(optional_arguments->c_str());
        if (buffer_size > argument_length)
        {
            strcpy_s(arguments, buffer_size, optional_arguments->c_str());
        }
        else
        {
            if (error_message)
            {
                std::ostringstream errorMessage;
                errorMessage << "Couldn't copy the command (of length " << argument_length
                             << ") into a non-const buffer of size " << buffer_size;
                *error_message = errorMessage.str();
            }
            return false;
        }
    }

    // Start a new process
    STARTUPINFO startupInfo = {};
    startupInfo.cb          = sizeof(startupInfo);

    PROCESS_INFORMATION processInformation = {};
    if (CreateProcess(command.c_str(),
                      arguments,
                      nullptr,
                      nullptr,
                      FALSE,
                      0,
                      nullptr,
                      nullptr,
                      &startupInfo,
                      &processInformation) != FALSE)
    {
        // Wait for the process to finish
        if (WaitForSingleObject(processInformation.hProcess, INFINITE) != WAIT_FAILED)
        {
            // Get the exit code

            DWORD exit_code;
            if (GetExitCodeProcess(processInformation.hProcess, &exit_code) == FALSE)
            {
                were_there_errors = true;
                if (error_message)
                {
                    std::stringstream errorMessage;
                    errorMessage << "Windows failed to get the exit code "
                                    "of the process \""
                                 << command << "\": " << GetLastError();
                    *error_message = errorMessage.str();
                }
            }
        }
        else
        {
            were_there_errors = true;
            if (error_message)
            {
                std::stringstream errorMessage;
                errorMessage << "Windows failed to wait for the process \"" << command
                             << "\" to finish: " << GetLastError();
                *error_message = errorMessage.str();
            }
        }
        // Close the process handles
        if (CloseHandle(processInformation.hProcess) == FALSE)
        {
            std::stringstream errorMessage;
            errorMessage << "Windows failed to close the handle to the process \"" << command
                         << "\": " << GetLastError();
            MessageBox(NULL, errorMessage.str().c_str(), "Error Closing Process Handle", MB_OK | MB_ICONERROR);
        }
        if (CloseHandle(processInformation.hThread) == FALSE)
        {
            std::stringstream errorMessage;
            errorMessage << "Windows failed to close the handle to the process \"" << command
                         << "\" thread: " << GetLastError();
            MessageBox(NULL, errorMessage.str().c_str(), "Error Closing Process Thread Handle", MB_OK | MB_ICONERROR);
        }

        return !were_there_errors;
    }
    else
    {
        if (error_message)
        {
            std::stringstream errorMessage;
            errorMessage << "Windows failed to start the process \"" << command << "\": " << GetLastError();
            *error_message = errorMessage.str();
        }
        return false;
    }
}

bool engine::ProcessSystem::ExecuteCommand(const std::string& command, std::string* error_message)
{
    return ExecuteCommand(command, nullptr, error_message);
}

std::string engine::ErrorSystem::GetFormattedErrorMessage(engine::ErrorCode error_code)
{
    DWORD       win_error_code = static_cast<DWORD>(error_code);
    std::string error_message;

    constexpr DWORD formatting_options =
        // Get the error message from Windows
        FORMAT_MESSAGE_FROM_SYSTEM
        // The space for the error message should be allocated by Windows
        | FORMAT_MESSAGE_ALLOCATE_BUFFER
        // Any potentially deferred inserts should be ignored
        // (i.e. the error message should be in its final form)
        | FORMAT_MESSAGE_IGNORE_INSERTS;
    const void*     message_is_from_windows             = nullptr;
    constexpr DWORD use_the_default_language            = 0;
    char*           message_buffer                      = nullptr;
    constexpr DWORD minimum_character_count_to_allocate = 1;
    va_list*        inserts_are_ignored                 = nullptr;
    const DWORD     stored_character_count              = FormatMessage(formatting_options,
                                                       message_is_from_windows,
                                                       win_error_code,
                                                       use_the_default_language,
                                                       reinterpret_cast<LPSTR>(&message_buffer),
                                                       minimum_character_count_to_allocate,
                                                       inserts_are_ignored);
    if (stored_character_count != 0)
    {
        error_message = message_buffer;
    }
    else
    {
        // If there's an error GetLastError() can be called again,
        // but that is too complicated for this program :)
        error_message = "Unknown Windows Error";
    }
    // Try to free the memory regardless of whether formatting worked or not,
    // and ignore any error messages
    LocalFree(message_buffer);

    return error_message;
}

engine::ErrorCode engine::ErrorSystem::GetLastError(std::string* error_message)
{
    // Windows stores the error as a code
    const DWORD error_code = ::GetLastError();
    if (error_message)
    {
        *error_message = GetFormattedErrorMessage(static_cast<ErrorCode>(error_code));
    }
    return error_code;
}

//void WindowsUtil::Print(std::string i_str,
//	const char * i_optionalFileName)
//{
//	std::stringstream message;
//	message << i_str;
//	if (i_optionalFileName != nullptr)
//		message << i_optionalFileName;
//#if _DEBUG
//	MessageBox(nullptr, message.str().c_str(), nullptr, MB_OK);
//#endif
//	std::cerr << message.str().c_str() << "\n";
//}
//
//bool WindowsUtil::Assert(bool evaluatedBool,
//	std::string message)
//{
//	if (!evaluatedBool)
//	{
//		Print(message);
//		return false;
//	}
//	assert(evaluatedBool);
//	return true;
//}

//void WindowsUtil::displayToOutPutWindow(std::string iString)
//{
//    OutputDebugString(iString.c_str());
//}
