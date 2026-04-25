#ifndef CORE_GRAPHICS_RENDER_CONTEXT_H_
#define CORE_GRAPHICS_RENDER_CONTEXT_H_

#include <cstdint>
#include <limits>
#include <vector>

#include "core/common/perf_stats.h"

#include "viewport.h"
#include "render_stats.h"
#include "image_2d.h"
#include "core/graphics_common/render_primitives.h"

namespace amit::graphics
{
    enum class PrimitiveDrawMode : std::uint8_t
    {
        kNone,
        kWireframe,
        kSolid,
    };

    enum class DrawDebugFlag
    {
        kNone,
        kWireframeBoundingBox
    };

    struct DrawOptions
    {
        PrimitiveDrawMode GetDrawMode() const
        {
            return primitive_draw_mode;
        }
        DrawDebugFlag     GetDrawDebugFlag() const
        {
            return draw_debug_flag;
        }

        const PrimitiveDrawMode primitive_draw_mode;
        const DrawDebugFlag     draw_debug_flag;
        const bool              collect_draw_stats;
    };

    class RenderConfig
    {
    public:
        explicit RenderConfig(const graphics::Viewport& viewport)
            : viewport_(viewport)
        {
        }

        RenderConfig() = delete;

        const graphics::Viewport& GetViewport() const
        {
            return viewport_;
        }

    private:
        Viewport viewport_;
    };

    class RenderState
    {
    public:
        explicit RenderState(const graphics::Viewport& viewport)
            : depth_buffer_(viewport.GetWidth(), viewport.GetHeight())
        {
            depth_buffer_.FillImage(std::numeric_limits<float>::infinity());
        }

        RenderState() = delete;

        float GetDepth(const ImageCoordinate& image_coordinate) const
        {
            return depth_buffer_.GetImageData(image_coordinate);
        }

        bool TryUpdateDepth(const ImageCoordinate& image_coordinate, float candidate_depth)
        {
            if (candidate_depth < depth_buffer_.GetImageData(image_coordinate))
            {
                depth_buffer_.SetImageData(image_coordinate, candidate_depth);
                return true;
            }

            return false;
        }

        const DepthBuffer& GetDepthBuffer() const
        {
            return depth_buffer_;
        }

    private:
        DepthBuffer depth_buffer_;
    };

    enum class RenderOutputFormat : std::uint8_t
    {
        kRgb8
    };

    struct RenderOutputDescription
    {
        Width              width;
        Height             height;
        RenderOutputFormat format = RenderOutputFormat::kRgb8;
    };

    class RenderOutput
    {
    public:
        explicit RenderOutput(const RenderOutputDescription& description)
            : format_(description.format)
            , color_buffer_(description.width, description.height)
        {
        }

        RenderOutput() = delete;

        RenderOutputFormat GetFormat() const
        {
            return format_;
        }

        ColorBuffer& GetColorBuffer()
        {
            return color_buffer_;
        }

        const ColorBuffer& GetColorBuffer() const
        {
            return color_buffer_;
        }

    private:
        RenderOutputFormat format_;
        ColorBuffer        color_buffer_;
    };

    class RenderFrame
    {
    public:
        explicit RenderFrame(const graphics::Viewport& viewport)
            : render_config_(viewport)
            , render_state_(viewport)
            , render_output_list_()
        {
            render_output_list_.emplace_back(
                RenderOutputDescription{viewport.GetWidth(), viewport.GetHeight(), RenderOutputFormat::kRgb8});
        }

        RenderFrame() = delete;

        const RenderConfig& GetRenderConfig() const
        {
            return render_config_;
        }

        RenderState& GetRenderState()
        {
            return render_state_;
        }

        RenderOutput& GetRenderOutput(std::uint32_t index = 0)
        {
            return render_output_list_.at(index);
        }

        const RenderOutput& GetRenderOutput(std::uint32_t index = 0) const
        {
            return render_output_list_.at(index);
        }

    private:
        RenderConfig              render_config_;
        RenderState               render_state_;
        std::vector<RenderOutput> render_output_list_;
    };
}  // namespace amit::graphics

#endif  // CORE_GRAPHICS_RENDER_CONTEXT_H_