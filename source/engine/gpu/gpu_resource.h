#ifndef ENGINE_GPU_GPU_RESOURCE_H_
#define ENGINE_GPU_GPU_RESOURCE_H_

#include <d3d12.h>

namespace engine
{
    struct GpuResourceDesc : D3D12_RESOURCE_DESC1
    {
    };

    class GpuResource
    {
        GpuResource(ID3D12Resource* d3d12_device);
    };
}  // namespace engine
#endif
