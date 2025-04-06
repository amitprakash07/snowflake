#ifndef ENGINE_PLATFORM_PLATFORM_H_
#define ENGINE_PLATFORM_PLATFORM_H_

#include <map>
#include <string>

namespace engine
{
    class FileSystem;
    class ProcessSystem;
    class ErrorSystem;
    class LoggingSystem;
    class WindowingSystem;
    class IPlatformHandler;

    using ProgramInstance = void*;

    struct EngineStartupInfo
    {
        ProgramInstance instance;
        int             win_display_state;
    };

    enum class PlatformHandlerType : int8_t
    {
        UnRegistered = -1,
        File         = 0,
        Process,
        Error,
        Logging,
        Windowing,
        Count
    };

    class Platform
    {
    public:
        virtual ~Platform() = default;
        static [[nodiscard]] Platform* Instance();

        IPlatformHandler* GetHandler(PlatformHandlerType handler_type) const
        {
            return platform_handlers_[static_cast<uint8_t>(handler_type)];
        }

        bool IsHandlerInitialized(PlatformHandlerType handler_type) const
        {
            return GetHandler(handler_type) != nullptr;
        }

        // Environment variable
        bool GetEnvVar(const char* env_var, std::string& env_val, std::string* error_message = nullptr);

        bool SetEnvVar(const char* env_var, const std::string& env_val, std::string* error_message = nullptr);

    protected:
        static [[nodiscard]] bool Initialize(const EngineStartupInfo& engine_startup_info);
        static [[nodiscard]] bool ShutDown();

    private:
        Platform()
            : platform_handlers_{}
            , initialized_(false)
        {
        }

        IPlatformHandler* platform_handlers_[static_cast<uint8_t>(PlatformHandlerType::Count)];
        bool              initialized_;
        static Platform*  platform_;
    };

    inline ErrorSystem* ErrorHandler()
    {
        return reinterpret_cast<ErrorSystem*>(Platform::Instance()->GetHandler(PlatformHandlerType::Error));
    }

    inline FileSystem* FileHandler()
    {
        return reinterpret_cast<FileSystem*>(Platform::Instance()->GetHandler(PlatformHandlerType::File));
    }

    inline ProcessSystem* ProcessHandler()
    {
        return reinterpret_cast<ProcessSystem*>(Platform::Instance()->GetHandler(PlatformHandlerType::Process));
    }

    inline LoggingSystem* LoggingHandler()
    {
        return reinterpret_cast<LoggingSystem*>(Platform::Instance()->GetHandler(PlatformHandlerType::Logging));
    }

    inline WindowingSystem* WindowHandler()
    {
        return reinterpret_cast<WindowingSystem*>(Platform::Instance()->GetHandler(PlatformHandlerType::Windowing));
    }

    class IPlatformHandler
    {
    public:
        IPlatformHandler()                 = delete;
        virtual bool StartUp()             = 0;
        virtual bool ShutDown()            = 0;
        virtual bool IsInitialized() const = 0;
        virtual ~IPlatformHandler()        = default;

    protected:
        IPlatformHandler(PlatformHandlerType handler_type)
        {
            handler_type_ = handler_type;
        }

        bool Registered() const
        {
            return handler_type_ != PlatformHandlerType::UnRegistered;
        }

        PlatformHandlerType handler_type_;
    };

    class FileSystem : public IPlatformHandler
    {
    public:
        friend class Platform;
        ~FileSystem() override = default;

        bool Copy(const char*  path_source,
                  const char*  path_target,
                  bool         overwrite     = false,
                  bool         modify_time   = false,
                  std::string* error_message = nullptr);

        bool CreateDirectoryIfNecessary(const std::string& directory_path, std::string* error_message = nullptr);

        bool DoesFileExist(const std::string& file_path, std::string* error_message = nullptr);

        bool GetLastWriteTime(const std::string& file_path,
                              uint64_t&          last_write_time,
                              std::string*       error_message = nullptr);

