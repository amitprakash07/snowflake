
#include "opencv2/opencv.hpp"

#include "image.h"

bool engine::PpmImage::Load()
{
    cv::Mat image_data = cv::imread(GetPath().AsCharArray());
    return true;
}
