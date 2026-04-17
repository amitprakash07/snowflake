#ifndef ENGINE_GRAPHICS_RASTERIZER_H_
#define ENGINE_GRAPHICS_RASTERIZER_H_

#include <functional>

#include "engine/maths/geometry_primitives.h"
#include "pixel.h"
#include "viewport.h"
#include "engine/common/perf_stats.h"

namespace engine
{
    namespace graphics
    {
        enum class RasterizeMode : uint8_t
        {
            PrimitiveOnly,
            BoundingBoxOnly,
            PrimitiveAndBoundingBox
        };

        enum class RenderStatCountKind : uint8_t
        {
            kRasterizedPixelCount
        };

        class RenderStats : public IStatsBucket
        {
        public:
            void Init() override
            {
                rasterization_timer_      = GetOrCreateTimerStat("Duration");
                rasterized_pixel_counter_ = GetOrCreateCounterStat("PixelCount");
            }

            ~RenderStats() override = default;
            std::shared_ptr<TimerStat>   rasterization_timer_;
            std::shared_ptr<CounterStat> rasterized_pixel_counter_;

            friend class engine::StatsCollector;

        private:
            RenderStats(const std::string& name)
                : IStatsBucket(name)
            {
            }
        };

        class RenderContext
        {
        public:
            RenderContext(const Viewport& viewport, RasterizeMode mode, bool collect_render_stats = false)
                : raster_mode_(mode)
                , collect_render_stats_(collect_render_stats)
                , viewport_(viewport)
            {
            }

            RenderContext() = delete;

            RasterizeMode GetRasterizeMode() const
            {
                return raster_mode_;
            }

            const Viewport& GetViewport() const
            {
                return viewport_;
            }

            void StartRenderStatCollection(const geometry::Primitive& primitive)
            {
                if (!IsCollectRenderStats())
                {
                    return;
                }

                if (render_stats_ == nullptr)
                {
                    std::string name = std::format("Render stats of {}", primitive.GetObjectLabel().ToString());
                    render_stats_    = StatsCollector::GetInstance().GetOrCreateStatsBucket<RenderStats>(name);
                }

                if (render_stats_)
                {
                    render_stats_->rasterization_timer_->StartTimer();
                }
            }

            void EndRenderStatCollection()
            {
                if (!IsCollectRenderStats())
                {
                    return;
                }

                if (render_stats_)
                {
                    render_stats_->rasterization_timer_->EndTimer();
                }
            }

            void IncrementRenderStat(RenderStatCountKind kind)
            {
                if (!IsCollectRenderStats())
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

        private:
            bool IsCollectRenderStats() const
            {
                return collect_render_stats_;
            }

            RasterizeMode                raster_mode_;
            bool                         collect_render_stats_;
            std::shared_ptr<RenderStats> render_stats_;
            Viewport                     viewport_;
        };

        struct RasterizedPixel
        {
            enum class Kind : uint8_t
            {
                Primitive,
                BoundingBox
            };

            Pixel pixel;
            Kind  pixel_kind;
        };

        class Rasterizer
        {
        public:
            Rasterizer() = default;

            template <engine::geometry::PrimitiveTypeConcept Primitive>
            void Rasterize(RenderContext&,
                           const Primitive&,
                           const std::function<void(const engine::graphics::RasterizedPixel&)>&) const
            {
            }

        private:
            void RenderPixel(RenderContext&         render_context,
                             const RasterizedPixel& pixel,
                             const std::function<void(const engine::graphics::RasterizedPixel& rasterized_pixel)>&
                                 pixel_callback) const
            {
                pixel_callback(pixel);
                render_context.IncrementRenderStat(RenderStatCountKind::kRasterizedPixelCount);
            }
        };

        template <>
        void Rasterizer::Rasterize<geometry::Triangle>(
            RenderContext&                                                                        render_context,
            const geometry::Triangle&                                                             triangle,
            const std::function<void(const engine::graphics::RasterizedPixel& rasterized_pixel)>& pixel_callback) const;

        template <>
        void Rasterizer::Rasterize<geometry::LineSegment>(
            RenderContext&                                                                        render_context,
            const geometry::LineSegment&                                                          line,
            const std::function<void(const engine::graphics::RasterizedPixel& rasterized_pixel)>& pixel_callback) const;

    }  // namespace graphics
}  // namespace engine

#endif