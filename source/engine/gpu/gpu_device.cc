#include <cassert>

#include "gpu_device.h"

engine::GpuDevice::GpuDevice(ID3D12Device10* d3d12_device)
    : d3d12_device_(d3d12_device)
{
    if (d3d12_device_)
    {
        d3d12_device_->AddRef();
    }
}

engine::GpuDevice::~GpuDevice()
{
    if (d3d12_device_)
    {
        d3d12_device_->Release();
        d3d12_device_ = nullptr;
    }
}

#define DEFINE_SPECIALIZED_CREATE(resource_type, resource_ptr_type, resource_desc) \
    template <>                                                                    \
    engine::GpuDeviceResource<resource_ptr_type>*                                  \
    engine::GpuDevice::Create<engine::GpuDeviceResource<resource_ptr_type>,        \
                              engine::GpuDeviceResourceDesc<resource_desc>>(       \
        const engine::GpuDeviceResourceDesc<resource_desc>& desc)

DEFINE_SPECIALIZED_CREATE(CmdQueue, ID3D12CommandQueue, D3D12_COMMAND_QUEUE_DESC)
{
    GpuDeviceResourceDesc<D3D12_COMMAND_QUEUE_DESC> queue_desc = desc;
    GpuDeviceResource<ID3D12CommandQueue>*          ret_queue  = nullptr;

    if (d3d12_device_)
    {
        ID3D12CommandQueue* cmd_queue = nullptr;
        if (SUCCEEDED(d3d12_device_->CreateCommandQueue(
                &queue_desc, __uuidof(ID3D12CommandQueue), reinterpret_cast<void**>(&cmd_queue))))
        {
            ret_queue =
                new GpuDeviceResContainer<CmdQueue, ID3D12CommandQueue, D3D12_COMMAND_QUEUE_DESC>(cmd_queue, desc);
            device_resources_map_[CmdList].push_back(ret_queue);
        }
    }

    return ret_queue;
}

DEFINE_SPECIALIZED_CREATE(CmdList, ID3D12CommandList, engine::GpuCmdListDesc)
{
    ID3D12CommandAllocator*               cmd_allocator = nullptr;
    GpuDeviceResourceDesc<GpuCmdListDesc> cmd_desc      = desc;
    GpuDeviceResource<ID3D12CommandList>* ret_list      = nullptr;

    if (!cmd_allocators_map_by_type_.contains(cmd_desc.Type))
    {
        if (SUCCEEDED(d3d12_device_->CreateCommandAllocator(
                cmd_desc.Type, __uuidof(ID3D12CommandAllocator), reinterpret_cast<void**>(&cmd_allocator))))
        {
            cmd_allocators_map_by_type_[cmd_desc.Type] = cmd_allocator;
        }
    }

    cmd_allocator = cmd_allocators_map_by_type_[cmd_desc.Type];

    if (cmd_allocator)
    {
        ID3D12CommandList* cmd_list = nullptr;
        if (SUCCEEDED(d3d12_device_->CreateCommandList(cmd_desc.Node,
                                                       cmd_desc.Type,
                                                       cmd_allocator,
                                                       nullptr,
                                                       __uuidof(ID3D12CommandList),
                                                       reinterpret_cast<void**>(&cmd_list))))
        {
            ret_list = new GpuDeviceResContainer<CmdList, ID3D12CommandList, engine::GpuCmdListDesc>(cmd_list, desc);
            device_resources_map_[CmdList].push_back(ret_list);
        }
    }

    return ret_list;
}

DEFINE_SPECIALIZED_CREATE(GraphicsPipeline, ID3D12PipelineState, D3D12_GRAPHICS_PIPELINE_STATE_DESC)
{
    GpuDeviceResource<ID3D12PipelineState>* ret_pipeline = nullptr;

    ID3D12PipelineState* pipeline_state = nullptr;
    if ((SUCCEEDED(d3d12_device_->CreateGraphicsPipelineState(
            &desc, __uuidof(ID3D12PipelineState), reinterpret_cast<void**>(&pipeline_state)))))
    {
        ret_pipeline =
            new GpuDeviceResContainer<GraphicsPipeline, ID3D12PipelineState, D3D12_GRAPHICS_PIPELINE_STATE_DESC>(
                pipeline_state, desc);
        device_resources_map_[GraphicsPipeline].push_back(ret_pipeline);
    }

    return ret_pipeline;
}

DEFINE_SPECIALIZED_CREATE(ComputePipeline, ID3D12PipelineState, D3D12_COMPUTE_PIPELINE_STATE_DESC)
{
    GpuDeviceResource<ID3D12PipelineState>* ret_pipeline = nullptr;

    ID3D12PipelineState* pipeline_state = nullptr;
    if ((SUCCEEDED(d3d12_device_->CreateComputePipelineState(
            &desc, __uuidof(ID3D12PipelineState), reinterpret_cast<void**>(&pipeline_state)))))
    {
        ret_pipeline =
            new GpuDeviceResContainer<GraphicsPipeline, ID3D12PipelineState, D3D12_COMPUTE_PIPELINE_STATE_DESC>(
                pipeline_state, desc);
        device_resources_map_[ComputePipeline].push_back(ret_pipeline);
    }

    return ret_pipeline;
}
