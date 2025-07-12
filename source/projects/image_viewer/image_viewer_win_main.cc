#include <Windows.h>

#include "image/image.h"
#include "platform/platform.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    engine::FilePath image_file(std::string("C:\\Users\\amprakash\\Downloads\\screnshot.ppm"));

    engine::Image* image_obj =  engine::Image::CreateImage(image_file);
    if (!image_obj->Load())
    {
        return -1;
    }

    engine::EngineStartupInfo engine_startup_info;
    engine_startup_info.win_display_state = 
    engine::Platform::Instance()->Initialize()
}
