#ifndef CORE_GRAPHICS_RENDER_CONTEXT_H_
#define CORE_GRAPHICS_RENDER_CONTEXT_H_

#include <cstdint>
#include <limits>

#include "core/common/perf_stats.h"

#include "viewport.h"
#include "render_stats.h"
#include "image_2d.h"
#include "render_primitives.h"

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

    class DrawContext
    {
    public:
        DrawContext(PrimitiveDrawMode primitive_draw_mode_in,
                    DrawDebugFlag     draw_debug_flag_in,
                    bool              collect_draw_stats_in)
            : primitive_draw_mode_(primitive_draw_mode_in)
            , draw_debug_flag_(draw_debug_flag_in)
            , collect_draw_stats_(collect_draw_stats_in)
        {
        }

        DrawContext()
            : primitive_draw_mode_(PrimitiveDrawMode::kSolid)
            , draw_debug_flag_(DrawDebugFlag::kNone)
            , collect_draw_stats_(false)
        {
        }

        template <RenderPrimitiveType PrimitiveType>
        void StartRenderStatCollection(const RenderPrimitive<PrimitiveType>& primitive)
        {
            if (!collect_draw_stats_)
            {
                return;
            }

            if (render_stats_ == nullptr)
            {
                std::string name = std::format("Render stats of {}", primitive.GetObjectLabel().ToString());
                render_stats_    = StatsCollector::GetInstance().GetOrCreateStatsBucket<RenderStats>(name);
            }

            if (render_stats_ && !timer_started_)
            {
                render_stats_->rasterization_timer_->StartTimer();
                timer_started_ = true;
            }
        }

        void EndRenderStatCollection()
        {
            if (!collect_draw_stats_)
            {
                return;
            }

            if (render_stats_ && timer_started_)
            {
                render_stats_->rasterization_timer_->EndTimer();
                timer_started_ = false;
            }
        }

        void IncrementRenderStat(RenderStatCountKind kind)
        {
            if (!collect_draw_stats_)
            {
                return;
            }

            if (render_stats_ == nullptr)
            {
                return;
            }

            switch (kind)
            {
            case RenderStatCountKind::kRasterizedPixelCount:
                render_stats_->rasterized_pixel_counter_->Increment();
                break;
            }
        }

        PrimitiveDrawMode GetDrawMode() const
        {
            return primitive_draw_mode_;
        }

        DrawDebugFlag GetDrawDebugFlag() const
        {
            return draw_debug_flag_;
        }

    private:
        PrimitiveDrawMode            primitive_draw_mode_;
        DrawDebugFlag                draw_debug_flag_;
        bool                         collect_draw_stats_;
        std::shared_ptr<RenderStats> render_stats_;
        bool                         timer_started_ = false;
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

    class RenderOutputs
    {
    public:
        explicit RenderOutputs(const graphics::Viewport& viewport)
            : color_buffer_(viewport.GetWidth(), viewport.GetHeight())
        {
        }

        RenderOutputs() = delete;

        ColorBuffer& GetColorBuffer()
        {
            return color_buffer_;
        }

        const ColorBuffer& GetColorBuffer() const
        {
            return color_buffer_;
        }

    private:
        ColorBuffer color_buffer_;
    };

    class RenderFrame
    {
    public:
        explicit RenderFrame(const graphics::Viewport& viewport)
            : render_config_(viewport)
            , render_state_(viewport)
            , render_outputs_(viewport)
        {
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

        RenderOutputs& GetRenderOutputs()
        {
            return render_outputs_;
        }

        const RenderOutputs& GetRenderOutputs() const
        {
            return render_outputs_;
        }

    private:
        RenderConfig  render_config_;
        RenderState   render_state_;
        RenderOutputs render_outputs_;
    };
}  // namespace amit::graphics

#endif  // CORE_GRAPHICS_RENDER_CONTEXT_H_