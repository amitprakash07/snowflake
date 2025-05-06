#include <Windows.h>

#include "gpu/gpu_factory.h"
#include "gpu/gpu_device.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    MessageBox(nullptr, "Testing the Win Main", "Testing", MB_OK);

    {
        engine::GpuFactory gpu;

        if (gpu.Initialize())
        {
            engine::GpuDevice* device = gpu.GetDevice();
            device->UnitTest();
        }
    }
}
