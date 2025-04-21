#ifndef ENGINE_GPU_GPU_DEVICE_H_
#define ENGINE_GPU_GPU_DEVICE_H_

#include <d3d12.h>

namespace engine
{
    class GpuQueue;
    class GpuCmdList;
    class GpuResource;

    enum GpuQueueType

    class GpuDevice
    {
    public:
        GpuDevice(ID3D12Device10* d3d12_device);
        GpuDevice() = delete;

        GpuQueue* GetQueue()
    };
}

#endif