
#include "platform/platform_objects.h"
#include "common/string_util.h"

engine::FilePath::FilePath(const std::string& file_abs_path)
{
    Init(file_abs_path);
}

engine::FilePath::FilePath(const std::string& dir, const std::string& file_name)
{
    Init(dir + "\\" + file_name);
}

std::string_view engine::FilePath::ParentDirectory() const
{
    return file_parent_directory_;
}

void engine::FilePath::Init(const std::string& abs_path)
{
    if (!abs_path.empty())
    {
        file_abs_path_         = engine_string_util::ToWinFilePath(abs_path);
        file_parent_directory_ = engine_string_util::GetWinDirFromAbsPath(abs_path);
    }
}

engine::FileMetaData::FileMetaData(const FilePath& file_path)
{
    std::string temp_path_string = file_path.AsCharArray();

    if (!temp_path_string.empty())
    {
        size_t pos = temp_path_string.find_last_of('.');
        file_extension_ =
            std::string(temp_path_string.cbegin() + static_cast<size_t>(pos + 1), temp_path_string.cend());
        size_t last_separator        = temp_path_string.find_last_of('\\');
        file_name_without_extension_ = std::string(temp_path_string.cbegin() + static_cast<size_t>(last_separator + 1),
                                                   temp_path_string.cbegin() + static_cast<size_t>(pos));
        file_name_ =
            std::string(temp_path_string.cbegin() + static_cast<size_t>(last_separator + 1), temp_path_string.cend());
    }
}
