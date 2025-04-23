#ifndef ENGINE_GPU_GPU_CMD_LIST_H_
#define ENGINE_GPU_GPU_CMD_LIST_H_

#include <d3d12.h>

namespace engine
{
    struct GpuCmdListDesc
    {
        GpuCmdListDesc()
        {
            Node = 0;
            Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
        }

        uint8_t                 Node;
        D3D12_COMMAND_LIST_TYPE Type;
    };

    class GpuCommandList
    {
    public:
        GpuCommandList(ID3D12CommandList* cmd_list);
    };
}  // namespace engine

#endif
