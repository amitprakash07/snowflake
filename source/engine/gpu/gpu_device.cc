#include "gpu_device.h"

#include <cassert>

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

engine::GpuQueue* engine::GpuDevice::CreateQueue(const GpuQueueDesc* desc)
{
    GpuQueueDesc queue_desc;
    if (desc)
    {
        queue_desc = *desc;
    }

    if (d3d12_device_)
    {
        ID3D12CommandQueue* cmd_queue = nullptr;
        if (SUCCEEDED(d3d12_device_->CreateCommandQueue(
                &queue_desc, __uuidof(ID3D12CommandQueue), reinterpret_cast<void**>(&cmd_queue))))
        {
            GpuQueue* new_queue = new GpuQueue(cmd_queue);
            gpu_queues_.push_back(new_queue);
            return new_queue;
        }
    }

    return nullptr;
}

engine::GpuCommandList* engine::GpuDevice::CreateCmdList(const GpuCmdListDesc* desc)
{
    ID3D12CommandAllocator* cmd_allocator = nullptr;
    GpuCmdListDesc          cmd_desc;
    GpuCommandList*         ret_list = nullptr;

    if (desc)
    {
        cmd_desc = *desc;
    }

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
            ret_list = new GpuCommandList(cmd_list);
        }
    }

    return ret_list;
}

engine::GpuResource* engine::GpuDevice::CreateResource(const GpuResourceDesc* desc)
{
}

engine::GpuPipeline* engine::GpuDevice::CreatePipeline(const GpuPipelineDesc* desc)
{
    GpuPipeline*         pipeline        = nullptr;
    ID3D12PipelineState* driver_pipeline = nullptr;

    if (desc)
    {
        switch (desc->type)
        {
        case Graphics:
        {
            assert(SUCCEEDED(d3d12_device_->CreateGraphicsPipelineState(&desc->graphics_pipeline_desc,
                                                                        __uuidof(ID3D12PipelineState),
                                                                        reinterpret_cast<void**>(&driver_pipeline))));
        }
        break;
        case Compute:
        {
            assert(SUCCEEDED(d3d12_device_->CreateComputePipelineState(&desc->compute_pipeline_desc,
                                                                       __uuidof(ID3D12PipelineState),
                                                                       reinterpret_cast<void**>(&driver_pipeline))));
        }
        break;
        }
    }

    if (driver_pipeline)
    {
        pipeline = new GpuPipeline(desc, driver_pipeline);
        gpu_pipelines_.push_back(pipeline);
    }

    return pipeline;
}