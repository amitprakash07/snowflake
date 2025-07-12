#include "opencv2/opencv.hpp"

#include "image.h"

engine::Image* engine::Image::CreateImage(const FilePath& image_file_path)
{
    Image* ret_image = new PpmImage(image_file_path);
    return ret_image;
}

bool engine::Image::LoadDefault()
{
    cv::Mat image_data = cv::imread(GetPath().AsCharArray());
    return true;
}
