
#include "platform/platform_objects.h"
#include "common/string_util.h"

engine::FilePath::FilePath(const std::string& file_abs_path)
{
    file_abs_path_ = engine_string_util::ToWinFilePath(file_abs_path);
}

engine::FilePath::FilePath(const std::string& dir, const std::string& file_name)
{
    file_abs_path_ = dir + "\\" + file_name;
    file_abs_path_ = engine_string_util::ToWinFilePath(file_abs_path_);
}
