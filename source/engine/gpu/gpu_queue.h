#ifndef ENGINE_GPU_GPU_QUEUE_H_
#define ENGINE_GPU_GPU_QUEUE_H_

#include <d3d12.h>

namespace engine
{

    struct GpuQueueDesc : D3D12_COMMAND_QUEUE_DESC
    {
        GpuQueueDesc()
        {
            Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
            Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
            Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
            NodeMask = 0;
        }
    };

    class GpuQueue
    {
    public:
        GpuQueue(ID3D12CommandQueue* cmd_queue);
    };
}

#endif
