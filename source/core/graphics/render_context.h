#ifndef CORE_GRAPHICS_RENDER_CONTEXT_H_
#define CORE_GRAPHICS_RENDER_CONTEXT_H_

#include <cstdint>

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

    class RenderContext
    {
    public:
        RenderContext(const graphics::Viewport& viewport)
            : viewport_(viewport)
            , color_buffer_(viewport.GetWidth(), viewport.GetHeight())
            , depth_buffer_(viewport.GetWidth(), viewport.GetHeight())
        {
            depth_buffer_.FillImage(std::numeric_limits<float>::infinity());
        }

        RenderContext() = delete;

        const graphics::Viewport& GetViewport() const
        {
            return viewport_;
        }

        ColorBuffer& GetColorBuffer()
        {
            return color_buffer_;
        }

        DepthBuffer& GetDepthBuffer()
        {
            return depth_buffer_;
        }

    private:
        Viewport    viewport_;
        ColorBuffer color_buffer_;
        DepthBuffer depth_buffer_;
    };
}  // namespace amit::graphics

#endif  // CORE_GRAPHICS_RENDER_CONTEXT_H_