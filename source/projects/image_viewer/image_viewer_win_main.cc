#include <Windows.h>

#include "image/image.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    engine::FilePath image_file(std::string("C:\\Users\\amprakash\\Downloads\\screnshot.ppm"));

    engine::Image* image_obj =  engine::Image::CreateImage(image_file);
    if (!image_obj->Load())
    {
        return -1;
    }

}
