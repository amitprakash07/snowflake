#ifndef ENGINE_GPU_GPU_DEVICE_RESOURCE_H_
#define ENGINE_GPU_GPU_DEVICE_RESOURCE_H_

#include <cstdint>
#include <d3d12.h>

namespace engine
{
    enum GpuDeviceResourceType
    {
        Unknown,
        CmdQueue,
        CmdList,
        RootSignature,
        CommittedResource,
        PlacedResource,
        ComputePipeline,
        GraphicsPipeline,
        DescriptorHeap,
        Fence,
        Heap,
        QueryHeap,
        Test
    };

    class GpuNoDesc
    {
    };

    struct GpuFenceDesc
    {
        UINT64            InitialValue;
        D3D12_FENCE_FLAGS Flags;
    };

    struct GpuPlacedResDesc : D3D12_RESOURCE_DESC
    {
        ID3D12Heap*              pHeap;
        UINT64                   HeapOffset;
        D3D12_RESOURCE_STATES    InitialState;
        const D3D12_CLEAR_VALUE* pOptimizedClearValue;
    };

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

    struct GpuCommittedResDesc : D3D12_RESOURCE_DESC
    {
        const D3D12_HEAP_PROPERTIES* pHeapProperties;
        D3D12_HEAP_FLAGS             HeapFlags;
        D3D12_RESOURCE_STATES        InitialResourceState;
        const D3D12_CLEAR_VALUE*     pOptimizedClearValue;
    };

    struct GpuRootSignatureDesc : D3D12_ROOT_SIGNATURE_DESC
    {
        UINT        nodeMask;
        const void* pBlobWithRootSignature;
        SIZE_T      blobLengthInBytes;
    };

    template <typename DeviceResourceDesc>
    DeviceResourceDesc GetDeviceResourceDefaultDesc()
    {
        return DeviceResourceDesc{};
    }

    template <>
    D3D12_COMMAND_QUEUE_DESC GetDeviceResourceDefaultDesc<D3D12_COMMAND_QUEUE_DESC>();

    template <class DeviceResourceDesc>
    class GpuDeviceResourceDesc : public DeviceResourceDesc
    {
    public:
        GpuDeviceResourceDesc()
        {
            *this = GetDeviceResourceDefaultDesc<DeviceResourceDesc>();
        }

        GpuDeviceResourceDesc(const DeviceResourceDesc& desc)
        {
            memcpy(this, &desc, sizeof(DeviceResourceDesc));
        }
    };

    template <>
    class GpuDeviceResourceDesc<GpuNoDesc>
    {
    };

    template <class DeviceResourcePtrType>
    class GpuDeviceResource
    {
    public:
        GpuDeviceResource(DeviceResourcePtrType* ptr)
            : device_res_ptr_(ptr)
        {
        }

        DeviceResourcePtrType* GetPtr() const
        {
            return device_res_ptr_;
        }

    private:
        DeviceResourcePtrType* device_res_ptr_;
    };

    template <GpuDeviceResourceType resource_type,
              class DeviceResourcePtrType,
              class DeviceResourceDesc = GpuDeviceResourceDesc<GpuNoDesc>>
    class GpuDeviceResContainer : public GpuDeviceResource<DeviceResourcePtrType>
    {
    public:
        GpuDeviceResContainer(DeviceResourcePtrType* device_res_ptr, const DeviceResourceDesc& device_res_desc)
            : GpuDeviceResource<DeviceResourcePtrType>(device_res_ptr)
            , device_res_desc_(device_res_desc)
            , resource_type_(resource_type)
        {
        }

        GpuDeviceResContainer() = delete;

        GpuDeviceResourceType Type() const
        {
            return resource_type_;
        }

    private:
        GpuDeviceResourceDesc<DeviceResourceDesc> device_res_desc_;
        GpuDeviceResourceType                     resource_type_;
    };

#define INSTANTIATE_DEVICE_RESOURCE(resource_type, resource_ptr_type, resource_desc)                    \
    template <>                                                                                         \
    class GpuDeviceResContainer<resource_type, resource_ptr_type, GpuDeviceResourceDesc<resource_desc>> \
    {                                                                                                   \
    };

    INSTANTIATE_DEVICE_RESOURCE(CmdQueue, ID3D12CommandQueue, D3D12_COMMAND_QUEUE_DESC);
    INSTANTIATE_DEVICE_RESOURCE(ComputePipeline, ID3D12PipelineState, D3D12_COMPUTE_PIPELINE_STATE_DESC);
    INSTANTIATE_DEVICE_RESOURCE(GraphicsPipeline, ID3D12PipelineState, D3D12_GRAPHICS_PIPELINE_STATE_DESC);
    INSTANTIATE_DEVICE_RESOURCE(DescriptorHeap, ID3D12DescriptorHeap, D3D12_DESCRIPTOR_HEAP_DESC);
    INSTANTIATE_DEVICE_RESOURCE(Heap, ID3D12Heap, D3D12_HEAP_DESC);
    INSTANTIATE_DEVICE_RESOURCE(QueryHeap, ID3D12QueryHeap, D3D12_QUERY_HEAP_DESC);

    INSTANTIATE_DEVICE_RESOURCE(CmdList, ID3D12CommandList, GpuCmdListDesc);
    INSTANTIATE_DEVICE_RESOURCE(CommittedResource, ID3D12Resource, GpuCommittedResDesc);
    INSTANTIATE_DEVICE_RESOURCE(PlacedResource, ID3D12Resource, GpuPlacedResDesc);
    INSTANTIATE_DEVICE_RESOURCE(Fence, ID3D12Fence, GpuFenceDesc);
    INSTANTIATE_DEVICE_RESOURCE(RootSignature, ID3D12RootSignature, GpuRootSignatureDesc);

}  // namespace engine
#endif
