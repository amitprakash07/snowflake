#ifndef ENGINE_PLATFORM_PLATFORM_OBJECTS_H_
#define ENGINE_PLATFORM_PLATFORM_OBJECTS_H_

#include <string>
#include <fstream>

#include "common/string_util.h"

namespace engine
{
    enum class FileOpenMode
    {
        Read,
        Write,
        Append
    };

    extern const uint16_t kFilePathMaxSize;

    class FilePath
    {
    public:
        FilePath(const std::string& file_abs_path);
        FilePath(const std::string& dir, const std::string& file_name);
        [[nodiscard]] std::string_view ParentDirectory() const;
        const char*                    AsCharArray() const
        {
            return file_abs_path_.c_str();
        }

    private:
        void        Init(const std::string& abs_path);
        std::string file_abs_path_;
        std::string file_parent_directory_;
    };

    class FileMetaData
    {
    public:
        FileMetaData() = delete;
        FileMetaData(const FilePath& file_path);

        FileMetaData(FileMetaData&& other) noexcept
        {
            file_name_                   = std::move(other.file_name_);
            file_name_without_extension_ = std::move(other.file_name_without_extension_);
            file_extension_              = std::move(other.file_extension_);
        }

        FileMetaData& operator=(FileMetaData&& other) noexcept
        {
            file_name_                   = std::move(other.file_name_);
            file_name_without_extension_ = std::move(other.file_name_without_extension_);
            file_extension_              = std::move(other.file_extension_);
            return *this;
        }

        inline std::string_view GetFileName() const
        {
            return file_name_;
        }

        inline std::string_view GetFileNameWithoutExtension() const
        {
            return file_name_without_extension_;
        }

        inline std::string_view GetExtension() const
        {
            return file_extension_;
        }

    private:
        std::string file_name_;
        std::string file_name_without_extension_;
        std::string file_extension_;
    };

    class File
    {
    public:
        File() = delete;
        File(FilePath path, FileOpenMode mode = FileOpenMode::Read)
            : file_path_(std::move(path))
            , file_mode_(mode)
            , file_meta_data_(file_path_)
        {
        }
        File(const File& other) = delete;
        File(File&& other) noexcept
            : file_path_(std::move(other.file_path_))
            , file_stream_(std::move(other.file_stream_))
            , file_meta_data_(std::move(other.file_meta_data_))
        {
            file_mode_ = other.file_mode_;
        }

        File& operator=(const File& other) = delete;

        File& operator=(File&& other) noexcept
        {
            file_path_      = other.file_path_;
            file_stream_    = std::move(other.file_stream_);
            file_mode_      = other.file_mode_;
            file_meta_data_ = std::move(other.file_meta_data_);
            return *this;
        }

        const FileMetaData& GetMetaData()
        {
            return file_meta_data_;
        }

        bool DoesExist() const
        {
            std::fstream temp;
            temp.open(file_path_.AsCharArray(), std::ifstream::in);

            if (temp.is_open())
            {
                return true;
            }

            return false;
        }

        bool IsOpen() const
        {
            return file_stream_.is_open();
        }

        bool Open()
        {
            std::ios_base::openmode open_mode = std::fstream::in;

            switch (file_mode_)
            {
            case FileOpenMode::Read:
                open_mode = std::fstream::in;
                break;
            case FileOpenMode::Write:
                open_mode = std::fstream::out;
                break;
            case FileOpenMode::Append:
                open_mode = std::fstream::app;
                break;
            }

            if (!IsOpen())
            {
                file_stream_.open(file_path_.AsCharArray(), open_mode);
            }

            return IsOpen();
        }

        ~File()
        {
            if (IsOpen())
            {
                file_stream_.close();
            }
        }

        std::filebuf* GetRawBuffer() const
        {
            return file_stream_.rdbuf();
        }

        const FilePath& GetPath() const
        {
            return file_path_;
        }

    private:
        FilePath     file_path_;
        std::fstream file_stream_;
        FileOpenMode file_mode_;
        FileMetaData file_meta_data_;
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
    using WndClassId    = unsigned int;

    // TO DO: Incompatible signature
    typedef ResultPtr(__stdcall* WndProc)(WindowHandle, WndMessage, Param, Param);

    struct WindowAttributes
    {
        WindowAttributes();
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
        std::string  window_caption;
        int          show_state;
    };

    class Window
    {
    public:
        Window() = default;
        Window(const WindowAttributes& wnd_meta_data)
            : wnd_attributes_(wnd_meta_data)
        {
        }

        bool Initialize();
        bool Shutdown();

        const WindowAttributes& Attributes() const
        {
            return wnd_attributes_;
        }

        void SetToFullResolution();

    private:
        bool             RegisterWindowClass();
        WindowAttributes wnd_attributes_;
    };

}  // namespace engine

#endif