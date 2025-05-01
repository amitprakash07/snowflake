#ifndef ENGINE_GPU_GPU_DEVICE_H_
#define ENGINE_GPU_GPU_DEVICE_H_

#include <vector>
#include <map>

#include <d3d12.h>

#include "gpu_device_resource.h"

namespace engine
{

    class GpuDevice
    {
    public:
        GpuDevice(ID3D12Device10* d3d12_device);
        GpuDevice() = delete;
        ~GpuDevice();

        template <class DeviceResourcePtrType, class DeviceResourceDesc>
        DeviceResourcePtrType* Create(const DeviceResourceDesc& desc)
        {
            return nullptr;
        }

#define DECLARE_SPECIALIZED_CREATE(resource_type, resource_ptr_type, resource_desc) \
    template <>                                                                     \
    GpuDeviceResource<resource_ptr_type>* Create(const GpuDeviceResourceDesc<resource_desc>& desc)

        DECLARE_SPECIALIZED_CREATE(CmdQueue, ID3D12CommandQueue, D3D12_COMMAND_QUEUE_DESC);
        DECLARE_SPECIALIZED_CREATE(ComputePipeline, ID3D12PipelineState, D3D12_COMPUTE_PIPELINE_STATE_DESC);
        DECLARE_SPECIALIZED_CREATE(GraphicsPipeline, ID3D12PipelineState, D3D12_GRAPHICS_PIPELINE_STATE_DESC);
        DECLARE_SPECIALIZED_CREATE(DescriptorHeap, ID3D12DescriptorHeap, D3D12_DESCRIPTOR_HEAP_DESC);
        DECLARE_SPECIALIZED_CREATE(Heap, ID3D12Heap, D3D12_HEAP_DESC);
        DECLARE_SPECIALIZED_CREATE(QueryHeap, ID3D12QueryHeap, D3D12_QUERY_HEAP_DESC);

        DECLARE_SPECIALIZED_CREATE(CmdList, ID3D12CommandList, GpuCmdListDesc);
        DECLARE_SPECIALIZED_CREATE(CommittedResource, ID3D12Resource, GpuCommittedResDesc);
        DECLARE_SPECIALIZED_CREATE(PlacedResource, ID3D12Resource, GpuPlacedResDesc);
        DECLARE_SPECIALIZED_CREATE(Fence, ID3D12Fence, GpuFenceDesc);
        DECLARE_SPECIALIZED_CREATE(RootSignature, ID3D12RootSignature, GpuRootSignatureDesc);

        GpuDevice(const GpuDevice&)  = delete;
        GpuDevice(const GpuDevice&&) = delete;

        GpuDevice& operator=(const GpuDevice&)  = delete;
        GpuDevice& operator=(const GpuDevice&&) = delete;

        static void UnitTest()
        {
            GpuDevice                         device(nullptr);
            D3D12_COMPUTE_PIPELINE_STATE_DESC desc = {};
            GpuDeviceResource                 res  = device.Create<ID3D12PipelineState>(&desc);
        }

    private:
        ID3D12Device10*              d3d12_device_;
        std::map<GpuDeviceResourceType, std::vector<void*>> device_resources_map_;
        std::map<D3D12_COMMAND_LIST_TYPE, ID3D12CommandAllocator*> cmd_allocators_map_by_type_;
    };
}  // namespace engine

#endif