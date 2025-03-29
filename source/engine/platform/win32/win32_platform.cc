

#include <iostream>
#include <ShlObj.h>
#include <sstream>
#include <ctime>

#include "win32_platform.h"

bool engine::Win32Platform::GetEnvVar(const char* const env_var, std::string& env_val, std::string* error_message)
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
            DWORD       error_code;
            std::string error_string = GetLastWindowsError(&error_code);
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

bool engine::Win32Platform::SetEnvVar(const char* env_var, const std::string& env_val, std::string* error_message)
{
    //Assert(env_var, "Null VAriable name");
    return (::SetEnvironmentVariable(env_var, env_val.c_str()));
}

bool engine::Win32Platform::CopyFile(const char* const path_source,
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
                    *error_message = GetLastWindowsError();
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
                    *error_message = GetLastWindowsError();
                }

                if (file_handle != INVALID_HANDLE_VALUE)
                {
                    if (CloseHandle(file_handle) == FALSE)
                    {
                        were_there_errors = true;
                        if (error_message)
                        {
                            *error_message += "\n";
                            *error_message += GetLastWindowsError();
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
        *error_message = GetLastWindowsError();
    }
    return false;
}

bool engine::Win32Platform::CreateDirectoryIfNecessary(const std::string& directory_path, std::string* error_message)
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
                *error_message = GetFormattedWindowsError(result);
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
        *error_message = GetLastWindowsError();
    }

    return false;
}

bool engine::Win32Platform::DoesFileExist(const std::string& file_path, std::string* error_message)
{
    // Try to get information about the file
    WIN32_FIND_DATA fileData;
    HANDLE          file = FindFirstFile(file_path.c_str(), &fileData);
    if (file != INVALID_HANDLE_VALUE)
    {
        if (FindClose(file) == FALSE)
        {
            std::stringstream errorMessage;
            errorMessage << "Windows failed to close the file handle to \"" << file_path
                         << "\": " << GetLastWindowsError();
            MessageBox(nullptr, errorMessage.str().c_str(), "Error Closing File Handle", MB_OK | MB_ICONERROR);
        }
        return true;
    }

    if (error_message)
    {
        *error_message = GetLastWindowsError();
    }
    return false;
}

bool engine::Win32Platform::GetLastWriteTime(const std::string& file_path,
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
                        *error_message = GetLastWindowsError();
                    }
                    return false;
                }
            }
            else
            {
                if (error_message)
                {
                    *error_message = GetLastWindowsError();
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

bool engine::Win32Platform::ExecuteCommand(const std::string& command,
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
                                 << command << "\": " << GetLastWindowsError();
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
                             << "\" to finish: " << GetLastWindowsError();
                *error_message = errorMessage.str();
            }
        }
        // Close the process handles
        if (CloseHandle(processInformation.hProcess) == FALSE)
        {
            std::stringstream errorMessage;
            errorMessage << "Windows failed to close the handle to the process \"" << command
                         << "\": " << GetLastWindowsError();
            MessageBox(NULL, errorMessage.str().c_str(), "Error Closing Process Handle", MB_OK | MB_ICONERROR);
        }
        if (CloseHandle(processInformation.hThread) == FALSE)
        {
            std::stringstream errorMessage;
            errorMessage << "Windows failed to close the handle to the process \"" << command
                         << "\" thread: " << GetLastWindowsError();
            MessageBox(NULL, errorMessage.str().c_str(), "Error Closing Process Thread Handle", MB_OK | MB_ICONERROR);
        }

        return !were_there_errors;
    }
    else
    {
        if (error_message)
        {
            std::stringstream errorMessage;
            errorMessage << "Windows failed to start the process \"" << command << "\": " << GetLastWindowsError();
            *error_message = errorMessage.str();
        }
        return false;
    }
}

bool engine::Win32Platform::ExecuteCommand(const std::string& command, std::string* error_message)
{
    return ExecuteCommand(command, nullptr, error_message);
}

std::string engine::Win32Platform::GetFormattedWindowsError(DWORD error_code)
{
    std::string error_message;
    {
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
                                                           error_code,
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
    }
    return error_message;
}

std::string engine::Win32Platform::GetLastWindowsError(DWORD* error_code)
{
    // Windows stores the error as a code
    const DWORD errorCode = GetLastError();
    if (error_code)
    {
        *error_code = errorCode;
    }
    return GetFormattedWindowsError(errorCode);
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
