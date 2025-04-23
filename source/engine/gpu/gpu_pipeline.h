#ifndef ENGINE_GPU_GPU_PIPELINE_H_
#define ENGINE_GPU_GPU_PIPELINE_H_

#include <d3d12.h>

namespace engine
{
    enum PipelineType
    {
        Compute,
        Graphics
    };

    struct GpuPipelineDesc
    {
        PipelineType type;
        union
        {
            D3D12_GRAPHICS_PIPELINE_STATE_DESC graphics_pipeline_desc;
            D3D12_COMPUTE_PIPELINE_STATE_DESC compute_pipeline_desc;
        };
    };

    class GpuPipeline
    {
    public:
        GpuPipeline(const GpuPipelineDesc* desc, ID3D12PipelineState* d3d12_pipeline);
    };
}  // namespace engine

#endif
