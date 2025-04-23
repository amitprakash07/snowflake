#ifndef ENGINE_GPU_GPU_DEVICE_H_
#define ENGINE_GPU_GPU_DEVICE_H_

#include <vector>

#include <d3d12.h>
#include <map>

#include "gpu_queue.h"
#include "gpu_cmd_list.h"
#include "gpu_pipeline.h"
#include "gpu_resource.h"

namespace engine
{
    class GpuDevice
    {
    public:
        GpuDevice(ID3D12Device10* d3d12_device);
        GpuDevice() = delete;
        ~GpuDevice();

        GpuQueue*       CreateQueue(const GpuQueueDesc* desc = nullptr);
        GpuCommandList* CreateCmdList(const GpuCmdListDesc* desc = nullptr);
        GpuResource*    CreateResource(const GpuResourceDesc* desc = nullptr);
        GpuPipeline*    CreatePipeline(const GpuPipelineDesc* desc);

        GpuDevice(const GpuDevice&)  = delete;
        GpuDevice(const GpuDevice&&) = delete;

        GpuDevice& operator=(const GpuDevice&)  = delete;
        GpuDevice& operator=(const GpuDevice&&) = delete;

    private:
        ID3D12Device10*                                            d3d12_device_;
        std::vector<GpuQueue*>                                     gpu_queues_;
        std::vector<GpuCommandList*>                               gpu_cmd_lists_;
        std::vector<GpuResource*>                                  gpu_resources_;
        std::vector<GpuPipeline*>                                  gpu_pipelines_;
        std::map<D3D12_COMMAND_LIST_TYPE, ID3D12CommandAllocator*> cmd_allocators_map_by_type_;
    };
}  // namespace engine

#endif