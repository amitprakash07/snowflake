#ifndef ENGINE_PLATFORM_PLATFORM_OBJECTS_H_
#define ENGINE_PLATFORM_PLATFORM_OBJECTS_H_

#include <string>
#include <fstream>

namespace engine
{
    enum class FileOpenMode
    {
        Read,
        Write,
        Append
    };

    class FilePath
    {
    public:
        FilePath(const std::string& file_abs_path);
        FilePath(const std::string& dir, const std::string& file_name);
        const char* AsCharArray() const
        {
            return file_abs_path_.c_str();
        }

    private:
        std::string file_abs_path_;
    };

    class File
    {
    public:
        File() = delete;
        File(FilePath path, FileOpenMode mode = FileOpenMode::Read)
            : file_path_(std::move(path))
            , file_mode_(mode)
        {
        }

        File(const File& other)            = delete;
        File& operator=(const File& other) = delete;

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

    private:
        FilePath     file_path_;
        std::fstream file_stream_;
        FileOpenMode file_mode_;
    };

}  // namespace engine

#endif