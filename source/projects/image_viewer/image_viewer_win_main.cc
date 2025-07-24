#include <iostream>
#include <Windows.h>

#include "image/image.h"
#include "platform/platform_objects.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    engine::FilePath image_file(std::string("C:\\Users\\amprakash\\Downloads\\screnshot.ppm"));

    engine::Image* image_obj =  engine::Image::CreateImage(image_file);
    if (!image_obj->Load())
    {
        return -1;
    }

    engine::Window image_viewer_window;
    if(image_viewer_window.Initialize())
    {
        std::cout << "Sweet";
    }

    image_viewer_window.Show();
}