        bool StartUp() override
        {
            return true;
        }

        bool ShutDown() override
        {
            return true;
        }

        bool IsInitialized() const override
        {
            return true;
        }

    private:
        FileSystem()
            : IPlatformHandler(PlatformHandlerType::File)
        {
        }
    };

    class ProcessSystem : public IPlatformHandler
    {
    public:
        friend class Platform;
        ~ProcessSystem() override = default;

        bool ExecuteCommand(const std::string& command, std::string* error_message = nullptr);

        bool ExecuteCommand(const std::string& command,
                            const std::string* optional_arguments = nullptr,
                            std::string*       error_message      = nullptr);

        bool StartUp() override
        {
            return true;
        }

        bool ShutDown() override
        {
            return true;
        }

        bool IsInitialized() const override
        {
            return true;
        }

    private:
        ProcessSystem()
            : IPlatformHandler(PlatformHandlerType::Process)
        {
        }
    };

    typedef unsigned long long ErrorCode;
    class ErrorSystem : public IPlatformHandler
    {
        friend class Platform;

    public:
        ErrorCode   GetLastError(std::string* error_message = nullptr);
        std::string GetFormattedErrorMessage(ErrorCode error_code);
        std::string GetFormattedLastError()
        {
            return GetFormattedErrorMessage(GetLastError());
        }

        bool StartUp() override
        {
            return true;
        }

        bool ShutDown() override
        {
            return true;
        }

        bool IsInitialized() const override
        {
            return true;
        }

    private:
        ErrorSystem()
            : IPlatformHandler(PlatformHandlerType::Error)
        {
        }
    };

    enum class LoggingMessageType
    {

    };

    class LoggingSystem : public IPlatformHandler
    {
        friend class Platform;

    public:
        void Log(LoggingMessageType type, const char* formatted_message, ...);

        bool StartUp() override
        {
            return true;
        }

        bool ShutDown() override
        {
            return true;
        }

        bool IsInitialized() const override
        {
            return true;
        }

    private:
        LoggingSystem()
            : IPlatformHandler(PlatformHandlerType::Logging)
        {
        }
    };

    using Icon          = void*;
    using Cursor        = Icon;
    using Brush         = void*;
    using WindowStyle   = void*;
    using ModuleHandle  = void*;
    using WindowHandle  = void*;
    using ProcessHandle = void*;
    using Param         = void*;
    using ResultPtr     = void*;
    using Menu          = void*;
    using WndMessage    = unsigned int;

    // TO DO: Incompatible signature
    typedef ResultPtr(__stdcall* WndProc)(WindowHandle, WndMessage, Param, Param);

    struct Window
    {
        Window();
        void         SetToFullResolution();
        WindowHandle parent_window;
        ModuleHandle module_handle;
        WndProc      wnd_proc;
        Icon         icon;
        Icon         small_icon;
        Cursor       cursor;
        Brush        background;
        int          width;
        int          height;
        std::string  class_name;
        std::string  menu_name;
        std::string  title_caption;
        int          show_state;
    };

    class WindowingSystem : public IPlatformHandler
    {
        friend class Platform;

    public:
        WindowHandle ConstructWindow(const Window* window_info = nullptr);

        WindowHandle GetMainWindowHandle() const
        {
            return main_window_handle_;
        }

        virtual ~WindowingSystem();

    private:
        //static ResultPtr CALLBACK DefaultWndProc(Window* window, WndMessage message, Param w_param, Param l_param);

        bool DeleteWindow(WindowHandle wnd_handle, bool delete_main_window = false);

        WindowingSystem(int win_main_display_state);

        bool StartUp() override
        {
            return true;
        }

        bool ShutDown() override
        {
            return true;
        }

        bool IsInitialized() const override
        {
            return true;
        }

        std::map<WindowHandle, const Window*> all_window_map_;
        Window*                               main_window_;
        WindowHandle                          main_window_handle_;
        int                                   win_main_display_state_;
    };

}  // namespace engine

#endif
